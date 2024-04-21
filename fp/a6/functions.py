from re import findall
from random import randint, choice
from ui import (display_table, display_incorrect_command_format_error, display_undo_error,
                display_unexisting_command_error)
import copy

#
# The program's functions are implemented here. There is no user interaction in this file,
# therefore no input/print statements. Functions here
# communicate via function parameters, the return statement and raising of exceptions.
#


def generate_expenses(number_of_expenses, expenses, expenses_history):
    first_day, last_day = 1, 30
    smallest_money_amount, largest_money_amount = 1, 100

    while number_of_expenses > 0:
        day = randint(first_day, last_day)
        amount_of_money = randint(smallest_money_amount, largest_money_amount)
        category = choice(["housekeeping", "food", "transport", "clothing", "internet", "others"])
        expenses.append({"day": day, "amount_of_money": amount_of_money, "category": category})
        number_of_expenses -= 1

    expenses_history.append(expenses)


def add_expense_to_current_date(user_input, expenses, categories):
    add_expense_command_length = 3
    current_day = 28
    amount_of_money_index_in_command = 1
    category_index_in_command = 2

    try:
        amount_of_money = int(user_input[amount_of_money_index_in_command])
        category = str(user_input[category_index_in_command])

        assert category in categories and len(user_input) == add_expense_command_length

        expenses.append({"day": current_day, "amount_of_money": amount_of_money, "category": category})

    except ValueError:
        display_incorrect_command_format_error()
    except AssertionError:
        display_incorrect_command_format_error()


def insert_expense_at_given_date(user_input, expenses, categories):
    first_day, last_day = 1, 30
    day_index_in_command = 1
    amount_of_money_index_in_command = 2
    category_index_in_command = 3
    insert_expense_command_length = 4

    try:
        day = int(user_input[day_index_in_command])
        amount_of_money = int(user_input[amount_of_money_index_in_command])
        category = str(user_input[category_index_in_command])

        assert len(user_input) == insert_expense_command_length and category in categories and first_day <= day <= last_day

        expenses.append({"day": day, "amount_of_money": amount_of_money, "category": category})

    except ValueError:
        display_incorrect_command_format_error()
    except AssertionError:
        display_incorrect_command_format_error()


def handle_removal(user_input, expenses, categories):
    first_day, last_day = 1, 30
    remove_category_or_day_command_length = 2
    remove_day_range_command_length = 4
    category_or_day_index_in_command = 1

    if (len(user_input) == remove_category_or_day_command_length and
            not any(char.isdigit() for char in user_input[category_or_day_index_in_command])):  # remove <category>
        category_index_in_command = 1
        try:
            category = str(user_input[category_index_in_command])

            assert category in categories

            remove_expense(expenses, category=category)

        except ValueError:
            display_incorrect_command_format_error()

    elif (len(user_input) == remove_category_or_day_command_length and
          any(char.isdigit() for char in user_input[category_or_day_index_in_command])):  # remove <day>
        day_index_in_command = 1
        try:
            day = int(user_input[day_index_in_command])
            remove_expense(expenses, day=day)

            assert first_day <= day <= last_day

        except ValueError:
            display_incorrect_command_format_error()

    elif len(user_input) == remove_day_range_command_length:  # remove <start_date> to <end_date>
        start_date_index_in_command = 1
        end_date_index_in_command = 3
        to_index_in_command = 2

        try:
            start_date = int(user_input[start_date_index_in_command])
            end_date = int(user_input[end_date_index_in_command])

            assert user_input[to_index_in_command] == "to"
            assert first_day <= start_date <= end_date <= last_day

            remove_expense(expenses, start_date=start_date, end_date=end_date)

        except ValueError:
            display_incorrect_command_format_error()

        except AssertionError:
            display_incorrect_command_format_error()

    else:
        display_incorrect_command_format_error()


def handle_listing(user_input, expenses, categories):
    list_all_expenses_command_length = 1
    list_category_command_length = 2
    list_expenses_by_value = 4

    if len(user_input) == list_all_expenses_command_length:
        list_expenses(expenses=expenses)

    elif len(user_input) == list_category_command_length:
        category_index_in_command = 1
        try:
            category = user_input[category_index_in_command]

            assert category in categories

            list_expenses(expenses=expenses, category=category)

        except ValueError:
            display_incorrect_command_format_error()
        except AssertionError:
            display_incorrect_command_format_error()

    elif len(user_input) == list_expenses_by_value:
        category_index_in_command = 1
        value_index_in_command = 3
        operator_index_in_command = 2

        try:
            category = str(user_input[category_index_in_command])
            value = int(user_input[value_index_in_command])

            assert user_input[operator_index_in_command] in [">", "<", "="] and category in categories

            list_expenses(expenses=expenses, value=value, operator=user_input[operator_index_in_command], category=category)

        except ValueError:
            display_incorrect_command_format_error()
        except AssertionError:
            display_incorrect_command_format_error()


def handle_filtering(user_input, expenses, categories):
    filter_category_command_length = 2
    category_index_in_command = 1
    value_index_in_command = 3
    operator_index_in_command = 2

    if len(user_input) == filter_category_command_length:
        try:
            category = str(user_input[category_index_in_command])

            assert category in categories

            filter_expense(expenses, category=category)

        except ValueError:
            display_incorrect_command_format_error()
        except AssertionError:
            display_incorrect_command_format_error()
    else:
        try:
            category = str(user_input[category_index_in_command])
            value = int(user_input[value_index_in_command])

            assert user_input[operator_index_in_command] in ["<", ">", "="] and category in categories

            filter_expense(expenses, operator=user_input[operator_index_in_command], category=category, value=value)

        except ValueError:
            display_incorrect_command_format_error()
        except AssertionError:
            display_incorrect_command_format_error()


def interpret_user_input(user_input: str, expenses, expenses_history):
    command_index_in_command = 0

    categories = ["housekeeping", "food", "transport", "clothing", "internet", "others"]

    user_input = findall(r"[a-zA-Z]+|\d+|[><=]", user_input)

    command = ""

    try:
        command = user_input[command_index_in_command]
    except IndexError:
        display_incorrect_command_format_error()

    command_functions = {
        "add": add_expense_to_current_date,
        "insert": insert_expense_at_given_date,
        "remove": handle_removal,
        "list": handle_listing,
        "filter": handle_filtering,
        "undo": undo
    }

    try:
        if command == "exit":
            exit(0)
        if command == "undo":
            undo(expenses_history, expenses)
        else:
            if command != "list":
                expenses_history.append(copy.deepcopy(expenses))
            command_functions[command](user_input, expenses, categories)

    except KeyError:
        display_unexisting_command_error()


def list_expenses(**kwargs):
    expenses_table = list()

    if "value" in kwargs:
        for expense in kwargs["expenses"]:
            if compare(kwargs["value"], expense["amount_of_money"], kwargs["operator"]) and expense["category"] == kwargs["category"]:
                expenses_table.append([expense["day"], expense["amount_of_money"], expense["category"]])

        display_table(expenses_table)

    elif "category" in kwargs:
        for expense in kwargs["expenses"]:
            if expense["category"] == kwargs["category"]:
                expenses_table.append([expense["day"], expense["amount_of_money"], expense["category"]])

        display_table(expenses_table)

    else:
        for expense in kwargs["expenses"]:
            expenses_table.append([expense["day"], expense["amount_of_money"], expense["category"]])

        display_table(expenses_table)


def remove_expense(expenses, **kwargs):
    if "category" in kwargs:
        for expense in list(expenses):
            if expense["category"] == kwargs["category"]:
                expenses.remove(expense)

    if "day" in kwargs:
        for expense in list(expenses):
            if expense["day"] == kwargs["day"]:
                expenses.remove(expense)

    if "start_date" in kwargs and "end_date" in kwargs:
        for expense in list(expenses):
            if kwargs["start_date"] <= expense["day"] <= kwargs["end_date"]:
                expenses.remove(expense)


def compare(value1: int, value2: int, operator: chr):
    if operator == '>':
        return value1 < value2
    if operator == '<':
        return value1 > value2
    if operator == '=':
        return value1 == value2


def filter_expense(expenses, **kwargs):
    if "value" in kwargs:
        for expense in list(expenses):
            if expense['category'] == kwargs['category']:
                if compare(expense["amount_of_money"], kwargs["value"], kwargs["operator"]):
                    expenses.remove(expense)
            else:
                expenses.remove(expense)

    else:
        for expense in list(expenses):
            if expense["category"] != kwargs["category"]:
                expenses.remove(expense)


def undo(expenses_history, expenses):
    if len(expenses_history) > 1:
        last_state = expenses_history.pop()
        expenses.clear()
        expenses.extend(last_state)
    else:
        display_undo_error()
