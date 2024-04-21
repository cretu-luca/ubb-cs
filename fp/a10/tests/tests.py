from unittest import TestCase

import numpy

from src.repository.board_repository import Board
from src.services.services import Services


class Test(TestCase):
    def setUp(self):
        self.__board = Board()
        self.__services = Services()
        self.__services.configure_board_service(line=5, column=5, orientation_selected='u', number_of_planes_known=1)

    def test_add_plane(self):
        human_board = self.__services.get_human_player_board_state()
        self.assertTrue(human_board[5][5] == 1)

    def test_hit_plane(self):
        attacked_plane, attack_outcome, enemy_planes_left, board_with_hits = self.__board.handle_attack(5, 5)
        self.assertTrue(board_with_hits[5][5] == 4)

    def test_miss_plane(self):
        self.__services.configure_board_service(line=3, column=3, orientation_selected='u', number_of_planes_known=1)
        attack_outcome, board = self.__services.handle_attack_by_human_service(9, 9)
        self.assertIn("No plane was hit", attack_outcome)

    def test_coordinate_validity(self):
        plane_coordinates = self.__services.get_plane_coordinates_service((5, 5), 'u')
        coordinates_validity = self.__services.check_coordinates_validity(plane_coordinates)
        self.assertTrue(coordinates_validity)

        plane_coordinates = self.__services.get_plane_coordinates_service((1, 1), 'u')
        coordinates_validity = self.__services.check_coordinates_validity(plane_coordinates)
        self.assertFalse(coordinates_validity)

    def test_friendly_plane_collision(self):
        plane_coordinates = self.__services.get_plane_coordinates_service((5, 4), 'u')
        plane_collision = self.__services.check_friendly_plane_collision(plane_coordinates)
        self.assertFalse(plane_collision)

    def test_generate(self):
        self.__generated_board = Board()
        self.__generated_board.generate_board()
        self.assertTrue(len(self.__generated_board.planes) == 3)