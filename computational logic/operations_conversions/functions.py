import math

dictionary = {
    0: "0", 1: "1", 2: "2", 3: "3", 4: "4", 5: "5", 6: "6", 7: "7",
    8: "8", 9: "9", 10: "A", 11: "B", 12: "C", 13: "D", 14: "E", 15: "F"
}

def is_power_of_two(number):
    while number > 1:
        number /= 2

    return number == 1


def digit_number(number):
    counter = 0
    while number > 0:
        counter += 1
        number //= 10

    return counter


def calculate_power_of_two(power):
    counter = 0
    while power > 1:
        power //= 2
        counter += 1

    return counter


def is_number_valid_for_base(number, base):
    hex_digits = "0123456789ABCDEF"[:base]

    for char in number.upper():
        if char not in hex_digits:
            return False

    return True

def string_to_digit_list(number_string):
    return [int(char, 16) for char in number_string.upper()]


def integer_to_digit_list(number, length):
    digit_list = [0] * (length + 1)
    while number > 0:
        digit_list[length] = number % 10
        number //= 10
        length -= 1

    return digit_list


def digit_list_to_string(digit_list):
    if digit_list is None:
        pass

    hex_digits = "0123456789ABCDEF"

    number_string = ""
    unnecessary_zeros = 1
    for digit in digit_list:
        if digit != 0:
            unnecessary_zeros = 0
        if not unnecessary_zeros:
            if isinstance(digit, int):
                number_string += hex_digits[digit]
            else:
                number_string += hex_digits[int(digit, 16)]

    if number_string == "":
        number_string = "0"

    return number_string


def digit_list_to_integer(number_digit_list):
    number_value = 0
    for digit in number_digit_list:
        number_value = number_value * 10 + digit

    return number_value

def addition(first_number, second_number, base):
    first_number_digit_list = string_to_digit_list(first_number)
    second_number_digit_list = string_to_digit_list(second_number)

    length = max(len(first_number_digit_list), len(second_number_digit_list))

    first_number_digit_list = [0] * (length - len(first_number_digit_list)) + first_number_digit_list
    second_number_digit_list = [0] * (length - len(second_number_digit_list)) + second_number_digit_list

    result_digit_list = [0] * (length + 1)

    carry = 0
    for index in range(length - 1, -1, -1):
        value = first_number_digit_list[index] + second_number_digit_list[index] + carry
        carry = value // base
        result_digit_list[index+1] = value % base

    if carry > 0:
        result_digit_list[0] = carry

    return result_digit_list


def subtraction(first_number, second_number, base):
    first_number_digit_list = string_to_digit_list(first_number)
    second_number_digit_list = string_to_digit_list(second_number)

    if digit_list_to_integer(first_number_digit_list) < digit_list_to_integer(second_number_digit_list):
        first_number_digit_list, second_number_digit_list = second_number_digit_list, first_number_digit_list
        negative = True
    else:
        negative = False

    length = max(len(first_number_digit_list), len(second_number_digit_list))

    first_number_digit_list = [0] * (length - len(first_number_digit_list)) + first_number_digit_list
    second_number_digit_list = [0] * (length - len(second_number_digit_list)) + second_number_digit_list

    result_digit_list = [0] * length

    borrow = 0
    for index in range(length - 1, -1, -1):
        subtraction_result_at_index = first_number_digit_list[index] - second_number_digit_list[index] - borrow
        if subtraction_result_at_index < 0:
            subtraction_result_at_index += base
            borrow = 1
        else:
            borrow = 0

        result_digit_list[index] = subtraction_result_at_index

    result_string = digit_list_to_string(result_digit_list)
    if negative:
        result_string = '-' + result_string

    return result_string


def multiplication_by_one_digit(first_number, second_number, base):
    first_number_digit_list = string_to_digit_list(first_number)
    second_number_value = int(second_number, 16)

    length_of_result = len(first_number_digit_list)
    result_digit_list = [0] * (length_of_result + 1)

    carry = 0
    for index in range(length_of_result - 1, -1, -1):
        product = first_number_digit_list[index] * second_number_value + carry
        result_digit_list[index+1] = product % base
        carry = product // base

    if 0 < carry < base:
        result_digit_list[0] = carry

    return digit_list_to_string(result_digit_list)


def division_by_one_digit(first_number, second_number, base):
    first_number_digit_list = string_to_digit_list(first_number)
    second_number_value = int(second_number, base)

    length_of_result = len(first_number_digit_list)
    result_digit_list = [0] * length_of_result

    last_remainder = 0
    for index in range(length_of_result):
        value = last_remainder * base + first_number_digit_list[index]
        result_digit_list[index] = value // second_number_value
        last_remainder = value % second_number_value

    return result_digit_list, last_remainder


def compute_binary_value(digit_string):
    int_value = int(digit_string, 16)
    result = ""

    while int_value > 0:
        result = str(int_value % 2) + result
        int_value //= 2

    return result


def base_b_to_base_2(number_string, base):
    result = ""
    digit_group = int(math.log2(base))
    for digit in number_string:
        digit = compute_binary_value(digit)
        while len(digit) < digit_group:
            digit = "0" + digit

        result += digit

    return result.lstrip('0') or '0'


def base_2_to_base_b(value, base):
    digit_group = int(math.log2(base))

    while len(value) % digit_group != 0:
        value = '0' + value

    hex_digits = "0123456789ABCDEF"

    base_b_value_string = ""
    for index in range(0,  len(value), digit_group):
        group = value[index:index+digit_group]

        group = group[::-1]

        base_b_value = 0
        power = 1
        for char in group:
            if char == '1':
                base_b_value += power
            power *= 2

        current_value_string = ""
        if base_b_value == 0:
            base_b_value_string += '0'
        else:
            while base_b_value > 0:
                remainder = base_b_value % base
                current_value_string = hex_digits[remainder] + current_value_string
                base_b_value //= base

            base_b_value_string += current_value_string

    return base_b_value_string


def base_b_to_base_10(number, base):
    number_digit_list = string_to_digit_list(number)
    base = int(base)

    number_length = len(number_digit_list)
    base_10_value = 0

    for index in range(number_length):
        power = number_length - index - 1
        base_10_value = base_10_value + number_digit_list[index] * (base ** power)

    return base_10_value


def base_10_to_base_b(number, base):
    hex_digits = "0123456789ABCDEF"
    result = ""

    base = int(base)
    if number == 0:
        return "0"

    while number > 0:
        remainder = number % base
        result = hex_digits[remainder] + result
        number //= base

    return result


def substitution_method(number, source_base, destination_base):
    source_base = int(source_base, 10)
    source_base = format(source_base, 'X')
    destination_base = int(destination_base)
    result = "0"

    for i, digit in enumerate(reversed(number.upper())):

        power = "1"
        for _ in range(i):
            power = multiplication_by_one_digit(power, str(source_base), destination_base)

        term = multiplication_by_one_digit(power, digit, destination_base)
        result = digit_list_to_string(addition(str(result), term, destination_base))

    return result


def successive_divisions_method(number, source_base, destination_base):
    destination_base = int(destination_base, 10)
    destination_base = format(destination_base, 'X')
    source_base = int(source_base)
    result = ""

    quotient = number

    while quotient != "0":
        quotient, remainder = division_by_one_digit(quotient, destination_base, source_base)
        quotient = digit_list_to_string(quotient)
        result = dictionary[remainder] + result

    return result
