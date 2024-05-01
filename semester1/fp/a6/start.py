from functions import generate_expenses, interpret_user_input
from ui import read_user_input, display_commands

#
# This module is used to invoke the program's UI and start it. It should not contain a lot of code.
#


def start():
    expenses = list()
    expenses_history = list()
    generate_expenses(15, expenses, expenses_history)

    while True:
        display_commands()
        user_input = read_user_input()
        interpret_user_input(user_input, expenses, expenses_history)


start()