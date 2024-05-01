import pickle
from datetime import datetime
from src.repository.rental_repositories.rental_memory_repository import RentalMemoryRepository
from src.domain.rental import Rental


class RentalBinaryFileRepository(RentalMemoryRepository):
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

        file = open(self.file_path, 'rb')

        rental_information = pickle.load(file)
        for rental_object in rental_information:
            rental_object = rental_object.split(',')
            rental_id = int(rental_object[rental_id_index])
            movie_id = int(rental_object[movie_id_index])
            client_id = int(rental_object[client_id_index])
            rental_date = datetime.strptime(rental_object[rental_date_index],'%Y-%m-%d').date()
            due_date = datetime.strptime(rental_object[due_date_index],'%Y-%m-%d').date()
            returned_date = datetime.strptime(rental_object[returned_date_index],'%Y-%m-%d').date()
            returned_in_time = rental_object[returned_in_time_index].strip() == 'True'

            self.add_rental(Rental(rental_id, movie_id, client_id, rental_date, due_date, returned_date,
                                   returned_in_time))

        file.close()

    def write_to_file(self):
        file = open(self.file_path, 'wb')
        file.truncate(0)
        rental_information = []
        for rental in self.rental_list:
            rental_string = (str(rental.rental_id) + "," + str(rental.movie_id) + "," +
                              str(rental.client_id) + "," + str(rental.rental_date) + "," + str(rental.due_date) + ","
                              + str(rental.returned_date) + "," + str(rental.returned_in_time))
            rental_information.append(rental_string)
        pickle.dump(rental_information, file)
        file.close()
