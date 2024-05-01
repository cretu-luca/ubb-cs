from numpy import zeros
from random import choice
from src.domain.plane import Plane


class Board:
    def __init__(self):
        self.__board = zeros((15, 15))
        self.__board_with_hits = zeros((15, 15))
        self.planes = []
        self.__all_planes = []
        self.__functioning_planes = 3

    @property
    def matrix(self):
        return self.__board

    @matrix.setter
    def matrix(self, other):
        self.__board = other

    @property
    def matrix_with_hits(self):
        return self.__board

    @matrix_with_hits.setter
    def matrix_with_hits(self, other):
        self.__board = other

    def display_ai_board(self):
        board_size = 10
        matrix = ""
        for i in range(0, board_size):
            row = ""
            for j in range(0, board_size):
                row += str(int(self.__board[i][j])) + " "
            matrix += row + '\n'
        return matrix

    def create_ai_board(self):
        self.__all_planes = self.all_possible_planes()

    def display_board(self, **kwargs):
        board_size = 10
        no_hit_point = 4
        hit_point = 5
        board_string = "    1  2  3  4  5  6  7  8  9  10\n"
        attacked_areas = {no_hit_point: 'o', hit_point: 'x'}

        for i in range(board_size):
            row = f' {chr(int(str(i + 1)) + 64)} '
            for j in range(board_size):
                if self.__board_with_hits[i][j] in [no_hit_point, hit_point]:
                    row += f' {attacked_areas[int(self.__board_with_hits[i][j])]} '
                elif kwargs['show_planes'] and self.__board[i][j] in [1, 2, 3]:
                    row += f' {int(self.__board[i][j])} '
                else:
                    row += ' _ '

            board_string += row + '\n'

        return board_string

    def configure_board(self, cockpit_coordinates, plane_orientation, plane_identifier):
        plane_codes = [1, 2, 3]
        plane_coordinates = self.get_plane_coordinates(cockpit_coordinates, plane_orientation)
        if plane_identifier in plane_codes:
            self.planes.append(Plane(plane_coordinates, plane_orientation))
        for plane_coordinate in plane_coordinates:
            self.__board[int(plane_coordinate[0])][int(plane_coordinate[1])] = plane_identifier

    def configure_board_with_hits(self, cockpit_coordinates, plane_orientations, plane_identifier, **kwargs):
        plane_coordinates = [cockpit_coordinates]
        if kwargs['downed'] == 'yes':
            plane_coordinates = self.get_plane_coordinates(cockpit_coordinates, plane_orientations)
        for plane_coordinate in plane_coordinates:
            self.__board_with_hits[int(plane_coordinate[0])][int(plane_coordinate[1])] = plane_identifier

    @staticmethod
    def check_coordinates_validity(plane_coordinates):
        board_size = 10
        for coordinate in plane_coordinates:
            if not 0 <= coordinate[0] < board_size or not 0 <= coordinate[1] < board_size:
                return False

        return True

    def all_possible_planes(self):
        board_size = 10
        planes = []
        for i in range(0, board_size):
            for j in range(0, board_size):
                for orientation in ['u', 'r', 'd', 'l']:
                    plane_coordinates = self.get_plane_coordinates((i, j), orientation)
                    if self.check_coordinates_validity(plane_coordinates):
                        self.__board[i][j] += 1
                        plane = Plane(plane_coordinates, orientation)
                        planes.append(plane)

        return planes

    def valid_coordinate(self, line, column):
        return self.__board[line][column] >= 0

    def update_ai_board(self, line, column, attacked_plane, hit_type):
        chance_of_one = 1
        self.__board[line][column] = -chance_of_one
        if hit_type == "1 plane hit and downed!":
            if self.__board[line-1][column]:
                self.__board[line-1][column] += chance_of_one
            if self.__board[line+1][column]:
                self.__board[line+1][column] += chance_of_one
            if self.__board[line][column-1]:
                self.__board[line][column-1] += chance_of_one
            if self.__board[line][column+1]:
                self.__board[line][column+1] += chance_of_one
            for coordinate in attacked_plane.coordinates:
                self.__board[coordinate[0]][coordinate[1]] = 0

            if attacked_plane in self.__all_planes:
                self.__all_planes.remove(attacked_plane)

        elif hit_type == "1 plane hit, but not downed!":
            self.__board[line][column] = -100
            if self.__board[line-1][column]:
                self.__board[line-1][column] += chance_of_one
            if self.__board[line+1][column]:
                self.__board[line+1][column] += chance_of_one
            if self.__board[line][column-1]:
                self.__board[line][column-1] += chance_of_one
            if self.__board[line][column+1]:
                self.__board[line][column+1] += chance_of_one

        elif hit_type == "No plane was hit!":
            self.__board[line][column] = -100
            for plane in self.__all_planes:
                if (line, column) in plane.coordinates:
                    self.__board[plane.cockpit_coordinates[0]][plane.cockpit_coordinates[1]] -= chance_of_one
                    self.__all_planes.remove(plane)

    def handle_attack(self, line, column):
        if self.__board[line][column]:
            attacked_plane = None
            for plane in self.planes:
                if (line, column) in plane.coordinates:
                    attacked_plane = plane
                    break

            if attacked_plane:
                if (line, column) == attacked_plane.cockpit_coordinates:
                    self.__functioning_planes -= 1
                    orientation = attacked_plane.orientation
                    self.configure_board((line, column), orientation, 6)
                    self.configure_board_with_hits((line, column), orientation, 6, downed='yes')
                    self.planes.remove(attacked_plane)
                    attack_outcome = "1 plane hit and downed!"

                    return attacked_plane, attack_outcome, self.__functioning_planes, self.__board_with_hits
                else:
                    self.__board_with_hits[line][column] = 5
                    attack_outcome = "1 plane hit, but not downed!"

                    return attacked_plane, attack_outcome, self.__functioning_planes, self.__board_with_hits

        attacked_plane = None
        attack_outcome = "No plane was hit!"
        self.__board_with_hits[line][column] = 4

        return attacked_plane, attack_outcome, self.__functioning_planes, self.__board_with_hits

    def generate_board(self):
        board_size = 10
        maximum_number_of_tries = 150
        available_coordinates = []

        for i in range(0, board_size):
            for j in range(0, board_size):
                available_coordinates.append((i, j))

        planes_number = 0
        tries = 0
        while planes_number != 3:
            tries += 1
            valid_coordinates = True
            cockpit_coordinates = choice(available_coordinates)
            orientation = choice(['u', 'd', 'r', 'l'])
            plane_coordinates = self.get_plane_coordinates(cockpit_coordinates, orientation)

            for coordinates in plane_coordinates:
                if (self.__board[coordinates[0]][coordinates[1]] or not (0 <= coordinates[0] < board_size) or
                        not (0 <= coordinates[1] < board_size)):
                    valid_coordinates = False

            if valid_coordinates:
                plane = Plane(plane_coordinates, orientation)
                self.planes.append(plane)
                planes_number += 1
                for coordinates in plane_coordinates:
                    self.__board[coordinates[0]][coordinates[1]] = planes_number
                    available_coordinates.remove(coordinates)

            if tries > maximum_number_of_tries:
                available_coordinates = []
                tries = 0
                planes_number = 0
                self.planes = []
                for i in range(0, board_size):
                    for j in range(0, board_size):
                        self.__board[i][j] = 0
                        available_coordinates.append((i, j))

    @staticmethod
    def get_plane_coordinates(cockpit_coordinates, orientation):
        transformations = {
            'u': [(0, 0), (1, -2), (1, -1), (1, 0), (1, 1), (1, 2), (2, 0), (3, -1), (3, 0), (3, 1)],
            'd': [(0, 0), (-1, -2), (-1, -1), (-1, 0), (-1, 1), (-1, 2), (-2, 0), (-3, -1), (-3, 0), (-3, 1)],
            'r': [(0, 0), (0, -1), (-1, -1), (-2, -1), (1, -1), (2, -1), (0, -2), (-1, -3), (0, -3), (1, -3)],
            'l': [(0, 0), (-2, 1), (-1, 1), (0, 1), (1, 1), (2, 1), (0, 2), (-1, 3), (0, 3), (1, 3)]
        }

        return [(cockpit_coordinates[0] + vertical_direction, cockpit_coordinates[1] + horizontal_direction)
                for vertical_direction, horizontal_direction in transformations[orientation]]