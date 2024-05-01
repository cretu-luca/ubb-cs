from src.repository.client_repositories.client_memory_repository import ClientMemoryRepository
from src.domain.client import Client


class ClientTextFileRepository(ClientMemoryRepository):
    def __init__(self, file_path):
        super().__init__()
        self.client_list = []
        self.file_path = file_path
        self.read_from_file()

    def read_from_file(self):
        client_id_index = 0
        name_index = 1

        file = open(self.file_path, 'r')
        current_line_in_file = file.readline()

        while current_line_in_file != "":
            current_line_in_file = current_line_in_file.strip().split(',')
            client_id = int(current_line_in_file[client_id_index])
            name = current_line_in_file[name_index]

            self.add_client(Client(client_id, name))
            current_line_in_file = file.readline()

        file.close()

    def write_to_file(self):
        with open(self.file_path, 'w') as file:
            file.truncate(0)

        file = open(self.file_path, 'w')
        client_list = self.client_list

        for client in client_list:
            file.write(str(client.client_id) + "," + client.name)
            file.write('\n')

        file.close()
