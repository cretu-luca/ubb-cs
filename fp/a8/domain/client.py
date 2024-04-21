class Client:
    def __init__(self, client_id: int, name: str):
        self.__client_id = client_id
        self.__name = name

    @property
    def client_id(self):
        return self.__client_id

    @client_id.setter
    def client_id(self, new_client_id):
        self.__client_id = new_client_id

    @property
    def name(self):
        return self.__name

    @name.setter
    def name(self, new_name):
        self.__name = new_name

    @property
    def to_string(self):
        return (f"Client ID: {self.__client_id}\n"
                f"Name: {self.__name}\n")

    @property
    def to_dictionary(self):
        return {
            'Client ID': self.__client_id,
            'Name': self.__name
        }
