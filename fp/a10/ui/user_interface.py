from src.ui.ui_exception import UiException
from src.services.services import Services


class UserInterface:
    def __init__(self):
        self.__services = Services()
        self.main_menu()

    def main_menu(self):
        self.__configure_human_board_ui()
        self.__handle_guessing_ui()

    def __configure_human_board_ui(self):
        maximum_number_of_planes = 3
        print("1. Choose your own planes on the board.\n"
              "2. Generate randomly your plane coordinates.")
        option = int(input("> "))
        number_of_planes_known = 0
        if option == 1:
            while number_of_planes_known < maximum_number_of_planes:
                print(self.__services.display_board_service("human_player_board"))
                print("'u' - upwards\n"
                      "'r' - rightwards\n"
                      "'d' - downwards\n"
                      "'l' - leftwards\n")
                orientation_selected = input(
                    f"Enter the orientation of the plane {number_of_planes_known + 1}: \n> ").lower()
                if orientation_selected not in ['u', 'r', 'd', 'l']:
                    print("Invalid plane orientation! Please enter a valid orientation.")
                    continue

                line = self.get_line_input()
                column = self.get_column_input()

                plane_coordinates = self.__services.get_plane_coordinates_service((line, column), orientation_selected)
                if not self.__services.check_coordinates_validity(plane_coordinates):
                    print("Invalid plane coordinates! Please enter valid coordinates.")
                    continue

                if not self.__services.check_friendly_plane_collision(plane_coordinates):
                    print("Planes are colliding! Please enter different coordinates.")
                    continue

                number_of_planes_known += 1
                self.__services.configure_board_service(line=line, column=column,
                                                        orientation_selected=orientation_selected,
                                                        number_of_planes_known=number_of_planes_known)
                print("Plane added successfully.")
        elif option == 2:
            self.__services.generate_board_service("human_player_board")
        else:
            print("Invalid input! Please select option 1 or 2.")

        print("This is your board: \n")
        print(self.__services.display_board_service("human_player_board"))

    def __handle_guessing_ui(self):
        while True:
            print("Launch your attack on the enemy's board!\n")
            print(self.__services.display_board_service("computer_player_board_with_hits"))

            line = self.get_line_input()
            column = self.get_column_input()

            if not self.__services.check_coordinates_validity([(line, column)]):
                raise UiException("Invalid attack coordinates!")

            print(f"You attacked at {chr(int(str(line+1)) + 64), column + 1}")
            attack_outcome, planes_left = self.__services.handle_attack_by_human_service(line, column)
            print(attack_outcome, '\n\n\n\n\n')

            if planes_left == 0:
                print("You won!")
                print(self.__services.display_board_service("computer_player_board_with_hits"))
                exit(0)
            print("\n\n\n\nYour board: ")
            attack_outcome, planes_left = self.__services.handle_attack_by_computer_service()
            print(attack_outcome)
            print(self.__services.display_board_service("human_player_board_with_hits"))

            if planes_left == 0:
                print("The computer won!")
                print(self.__services.display_board_service("human_player_board_with_hits"))
                exit(0)
            print("\n\n\n\n")

    @staticmethod
    def get_line_input():
        while True:
            line_input = input("Enter the line on which you deploy your attack: (A,B..J) \n> ").upper()

            if len(line_input) == 1 and line_input in 'ABCDEFGHIJ':
                return ord(line_input) - ord('A')
            else:
                print("Invalid input. Please enter a single letter from A to J.")

    @staticmethod
    def get_column_input():
        board_size = 9
        while True:
            try:
                column_input = input("Enter the column on which you place your plane: (1-10) \n> ")
                column = int(column_input) - 1
                if 0 <= column <= board_size:
                    return column
                else:
                    print("Invalid input. Please enter a number from 1 to 10.")
            except ValueError:
                print("Invalid input. Please enter an integer.")


if __name__ == "__main__":
    UI = UserInterface()