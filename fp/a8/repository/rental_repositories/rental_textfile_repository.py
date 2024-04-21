from src.repository.rental_repositories.rental_memory_repository import RentalMemoryRepository
from src.domain.rental import Rental
from datetime import datetime


class RentalTextFileRepository(RentalMemoryRepository):
    def __init__(self, file_path, movie_repository, client_repository):
        super().__init__(movie_repository, client_repository)
        self.rental_list = []
        self.file_path = file_path
        self.read_from_file()

    def read_from_file(self):
        rental_id_index = 0
        movie_id_index = 1
        client_id_index = 2
        rental_date_index = 3
        due_date_index = 4
        returned_date_index = 5
        returned_in_time_index = 6

        file = open(self.file_path, 'r')
        current_line_in_file = file.readline()

        while current_line_in_file != "":
            current_line_in_file = current_line_in_file.strip().split(',')
            rental_id = int(current_line_in_file[rental_id_index])
            movie_id = current_line_in_file[movie_id_index]
            client_id = current_line_in_file[client_id_index]
            rental_date = datetime.strptime(current_line_in_file[rental_date_index],'%Y-%m-%d').date()
            due_date = datetime.strptime(current_line_in_file[due_date_index],'%Y-%m-%d').date()
            returned_date = datetime.strptime(current_line_in_file[returned_date_index],'%Y-%m-%d').date()
            returned_in_time = current_line_in_file[returned_in_time_index].strip() == 'True'

            self.add_rental(Rental(rental_id, int(movie_id), int(client_id), rental_date, due_date, returned_date,
                                   bool(returned_in_time)))
            current_line_in_file = file.readline()

        file.close()

    def write_to_file(self):
        with open(self.file_path, 'w') as file:
            file.truncate(0)

        file = open(self.file_path, 'w')
        rental_list = self.rental_list

        for rental in rental_list:
            file.write(str(rental.rental_id) + "," + str(rental.movie_id) + "," + str(rental.client_id) + "," +
                       str(rental.rental_date) + "," + str(rental.due_date) + "," + str(rental.returned_date) + "," +
                       str(rental.returned_in_time))
            file.write('\n')

        file.close()