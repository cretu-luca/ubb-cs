from repository import Repository
from service import Service


class UI:
    def __init__(self, service):
        self.service = service
        self.cheat = 0
        while True:
            self.main_ui_menu()

    def main_ui_menu(self):
        if self.service.check_neighbors_of_earth() == 0:
            print("An alien ship got too close to Earth, you lost the game!")
        else:

            print("This is the board: ")
            self.service.display_board_service(self.cheat)

            command = input("Enter the attack coordinates: \n")
            command = command.split(" ")

            val_dict = {"A": 0, "B": 1, "C": 2, "D": 3, "E": 4, "F": 5, "G": 6}

            if command[0] == "cheat":
                self.cheat = 1
            else:
                col = val_dict[command[1][0]]
                line = int(command[1][1]) - 1

                attack_result = self.service.attack_at_service(line, col)
                if attack_result == 0:
                    print("You made an illegal move, try again!")
                if attack_result == 1:
                    print("You hit an alien ship!")
                elif attack_result == 2:
                    print("You did not hit anything!")
                elif attack_result == 3:
                    print("You won!")
                    exit(0)

                if attack_result in [1, 2]:
                    self.service.move_alien_ships_service()


ui = UI(Service(Repository()))
ui.main_ui_menu()
