class Player:
    def __init__(self, id, name, strength):
        self.__id = id
        self.__name = name
        self.__strength = strength

    @property
    def id(self):
        return self.__id

    @property
    def name(self):
        return self.__name

    @property
    def strength(self):
        return self.__strength

    @strength.setter
    def strength(self, other):
        self.__strength = other

    @property
    def to_string(self):
        string = ""
        string += (f"ID: {self.__id}\n"
                   f"Name: {self.__name}\n"
                   f"Strength: {self.__strength}\n")
        string += '\n'

        return string