from functions import (addition, subtraction, digit_list_to_string,
                       multiplication_by_one_digit, division_by_one_digit,
                       base_b_to_base_2, base_2_to_base_b, is_power_of_two,
                       base_b_to_base_10, base_10_to_base_b, substitution_method,
                       string_to_digit_list, digit_list_to_integer, is_number_valid_for_base,
                       successive_divisions_method, compute_binary_value)


def display_menu():
    print("1. Addition of two numbers in a base\n"
          "2. Subtraction of two numbers in a base\n"
          "3. Multiplication of a number by a digit in a base\n"
          "4. Division of a number by a digit in base\n"
          "5. Rapid conversions between two bases p, q from {2, 4, 8, 16}\n"
          "6. Algorithm for conversion using 10 as an intermediate base\n"
          "7. Algorithm for the substitution method\n"
          "8. Algorithm for the method of successive divisions\n"
          "9. Exit\n")


def UI():
    addition_option = 1
    subtraction_option = 2
    multiplication_option = 3
    division_option = 4
    rapid_conversions_option = 5
    ten_as_intermediate_base_method_option = 6
    substitution_method_option = 7
    successive_divisions_option = 8
    exit_option = 9

    while True:
        try:
            display_menu()
            option = int(input("Enter option: \n> "))

            if option > 9 or option < 1:
                raise ValueError("Unavailable option")

            if option == addition_option:
                base = int(input("Enter the base: "))
                first_number = str(input("Enter first number: "))
                second_number = str(input("Enter second number: "))

                assert 1 < base < 17
                assert is_number_valid_for_base(first_number, base)
                assert is_number_valid_for_base(second_number, base)

                print(f"Result is {digit_list_to_string(addition(first_number, second_number, base))}")

            elif option == subtraction_option:

                base = int(input("enter the base: "))
                first_number = str(input("enter first number: "))
                second_number = str(input("enter second number: "))

                assert 1 < base < 17
                assert is_number_valid_for_base(first_number, base)
                assert is_number_valid_for_base(second_number, base)

                print(f"Result is {subtraction(first_number, second_number, base)}")

            elif option == multiplication_option:

                base = int(input("enter the base: "))
                first_number = str(input("enter first number: "))
                second_number = str(input("enter second number: "))

                assert 1 < base < 17
                assert is_number_valid_for_base(first_number, base)
                assert is_number_valid_for_base(second_number, base)

                print(f"Result is {digit_list_to_string(multiplication_by_one_digit(first_number, second_number, base))}")

            elif option == division_option:

                base = int(input("enter the base: "))
                first_number = str(input("enter first number: "))
                second_number = str(input("enter second number: "))

                assert 1 < base < 17
                assert is_number_valid_for_base(first_number, base)
                assert is_number_valid_for_base(second_number, base)

                value, remainder = division_by_one_digit(first_number, second_number, base)
                print(f"Quotient is {digit_list_to_string(value)}", f"\nRemainder is {remainder}")

            elif option == rapid_conversions_option:

                source_base = int(input("Enter source base: "))
                number = str(input("Enter the number you want to convert: "))
                destination_base = int(input("Enter destination base: "))

                assert 17 > source_base > 1 and 17 > destination_base > 1
                assert is_power_of_two(source_base) and is_power_of_two(destination_base)
                assert is_number_valid_for_base(number, source_base)

                if source_base == 2:
                    destination_base_value = base_2_to_base_b(str(number), destination_base)
                elif destination_base == 2:
                    destination_base_value = base_b_to_base_2(str(number), source_base)
                else:
                    base_2_value = base_b_to_base_2(str(number), source_base)
                    destination_base_value = base_2_to_base_b(str(base_2_value), destination_base)

                print(f"Result is {destination_base_value}")

            elif option == ten_as_intermediate_base_method_option:

                source_base = int(input("Enter source base: "))
                number = str(input("Enter the number you want to convert: "))
                destination_base = int(input("Enter destination base: "))

                assert 17 > source_base > 1 and 17 > destination_base > 1
                assert is_number_valid_for_base(number, source_base)

                if source_base == 10:
                    destination_base_value = base_10_to_base_b(digit_list_to_integer(string_to_digit_list(number)),
                                                               str(destination_base))
                elif destination_base == 10:
                    destination_base_value = base_b_to_base_10(number, str(source_base))
                else:
                    base_10_value = base_b_to_base_10(number, str(source_base))
                    destination_base_value = base_10_to_base_b(base_10_value, destination_base)

                print(f"Result is {destination_base_value}")

            elif option == substitution_method_option:

                source_base = int(input("Enter source base: "))
                number = str(input("Enter the number you want to convert: "))
                destination_base = int(input("Enter destination base: "))

                assert 17 > source_base > 1 and 17 > destination_base > 1
                assert is_number_valid_for_base(number, source_base)

                if source_base > destination_base:
                    raise ValueError("Source base must be smaller than the destination base")

                print(f"Result is {substitution_method(number, str(source_base), str(destination_base))}")

            elif option == successive_divisions_option:

                source_base = int(input("Enter source base: "))
                number = str(input("Enter the number you want to convert: "))
                destination_base = int(input("Enter destination base: "))

                assert 17 > source_base > 1 and 17 > destination_base > 1
                assert is_number_valid_for_base(number, source_base)

                if source_base < destination_base:
                    raise ValueError("Source base must be larger than the destination base")

                print(f"Result is {successive_divisions_method(number, str(source_base), str(destination_base))}")

            elif option == exit_option:
                exit(0)

        except ValueError as ve:
            print(ve)
        except AssertionError:
            print("Incorrect base or number")


UI()