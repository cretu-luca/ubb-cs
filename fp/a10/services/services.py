from src.repository.board_repository import Board
from numpy import zeros


class Services:
    def __init__(self):
        self.__computer_player_board_repository = Board()
        self.__computer_player_board_repository.generate_board()
        self.__human_player_board_repository = Board()
        self.__default_board_repository = Board()
        self.__AI_board_repository = Board()
        self.__AI_board_repository.create_ai_board()
        self.__attacked_coordinates = []

    def display_board_service(self, board_to_display):
        if board_to_display == "computer_player_board_with_hits":
            return self.__computer_player_board_repository.display_board(show_planes=False, hits="displayed")
        elif board_to_display == "computer_player_board":
            return self.__computer_player_board_repository.display_board(show_planes=False, hits="hidden")
        elif board_to_display == "human_player_board_with_hits":
            return self.__human_player_board_repository.display_board(show_planes=True, hits="displayed")
        elif board_to_display == "human_player_board":
            return self.__human_player_board_repository.display_board(show_planes=True, hits="hidden")

    def generate_board_service(self, board_to_generate):
        if board_to_generate == "computer_player_board":
            self.__computer_player_board_repository.generate_board()
        else:
            self.__human_player_board_repository.generate_board()

    def get_plane_coordinates_service(self, cockpit_coordinates, orientation):
        return self.__default_board_repository.get_plane_coordinates(cockpit_coordinates, orientation)

    def configure_board_service(self, **kwargs):
        if 'line' in kwargs:
            self.__human_player_board_repository.configure_board((kwargs['line'], kwargs['column']),
                                                                 kwargs['orientation_selected'], kwargs['number_of_planes_known'])
        else:
            self.__human_player_board_repository.generate_board()

    def get_human_player_board_state(self):
        return self.__human_player_board_repository.matrix_with_hits

    def get_computer_player_board_state(self):
        return self.__computer_player_board_repository.matrix_with_hits

    def check_friendly_plane_collision(self, plane_coordinates):
        for coordinate in plane_coordinates:
            if self.__human_player_board_repository.matrix[coordinate[0]][coordinate[1]]:
                return False

        return True

    def handle_attack_by_human_service(self, line, column):

        attacked_plane, attack_outcome, enemy_planes_left, board_with_hits = self.__computer_player_board_repository.handle_attack(line, column)
        attack_outcome_string = attack_outcome + "\n" + f"Your enemy has {enemy_planes_left} functioning planes left!"

        return attack_outcome_string, enemy_planes_left

    def handle_attack_by_computer_service(self):
        maximum, line, column = self.find_maximum()
        attacked_plane, attack_outcome, enemy_planes_left, board_with_hits = self.__human_player_board_repository.handle_attack(line, column)
        self.__AI_board_repository.update_ai_board(line, column, attacked_plane, attack_outcome)

        attack_outcome_string = f"Enemy attacked at {chr(int(str(line+1)) + 64), column + 1}\n" + attack_outcome + "\n" + f"You have {enemy_planes_left} functioning planes left!"

        return attack_outcome_string, enemy_planes_left

    def find_maximum(self):
        board_size = 10
        maximum = float('-inf')
        line_with_maximum = 0
        column_with_maximum = 0
        for i in range(board_size):
            for j in range(board_size):
                if self.__AI_board_repository.matrix[i][j] > maximum and (i, j) not in self.__attacked_coordinates:
                    maximum = self.__AI_board_repository.matrix[i][j]
                    line_with_maximum = i
                    column_with_maximum = j
                    if (maximum == self.__AI_board_repository.matrix[i][j] and
                            (self.__human_player_board_repository.matrix[i + 1][j] == 5 or
                             self.__human_player_board_repository.matrix[i - 1][j] == 5 or
                             self.__human_player_board_repository.matrix[i][j + 1] == 5 or
                             self.__human_player_board_repository.matrix[i][j - 1] == 5)):
                        line_with_maximum = i
                        column_with_maximum = j

        self.__attacked_coordinates.append((line_with_maximum, column_with_maximum))
        return maximum, line_with_maximum, column_with_maximum

    @staticmethod
    def check_coordinates_validity(plane_coordinates):
        board_size = 10
        for coordinate in plane_coordinates:
            if not 0 <= coordinate[0] < board_size or not 0 <= coordinate[1] < board_size:
                return False

        return True