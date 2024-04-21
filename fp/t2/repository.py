from src.domain import Player


class TextFileRepository:
    def __init__(self, file_path):
        self.__player_data = []
        self.__file_path = file_path
        self.__read_from_file()

    @property
    def player_list(self):
        return self.__player_data[:]

    @player_list.setter
    def player_list(self, other):
        self.__player_data = other

    def __read_from_file(self):
        file = open(self.__file_path, 'r')

        line_in_file = file.readline()
        while line_in_file != "":
            line_in_file = line_in_file.split(",")
            id = int(line_in_file[0])
            name = line_in_file[1]
            strength = int(line_in_file[2])

            player = Player(id, name, strength)

            self.__player_data.append(player)

            line_in_file = file.readline()

