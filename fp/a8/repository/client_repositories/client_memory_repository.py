from random import randint, choice
from src.domain.client import Client


class ClientMemoryRepository:
    def __init__(self):
        self.__client_data = self.generated_clients(20)

    @property
    def client_list(self):
        return self.__client_data[:]

    @client_list.setter
    def client_list(self, other):
        self.__client_data = other

    def add_client(self, new_client: Client):
        self.__client_data.append(new_client)

    def remove_client(self, client_id: int):
        self.__client_data = [client for client in self.__client_data if client.client_id != client_id]

    def find_client(self, search_key, **kwargs):
        client_list = []
        for client in self.__client_data:
            if kwargs['search_criteria'] == 'client_id' and search_key == client.client_id:
                client_list.append(client)
            if kwargs['search_criteria'] == 'name' and search_key.lower() in client.name.lower():
                client_list.append(client)

        return client_list

    def update_client(self, client: Client):
        for i, existing_client in enumerate(self.client_list):
            if existing_client.client_id == client.client_id:
                self.__client_data[i] = client

    @staticmethod
    def generated_clients(number_of_clients_to_generate):
        clients_list = []
        lower_bound = 1
        upper_bound = 100
        names = [
            "Liam", "Emma", "Noah", "Olivia", "William", "Ava",
            "James", "Isabella", "Logan", "Sophia", "Benjamin",
            "Mia", "Mason", "Charlotte", "Elijah", "Amelia",
            "Oliver", "Evelyn", "Jacob", "Abigail"
        ]
        while number_of_clients_to_generate > 0:
            client_id = randint(lower_bound, upper_bound)
            client_name = choice(names)

            if not any(client_id == client.client_id for client in clients_list):
                new_client = Client(client_id, client_name)
                clients_list.append(new_client)
                number_of_clients_to_generate -= 1

        return clients_list
