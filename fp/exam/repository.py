from random import randint, choice
import numpy as np
from texttable import Texttable


class Repository:
    def __init__(self):
        # nothing = 0, asteroids = 1, alien = 2,
        self.board = np.zeros((7, 7), int)
        self.alien_ships_coordinates = []
        self.generate_board()
        self.working_alien_ships = 2

    def get_alien_ship_coordinates(self):
        return self.alien_ships_coordinates[:]

    def generate_board(self):
        self.board[3][3] = 4  # Earth
        asteroids_generated = 0
        while asteroids_generated != 8:
            asteroid_line = randint(0, 6)
            asteroid_col = randint(0, 6)

            if (not (asteroid_line == 3 and asteroid_col == 3) and self.board[asteroid_line][asteroid_col] == 0
                    and self.check_neighbors(asteroid_line, asteroid_col)):
                self.board[asteroid_line][asteroid_col] = 1
                asteroids_generated += 1

        alien_ships_generated = 0
        while alien_ships_generated != 2:
            alien_ship_line = choice([0, 6])
            alien_ship_col = choice([0, 6])

            if self.board[alien_ship_line][alien_ship_col] == 0:
                self.alien_ships_coordinates.append((alien_ship_line, alien_ship_col))
                self.board[alien_ship_line][alien_ship_col] = 2
                alien_ships_generated += 1

    def check_neighbors(self, asteroid_line, asteroid_col):
        coordinates_set = [(-1, -1), (-1, 0), (-1, 1), (0, -1), (0, 1), (1, -1), (1, 0), (1, 1)]

        for coordinates in coordinates_set:
            coordinates_to_check = (asteroid_line + coordinates[0], asteroid_col + coordinates[1])
            if coordinates_to_check[0] in range(0, 7) and coordinates_to_check[1] in range(0, 7):
                if self.board[coordinates_to_check[0]][coordinates_to_check[1]] == 1:
                    return 0

        return 1

    def display_board(self, display_aliens):
        if display_aliens == 1:  # display them
            board_dict = {-2: " ", -1: "-", 0: "", 1: "*", 2: "X", 3: "-", 4: "E"}
        else:
            board_dict = {-2: " ", -1: "-", 0: "", 1: "*", 2: "", 3: "-", 4: "E"}

        board_display = Texttable()
        board_display.header([" ", "A", "B", "C", "D", "E", "F", "G"])

        for row in range(7):
            new_row = list(self.board[row])
            another_row = []
            another_row.append(row + 1)
            for element in new_row:
                element = board_dict[element]
                another_row.append(element)
            board_display.add_row(another_row)

        print(board_display.draw())

    def attack_at(self, line, col):
        if self.board[line][col] == 1:  # asteroid
            return 0
        if self.board[line][col] == 3:  # already fired upon
            return 0
        if self.board[line][col] == 2:
            self.board[line][col] = 3  # alien ship down
            self.working_alien_ships -= 1

            for coordinates in self.alien_ships_coordinates:
                if (line, col) == coordinates:
                    self.alien_ships_coordinates.remove(coordinates)

            if self.working_alien_ships == 0:
                self.display_board(1)
                return 3  # player wins
            else:
                self.display_board(0)
                return 1  # downed ship, game still on

        if self.board[line][col] == 0:  # nothing
            self.board[line][col] = 3
            self.display_board(0)
            return 2

    def move_alien_ships(self):
        #print(self.get_alien_ship_coordinates())
        for coordinates in self.alien_ships_coordinates:
            #print(coordinates)
            #self.alien_ships_coordinates.remove(coordinates)

            if coordinates[0] in [0, 1, 2, 3]:
                delta_line = 1
            else:
                delta_line = -1

            if coordinates[1] in [0, 1, 2, 3]:
                delta_col = 1
            else:
                delta_col = -1

            potential_moves = [(coordinates[0] + delta_line, coordinates[1]), (coordinates[0], coordinates[1] + delta_col),
                               (coordinates[0] + delta_line, coordinates[1] + delta_col), (coordinates[0], coordinates[1])]

            move = choice(potential_moves)
            while self.board[move[0]][move[1]] != 0:
                move = choice(potential_moves)

            #print(move)

            self.board[coordinates[0]][coordinates[1]] = -2
            self.board[move[0]][move[1]] = 2

            # print(f"({coordinates[0]}, {coordinates[1]} -> ({move[0]}, {move[1]}")

    def get_neighbors_of_earth(self):
        coordinates_set = [(-1, -1), (-1, 0), (-1, 1), (0, -1), (0, 1), (1, -1), (1, 0), (1, 1)]
        earth_coordinates = (3, 3)
        neighbors_of_earth = []

        for coordinates in coordinates_set:
            neighbors_of_earth.append((self.board[earth_coordinates[0] + coordinates[0]][earth_coordinates[1] + coordinates[1]]))

        return neighbors_of_earth





