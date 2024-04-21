import random
import timeit
import time


def display_menu():
    header = "+------------------------------------------+"
    print(header)
    print("|                 MENU                     |")
    print(header)
    print("| 1. Generate a list of n random numbers.  |")
    print("| 2. Sort the list using Selection Sort.   |")
    print("| 3. Sort the list using Stooge Sort.      |")
    print("| 4. Best case scenario                    |")
    print("| 5. Average case scenario                 |")
    print("| 6. Worst case scenario                   |")
    print("| 7. Exit                                  |")
    print(header)


def time_effective_selection_sort(number_list: list):
    # time complexity: O(n^2)
    list_length = len(number_list)
    for i in range(0, list_length):
        index_of_minimum = i

        for j in range(i + 1, list_length):
            if number_list[j] < number_list[index_of_minimum]:
                index_of_minimum = j

        (number_list[i], number_list[index_of_minimum]) = (number_list[index_of_minimum], number_list[i])

    return number_list


def selection_sort_with_given_step(number_list: list, given_step: int):
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


def stooge_sort_with_given_step(number_list: list, given_step: int, left_index: int,
                                right_index: int, current_step: int):
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

        current_step = stooge_sort_with_given_step(number_list, given_step, left_index, right_index - one_third, current_step)
        current_step = stooge_sort_with_given_step(number_list, given_step, left_index + one_third, right_index, current_step)
        current_step = stooge_sort_with_given_step(number_list, given_step, left_index, right_index - one_third, current_step)

    return current_step


def time_effective_stooge_sort(number_list: list, left_index: int, right_index: int):
    # time complexity: O(n^2.709)
    if number_list[left_index] > number_list[right_index]:
        (number_list[left_index], number_list[right_index]) = (number_list[right_index], number_list[left_index])

    if right_index - left_index > 1:
        one_third = int((right_index - left_index + 1) // 3)

        time_effective_stooge_sort(number_list, left_index, right_index - one_third)
        time_effective_stooge_sort(number_list, left_index + one_third, right_index)
        time_effective_stooge_sort(number_list, left_index, right_index - one_third)


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


def display_runtime_based_on_scenario(sorting_scenario):
    list_length = 125
    header_format = "{:<10} | {:<10} | {:<10}"
    sorting_scenario_message = {1: "Best case scenario: ", 2: "Average case scenario: ", 3: "Worst case scenario "}
    print(sorting_scenario_message[sorting_scenario - 3])
    print(header_format.format("List Length", "Selection Sort", "Stooge Sort"))

    for _ in range(5):
        number_list = [0] * list_length
        for i in range(0, list_length - 1):
            number_list[i] = int(random.randint(-10000, 10000))

        if sorting_scenario == 4 or sorting_scenario == 6:
            number_list = time_effective_selection_sort(number_list)
        if sorting_scenario == 6:
            number_list.reverse()

        selection_sort_start_time = time.time()
        time_effective_selection_sort(number_list)
        selection_sort_end_time = time.time()

        elapsed_time_for_selection_sort = selection_sort_end_time - selection_sort_start_time

        if sorting_scenario == 4 or sorting_scenario == 6:
            number_list = time_effective_selection_sort(number_list)
        if sorting_scenario == 6:
            number_list.reverse()

        selection_sort_start_time = time.time()
        time_effective_stooge_sort(number_list, 0, list_length - 1)
        selection_sort_end_time = time.time()

        elapsed_time_for_stooge_sort = selection_sort_end_time - selection_sort_start_time

        print("{:<11} | {:<14f} | {:<12f}".format(list_length, elapsed_time_for_selection_sort,
                                                  elapsed_time_for_stooge_sort))
        list_length = list_length * 2
    print("")


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
                    selection_sort_with_given_step(number_list, step)
                    number_list = unsorted_number_list[:]
                elif option_selected == 3:
                    print(unsorted_number_list)
                    stooge_sort_with_given_step(number_list, step, 0, len(number_list) - 1, 0)
                    number_list = unsorted_number_list[:]

        if option_selected > 3 and option_selected != 7:
            display_runtime_based_on_scenario(option_selected)

        if option_selected == 7:
            exit()


while True:
    main()
