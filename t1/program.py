from random import randint

#
# Functions section
#


def integer_to_list(integer: int):
    digits_list = [0, 0, 0, 0]

    digits_list[3] = integer % 10
    digits_list[2] = integer // 10 % 10
    digits_list[1] = integer // 100 % 10
    digits_list[0] = integer // 1000

    return digits_list


def check_number_validity(random_list_of_digits):

    if not(999 < list_to_integer(random_list_of_digits) < 10000):
        return False

    frequency = [0] * 10
    for digit in random_list_of_digits:
        frequency[digit] += 1

    if max(frequency) > 1 or random_list_of_digits[0] == 0:
        return False

    return True


def find_codes_and_runners(generated_number_digits_list: list, input_number_digits_list):
    '''
    :param generated_number_digits_list: a list containing the digits of the secret number
    :param input_number_digits_list: a list containing the digits of the number entered by the player
    :return: the function returns the number of codes (correct digits in the correct position) and the number
    of runners (correct digits, but in incorrect positions
    '''

    codes = 0 # correct digits in correct positions
    runners = 0 # correct digits in incorrect positions

    for index in range(4):
        if input_number_digits_list[index] == generated_number_digits_list[index]:
            codes += 1
        if input_number_digits_list[index] != generated_number_digits_list[index] and \
                input_number_digits_list[index] in generated_number_digits_list:
            runners += 1

    return codes, runners


def generate_random_number():
    random_number_digits = [0] * 4
    random_number_digits[0] = randint(1, 9)
    digits_generated = 1

    while digits_generated < 4:
        next_digit = randint(0, 9)

        if next_digit not in random_number_digits:
            random_number_digits[digits_generated] = next_digit
            digits_generated += 1

    return random_number_digits


def list_to_integer(random_number_digits: list):
    random_number = 0
    digit_index = 0
    while digit_index < 4:
        random_number = random_number * 10 + random_number_digits[digit_index]
        digit_index += 1

    return random_number

#
# User interface section
#

def display_introduction_to_Code_Games():
    print("This is the Code Game! A four-digit random secret number has been generated\n"
          "Your goal is to guess it by entering four-distinct-digit numbers\n"
          "When a wrong input is entered, the game stops and the computer wins\n")


def display_cheat_code(randomly_generated_number_list):
    print(f"\nYou have enter the cheat code, which reveals the four-digit random secret number.\n"
          f"The secret number is {list_to_integer(randomly_generated_number_list)}\n")


def display_codes_and_runners(codes: int, runners: int):
    print(f"\nYour number contains {codes} codes and {runners} runners\n")


def main():

    cheat_code = 8086
    number_not_guessed = 1

    randomly_generated_number_list = generate_random_number()
    randomly_generated_number = list_to_integer(randomly_generated_number_list)
    display_introduction_to_Code_Games()

    while number_not_guessed:

        try:
            player_input = int(input("Enter your guess: "))

            if player_input == cheat_code:
                display_cheat_code(randomly_generated_number_list)
            else:
                if not check_number_validity(integer_to_list(player_input)):
                    raise ValueError

                if player_input == randomly_generated_number:
                    number_not_guessed = 0
                    print("\nYou have guessed the code!\nEnd of the game. You won!")
                    exit(0)
                else:
                    codes, runners = find_codes_and_runners(randomly_generated_number_list, integer_to_list(player_input))
                    display_codes_and_runners(codes, runners)

        except ValueError:
            print("\nThe number you entered is not valid.")
            print("This is the end of the game. The computer won...\n")
            exit(0)


main()