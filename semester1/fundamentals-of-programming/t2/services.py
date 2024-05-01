from src.repository import TextFileRepository


class Services:
    def __init__(self):
        self.__players_repository = TextFileRepository("text.txt")

    def retrieve_all_players(self):
        return self.__players_repository.player_list

    @staticmethod
    def get_power_of_two(number):
        power_of_two = 1
        while power_of_two * 2 < number:
            power_of_two *= 2

        return power_of_two

    def update_list(self, new_players_list):
        self.__players_repository.player_list = new_players_list