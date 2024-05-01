from unittest import TestCase
import numpy as np
from service import Service
from repository import Repository


class TestFire(TestCase):
    def setUp(self):
        self.repository = Repository()

    def test_fire_functionality_downed_ship(self):
        coordinates = self.repository.get_alien_ship_coordinates()

        attack_outcome = self.repository.attack_at(coordinates[0][0], coordinates[0][1])
        self.assertTrue(attack_outcome == 1)

    def test_fire_functionality_game_won(self):
        coordinates = self.repository.get_alien_ship_coordinates()
        attack_1_outcome = self.repository.attack_at(coordinates[0][0], coordinates[0][1])
        attack_2_outcome = self.repository.attack_at(coordinates[1][0], coordinates[1][1])

        self.assertTrue(attack_1_outcome == 1)
        self.assertTrue(attack_2_outcome == 3)

    def test_fire_functionality_no_hit(self):
        attack_outcome = self.repository.attack_at(3, 4)

        self.assertTrue(attack_outcome in [0, 2])
