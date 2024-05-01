from src.domain.rental import Rental
from src.domain.client import Client
from src.domain.movie import Movie
from src.services.service_exception import ServiceException
from src.repository.client_repositories.client_textfile_repository import ClientTextFileRepository
from src.repository.client_repositories.client_binaryfile_repository import ClientBinaryFileRepository
from src.services.undo_redo_service import FunctionCall, CascadedOperation, UndoRedo, Operation


class Services:
    def __init__(self, movie_repository, client_repository, rental_repository, undo_redo_repository):
        self.__movie_repository = movie_repository
        self.__client_repository = client_repository
        self.__rental_repository = rental_repository
        self.__undo_redo_repository = undo_redo_repository

    def save_to_file(self):
        self.__client_repository.write_to_file()
        self.__movie_repository.write_to_file()
        self.__rental_repository.write_to_file()

    def retrieve_clients_list(self):
        return [client for client in self.__client_repository.client_list]

    def find_client_service_by_field(self, searching_criteria, searching_key):
        return self.__client_repository.find_client(searching_key, search_criteria=searching_criteria)

    def retrieve_repository_type(self):
        if isinstance(self.__client_repository, ClientTextFileRepository):
            return "file"
        if isinstance(self.__client_repository, ClientBinaryFileRepository):
            return "file"
        return "memory"

    def add_client_service(self, new_client: Client):
        if not self.__client_repository.find_client(new_client.client_id, search_criteria='client_id'):
            self.__client_repository.add_client(new_client)
            undo_command = FunctionCall(self.__client_repository.remove_client, new_client.client_id)
            redo_command = FunctionCall(self.__client_repository.add_client, new_client)

            undo_redo_operation = Operation(undo_command, redo_command)
            self.__undo_redo_repository.record(undo_redo_operation)
        else:
            raise ServiceException(f"Client with ID {new_client.client_id} already in list!")

    def remove_client_service(self, client_id: int):
        clients = self.__client_repository.find_client(client_id, search_criteria='client_id')
        if not clients:
            raise ServiceException(f"Client with ID {client_id} does not exist!")

        client_to_remove = clients[0]
        self.__client_repository.remove_client(client_id)
        associated_rentals = self.__rental_repository.find_by_client_id(client_id)

        cascaded_operations = []
        for rental in associated_rentals:
            self.__rental_repository.remove_rental(rental.rental_id)
            undo_command = FunctionCall(self.__rental_repository.add_rental, rental)
            redo_command = FunctionCall(self.__rental_repository.remove_rental, rental.rental_id)
            undo_redo_command = Operation(undo_command, redo_command)
            cascaded_operations.append(undo_redo_command)

        undo_command = FunctionCall(self.__client_repository.add_client, client_to_remove)
        redo_command = FunctionCall(self.__client_repository.remove_client, client_id)
        undo_redo_command = Operation(undo_command, redo_command)
        cascaded_operations.append(undo_redo_command)

        cascaded_operations = CascadedOperation(*cascaded_operations)
        self.__undo_redo_repository.record(cascaded_operations)

    def update_client_service(self, old_client: Client, new_client: Client):
        original_client = self.find_client_service(old_client.client_id)
        if original_client:
            original_client = original_client[0]

            self.__client_repository.update_client(new_client)

            undo_command = FunctionCall(self.__client_repository.update_client, original_client)
            redo_command = FunctionCall(self.__client_repository.update_client, new_client)

            operation = Operation(undo_command, redo_command)
            self.__undo_redo_repository.record(operation)
        else:
            raise ServiceException(f"Client with ID {old_client.client_id} does not exist")

    def find_client_service(self, client_id):
        return self.__client_repository.find_client(client_id, search_criteria='client_id')

    def sort_clients_by_renting(self):
        sorted_clients = sorted(self.__client_repository.client_list,
                                key=lambda client: self.get_days_of_renting(client), reverse=True)

        return sorted_clients

    def get_days_of_renting(self, client):
        number_of_days = 0
        for rental in self.__rental_repository.rental_list:
            if rental.client_id == client.client_id:
                due_date = rental.due_date
                rental_date = rental.rental_date
                number_of_days += (due_date - rental_date).days

        return number_of_days

    def get_number_of_rents(self, movie):
        number_of_rents = 0
        for rental in self.__rental_repository.rental_list:
            if rental.movie_id == movie.movie_id:
                number_of_rents += 1

        return number_of_rents

    def retrieve_movies_list(self):
        return [movie for movie in self.__movie_repository.movie_list]

    def find_movie_service_by_field(self, searching_criteria, searching_key):
        return self.__movie_repository.find_movie(searching_key, search_criteria=searching_criteria)

    def add_movie_service(self, new_movie: Movie):
        if not self.__movie_repository.find_movie(new_movie.movie_id, search_criteria='movie_id'):
            self.__movie_repository.add_movie(new_movie)
            undo_command = FunctionCall(self.__movie_repository.remove_movie, new_movie.movie_id)
            redo_command = FunctionCall(self.__movie_repository.add_movie, new_movie)

            undo_redo_operation = Operation(undo_command, redo_command)
            self.__undo_redo_repository.record(undo_redo_operation)
        else:
            raise ServiceException(f"Movie with ID {new_movie.movie_id} already in list!")

    def remove_movie_service(self, movie_id: int):
        movies = self.__movie_repository.find_movie(movie_id, search_criteria='movie_id')
        if not movies:
            raise ServiceException(f"Movie with ID {movie_id} does not exist!")

        movies_to_remove = movies[0]
        self.__movie_repository.remove_movie(movie_id)
        associated_rentals = self.__rental_repository.find_by_movie_id(movie_id)

        cascaded_operations = []
        for rental in associated_rentals:
            self.__rental_repository.remove_rental(rental.rental_id)
            undo_command = FunctionCall(self.__rental_repository.add_rental, rental)
            redo_command = FunctionCall(self.__rental_repository.remove_rental, rental.rental_id)
            undo_redo_command = Operation(undo_command, redo_command)
            cascaded_operations.append(undo_redo_command)

        undo_command = FunctionCall(self.__movie_repository.add_movie, movies_to_remove)
        redo_command = FunctionCall(self.__movie_repository.remove_movie, movie_id)
        undo_redo_command = Operation(undo_command, redo_command)
        cascaded_operations.append(undo_redo_command)

        cascaded_operations = CascadedOperation(*cascaded_operations)
        self.__undo_redo_repository.record(cascaded_operations)

    def find_movie_service(self, movie_id):
        return self.__movie_repository.find_movie(movie_id, search_criteria='movie_id')

    def sort_movies_by_rents(self):
        sorted_movies = sorted(self.__movie_repository.movie_list,
                               key=lambda movie: self.get_number_of_rents(movie), reverse=True)

        return sorted_movies

    def retrieve_rentals_list(self):
        return [rental for rental in self.__rental_repository.rental_list]

    def add_rental_service(self, new_rental: Rental):
        self.__rental_repository.add_rental(new_rental)

        undo_command = FunctionCall(self.__rental_repository.remove_rental, new_rental.rental_id)
        redo_command = FunctionCall(self.__rental_repository.add_rental, new_rental)

        operation = Operation(undo_command, redo_command)
        self.__undo_redo_repository.record(operation)

    def find_rental_service(self, rental_id):
        for rental in self.__rental_repository.rental_list:
            if rental.rental_id == rental_id:
                return rental

        return None

    def update_movie_service(self, old_movie: Movie, new_movie: Movie):
        original_movie = self.find_movie_service(old_movie.movie_id)
        if original_movie:
            original_movie = original_movie[0]

            self.__movie_repository.update_movie(new_movie)

            undo_command = FunctionCall(self.__movie_repository.update_movie, original_movie)
            redo_command = FunctionCall(self.__movie_repository.update_movie, new_movie)

            operation = Operation(undo_command, redo_command)
            self.__undo_redo_repository.record(operation)
        else:
            raise ServiceException(f"Movie with ID {original_movie.movie_id} does not exist")

    def fill_return_status_service(self, rental_id, returned_date, status_value):
        self.__rental_repository.fill_return_status(rental_id, returned_date, status_value)

        undo_command = FunctionCall(self.__rental_repository.fill_return_status,
                                    *(rental_id, None, True))
        redo_command = FunctionCall(self.__rental_repository.fill_return_status,
                                    *(rental_id, returned_date, status_value))

        operation = Operation(undo_command, redo_command)
        self.__undo_redo_repository.record(operation)