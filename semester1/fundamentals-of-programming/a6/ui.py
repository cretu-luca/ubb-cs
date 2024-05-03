
#
# This is the program's UI module. The user interface and all interaction with the user (print and input statements)
# are found here
#


def read_user_input():
    user_input = str(input("enter command:\n> "))
    return user_input


def display_commands():
    print("These are the available commands:\n")
    print(f"1. Add a new expense:\n"
          f"> add <sum> <category>\n"
          f"> insert <day> <sum> <category\n\n"
          f"2. Modify expenses:\n"
          f"> remove <day>\n"
          f"> remove <start day> to <end day>\n"
          f"> remove <category>\n\n"
          f"3. Display expenses with different properties\n"
          f"> list\n"
          f"> list <category>\n"
          f"> list <category> [ < | = | > ] <value>\n\n"
          f"4. Filter expenses:\n"
          f"> filter <category>\n"
          f"> filter <category> [ < | = | > ] <value>\n\n"
          f"5. Undo:\n"
          f"> undo\n\n"
          f"6. Exit\n"
          f"> exit\n")


def display_table(expenses: list):
    header_format = "{:<10} | {:<10} | {:<10}"
    headers = ["Day", "Price", "Category"]
    print(header_format.format(*headers))
    print("------------------------------------")

    for expense in expenses:
        expense_str = [str(item) for item in expense]
        print(header_format.format(*expense_str))

    print('\n\n')


def display_incorrect_command_format_error():
    print("\nIncorrect command format\n")


def display_undo_error():
    print("\nYou can't undo, there are no previous version of the expenses list.\n")


def display_unexisting_command_error():
    print("\nThe command you entered does not exist.\n")