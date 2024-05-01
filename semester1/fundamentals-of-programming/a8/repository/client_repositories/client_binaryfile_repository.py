import pickle
from src.repository.client_repositories.client_memory_repository import ClientMemoryRepository
from src.domain.client import Client


class ClientBinaryFileRepository(ClientMemoryRepository):
    def __init__(self, file_path):
        super().__init__()
        self.client_list = []
        self.file_path = file_path
        self.read_from_file()

    def read_from_file(self):
        client_id_index = 0
        client_name_index = 1

        file = open(self.file_path, 'rb')
        client_information = pickle.load(file)

        for client_object in client_information:
            client_object = client_object.split(',')
            client_id = int(client_object[client_id_index])
            client_name = client_object[client_name_index]

            client_data_from_file = Client(client_id, client_name)
            self.add_client(client_data_from_file)

        file.close()

    def write_to_file(self):
        file = open(self.file_path, 'wb')
        file.truncate(0)
        client_information = []
        for client in self.client_list:
            client_string = str(client.client_id) + "," + client.name
            client_information.append(client_string)
        pickle.dump(client_information, file)
        file.close()
