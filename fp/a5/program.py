from math import sqrt
from random import randint

# task 5 and 9
# Write the implementation for A5 in this file
#

# 
# Write below this comment 
# Functions to deal with complex numbers -- list representation
# -> There should be no print or input statements in this section 
# -> Each function should do one thing only
# -> Functions communicate using input parameters and their return values
#


def complex_number_modulus_list_representation(complex_number):
    return sqrt(complex_number[0] * complex_number[0] + complex_number[1] * complex_number[1])


def generate_complex_numbers_list_representation(complex_numbers_list, number_of_values_to_read):
    lower_bound = -20
    upper_bound = 20
    while number_of_values_to_read > 0:
        real_part = randint(lower_bound, upper_bound)
        imaginary_part = randint(lower_bound, upper_bound)
        complex_numbers_list.append([real_part, imaginary_part])
        number_of_values_to_read -= 1

    return complex_numbers_list


def list_to_string(complex_number: list):
    zero = 0
    string_complex_number = ""
    if complex_number[0] != zero:
        string_complex_number += str(complex_number[0])
    if complex_number[1] < zero:
        string_complex_number += "-" + str(abs(complex_number[1])) + "i"
    elif complex_number[1] > zero:
        if complex_number[0] != zero:
            string_complex_number += "+"
        string_complex_number += str(complex_number[1]) + "i"
    if complex_number[0] == zero and complex_number[1] == zero:
        string_complex_number += "0"

    return string_complex_number


#
# Write below this comment
# Functions to deal with complex numbers -- dict representation
# -> There should be no print or input statements in this section
# -> Each function should do one thing only
# -> Functions communicate using input parameters and their return values


def complex_number_modulus_dictionary_representation(complex_number):
    return sqrt(complex_number["real"] * complex_number["real"] +
                complex_number["imaginary"] * complex_number["imaginary"])


def generate_complex_numbers_dictionary_representation(complex_numbers_list, number_of_values_to_read):
    lower_bound = -20
    upper_bound = 20
    while number_of_values_to_read > 0:
        real_part = randint(lower_bound, upper_bound)
        imaginary_part = randint(lower_bound, upper_bound)
        complex_numbers_list.append({"real": real_part, "imaginary": imaginary_part})
        number_of_values_to_read -= 1
    return complex_numbers_list


def dictionary_to_string(complex_number: dict):
    zero = 0
    string_complex_number = ""
    if complex_number["real"] != zero:
        string_complex_number += str(complex_number["real"])
    if complex_number["imaginary"] < zero:
        string_complex_number += "-" + str(abs(complex_number["imaginary"])) + "i"
    elif complex_number["imaginary"] > zero:
        if complex_number["real"] != zero:
            string_complex_number += "+"
        string_complex_number += str(complex_number["imaginary"]) + "i"
    if complex_number["real"] == zero and complex_number["imaginary"] == zero:
        string_complex_number += "0"

    return string_complex_number


#
# Write below this comment
# Functions that deal with subarray/subsequence properties
# -> There should be no print or input statements in this section
# -> Each function should do one thing only
# -> Functions communicate using input parameters and their return values
#


def find_longest_subarray_of_elements_with_modulus_under_ten_naive(complex_numbers_list):
    ten = 10
    current_length = 0
    maximum_length = 0
    current_subarray = []
    longest_subarray = []

    for complex_number in complex_numbers_list:
        if isinstance(complex_number, list):
            if complex_number_modulus_list_representation(complex_number) <= ten:
                current_length += 1
                current_subarray.append(complex_number)
            else:
                if current_length > maximum_length:
                    maximum_length = current_length
                    longest_subarray = current_subarray[:]
        elif isinstance(complex_number, dict):
            if complex_number_modulus_dictionary_representation(complex_number) <= ten:
                current_length += 1
                current_subarray.append(complex_number)
            else:
                if current_length > maximum_length:
                    maximum_length = current_length
                    longest_subarray = current_subarray[:]

    if current_length > maximum_length:
        maximum_length = current_length
        longest_subarray = current_subarray[:]

    return longest_subarray, maximum_length


def find_longest_increasing_subsequence_by_modulus_dynamical_programming(complex_numbers_list):
    sequence_length = len(complex_numbers_list)
    current_longest_sequence = [1] * sequence_length
    indices_of_increasing_subsequence = [-1] * sequence_length

    for i in range(1, sequence_length):
        for j in range(i):
            if isinstance(complex_numbers_list[0], list):
                if (complex_number_modulus_list_representation(complex_numbers_list[i]) >
                        complex_number_modulus_list_representation(complex_numbers_list[j]) and
                        current_longest_sequence[i] < current_longest_sequence[j] + 1):
                    current_longest_sequence[i] = current_longest_sequence[j] + 1
                    indices_of_increasing_subsequence[i] = j
            elif isinstance(complex_numbers_list[0], dict):
                if (complex_number_modulus_dictionary_representation(complex_numbers_list[i]) >
                        complex_number_modulus_dictionary_representation(complex_numbers_list[j]) and
                        current_longest_sequence[i] < current_longest_sequence[j] + 1):
                    current_longest_sequence[i] = current_longest_sequence[j] + 1
                    indices_of_increasing_subsequence[i] = j

    maximum_length = max(current_longest_sequence)
    maximum_length_right_index = current_longest_sequence.index(maximum_length)

    longest_sequence = []
    while maximum_length_right_index != -1:
        longest_sequence.append(complex_numbers_list[maximum_length_right_index])
        maximum_length_right_index = indices_of_increasing_subsequence[maximum_length_right_index]

    longest_sequence.reverse()

    return longest_sequence, maximum_length


#
# Write below this comment
# UI section
# Write all functions that have input or print statements here
# Ideally, this section should not contain any calculations relevant to program functionalities
#

def read_complex_numbers(complex_numbers_list):
    real_part = int(input("Enter the value of the real part: "))
    imaginary_part = int(input("Enter the value of the imaginary part: "))
    if isinstance(complex_numbers_list[0], list):
        complex_numbers_list.append(([real_part, imaginary_part]))
    elif isinstance(complex_numbers_list[0], dict):
        complex_numbers_list.append({"real": real_part, "imaginary": imaginary_part})


def print_menu():
    print("1. Read complex numbers\n"
          "2. Display the list of complex numbers\n"
          "3. Display length and elements of the longest subarray of numbers "
          "where each numbers's modulus is in the [0, 10] range\n"
          "4. The length and elements of a longest increasing subsequence, when considering "
          "each number's modulus\n"
          "5. Exit ")


def display_list(complex_numbers_list_to_display):
    for complex_number in complex_numbers_list_to_display:
        if isinstance(complex_number, list):
            print(list_to_string(complex_number))
        elif isinstance(complex_number, dict):
            print(dictionary_to_string(complex_number))


def main():
    read_numbers = 1
    display_the_list = 2
    the_longest_subarray_of_elements_with_modulus_under_ten = 3
    the_longest_increasing_sequence_by_modulus = 4
    exit_code = 5
    ten = 10

    list_representation = 1
    dictionary_representation = 2
    complex_numbers_list = []

    representation = int(input("Choose the representation:\n"
                               "1. List representation\n"
                               "2. Dictionary representation\n"
                               "> "))

    if representation == list_representation:
        generate_complex_numbers_list_representation(complex_numbers_list, ten)
        print("You have selected the list representation.")
    elif representation == dictionary_representation:
        generate_complex_numbers_dictionary_representation(complex_numbers_list, ten)
        print("You have selected the dictionary representation.")

    while True:
        print_menu()
        chosen_option = int(input("> "))

        if chosen_option == read_numbers:
            number_of_numbers_to_read = int(input("Enter the number of values to read\n> "))
            while number_of_numbers_to_read > 0:
                number_of_numbers_to_read -= 1
                read_complex_numbers(complex_numbers_list)
        elif chosen_option == display_the_list:
            display_list(complex_numbers_list)
        elif chosen_option == the_longest_subarray_of_elements_with_modulus_under_ten:
            longest_sequence, sequence_length = find_longest_subarray_of_elements_with_modulus_under_ten_naive(complex_numbers_list)
            print(f"This is the longest subarray with elements with modulus less than 10:")
            display_list(longest_sequence)
            print(f"It contains {sequence_length} elements")
        elif chosen_option == the_longest_increasing_sequence_by_modulus:
            longest_sequence, sequence_length = find_longest_increasing_subsequence_by_modulus_dynamical_programming(complex_numbers_list)
            print(f"This is the longest increasing sequence of complex numbers:")
            display_list(longest_sequence)
            print(f"It contains {sequence_length} elements")
        elif chosen_option == exit_code:
            exit(0)


if __name__ == "__main__":
    print("Make magic happen")
    main()
