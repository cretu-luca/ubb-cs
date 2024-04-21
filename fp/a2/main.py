import random


def display_menu():  # displays the menu
    print("MENU")
    print("1.Generate a list of n random natural numbers.")
    print("2.Sort the list using Selection Sort.")
    print("3.Sort the list using Stooge Sort.")
    print("4.Exit")


def selection_sort(number_list: list, given_step: int):
    # time complexity: O(n^2)
    list_length = len(number_list)
    current_step = 0
    for i in range(0, list_length):
        index_of_minimum = i

        for j in range(i + 1, list_length):
            if number_list[j] < number_list[index_of_minimum]:
                index_of_minimum = j

        (number_list[i], number_list[index_of_minimum]) = (number_list[index_of_minimum], number_list[i])
        current_step += 1

        if current_step == given_step:
            for ind in range(0, list_length):
                print(number_list[ind], end=" ")
            print("")
            current_step = 0


def stooge_sort(number_list: list, given_step: int, left_index: int, right_index: int, current_step: int):
    # time complexity: O(n^2.709)
    if number_list[left_index] > number_list[right_index]:
        (number_list[left_index], number_list[right_index]) = (number_list[right_index], number_list[left_index])
        current_step += 1

    if current_step == given_step:
        for index in range(0, len(number_list)):
            print(number_list[index], end=" ")
        print("")
        current_step = 0

    if right_index - left_index > 1:  # more than 2 elements
        one_third = int((right_index - left_index + 1) / 3)

        current_step = stooge_sort(number_list, given_step, left_index, right_index - one_third, current_step)
        current_step = stooge_sort(number_list, given_step, left_index + one_third, right_index, current_step)
        current_step = stooge_sort(number_list, given_step, left_index, right_index - one_third, current_step)

    return current_step


def fill_the_list():  # fills the list with random values, for given length of the list
    list_length = int(input("Type the length of the list: "))
    number_list = [0] * list_length
    for i in range(0, list_length):
        number_list[i] = int(random.randint(0, 100))

    print("The list contains the following elements: ")
    for i in range(0, list_length):
        print(number_list[i], end=" ")
    print("")

    return number_list


def main():
    are_numbers_generated = 0
    number_list = list()
    unsorted_number_list = list()

    while True:
        display_menu()
        option_selected = int(input("> "))

        if option_selected == 1:
            number_list = fill_the_list()
            unsorted_number_list = number_list[:]
            are_numbers_generated = 1

        if option_selected == 2 or option_selected == 3:
            if are_numbers_generated == 0:
                print("You need to generate the list's elements first!")
            else:
                step = int(input("Type the step value: "))

                if option_selected == 2:
                    print(unsorted_number_list)
                    selection_sort(number_list, step)
                    number_list = unsorted_number_list[:]
                elif option_selected == 3:
                    print(unsorted_number_list)
                    stooge_sort(number_list, step, 0, len(number_list) - 1, 0)
                    number_list = unsorted_number_list[:]

        if option_selected == 4:
            exit()


while True:
    main()
