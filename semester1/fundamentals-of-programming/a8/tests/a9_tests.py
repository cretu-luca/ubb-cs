from unittest import TestCase
from src.services.undo_redo_service import UndoRedo, Operation, FunctionCall
from src.ui.ui import UserInterface
from src.repository.movie_repositories.movie_memory_repository import MovieMemoryRepository
from src.repository.client_repositories.client_memory_repository import ClientMemoryRepository
from src.repository.rental_repositories.rental_memory_repository import RentalMemoryRepository
from src.services.services import Services
from src.domain.client import Client
from src.domain.movie import Movie


class Test(TestCase):
    def setUp(self):
        self.__movie_repository = MovieMemoryRepository()
        self.__client_repository = ClientMemoryRepository()
        self.__rental_repository = RentalMemoryRepository(self.__movie_repository, self.__client_repository)
        self.__undo_redo_service = UndoRedo()
        self.__services = Services(self.__movie_repository, self.__client_repository, self.__rental_repository, self.__undo_redo_service)
        self.__user_interface = UserInterface(self.__services, self.__undo_redo_service)

    def test_undo_redo_add_client(self):
        client = Client(10001, "Luca")
        self.__client_repository.add_client(client)
        self.assertTrue(client in self.__client_repository.client_list)

        undo_command = FunctionCall(self.__client_repository.remove_client, client.client_id)
        redo_command = FunctionCall(self.__client_repository.add_client, client)
        undo_redo_operation = Operation(undo_command, redo_command)
        self.__undo_redo_service.record(undo_redo_operation)

        self.__undo_redo_service.undo()
        self.assertTrue(client not in self.__client_repository.client_list)

        self.__undo_redo_service.redo()
        self.assertTrue(client in self.__client_repository.client_list)

    def test_undo_redo_add_movie(self):
        movie = Movie(10, "Fight Club", "funny, entertaining", "action")
        self.__movie_repository.add_movie(movie)
        self.assertTrue(movie in self.__movie_repository.movie_list)

        undo_command = FunctionCall(self.__movie_repository.remove_movie, movie.movie_id)
        redo_command = FunctionCall(self.__movie_repository.add_movie, movie)

        undo_redo_operation = Operation(undo_command, redo_command)
        self.__undo_redo_service.record(undo_redo_operation)
        self.__undo_redo_service.undo()
        self.assertTrue(movie not in self.__movie_repository.movie_list)

        self.__undo_redo_service.redo()
        self.assertTrue(movie in self.__movie_repository.movie_list)

    def test_undo_redo_remove_movie(self):
        movie = Movie(10, "Fight Club", "funny, entertaining", "action")
        self.__movie_repository.add_movie(movie)
        self.assertTrue(movie in self.__movie_repository.movie_list)

        self.__movie_repository.remove_movie(movie.movie_id)
        self.assertTrue(movie not in self.__movie_repository.movie_list)

        undo_command = FunctionCall(self.__movie_repository.add_movie, movie)
        redo_command = FunctionCall(self.__movie_repository.remove_movie, movie.movie_id)
        undo_redo_operation = Operation(undo_command, redo_command)
        self.__undo_redo_service.record(undo_redo_operation)

        self.__undo_redo_service.undo()
        self.assertTrue(movie in self.__movie_repository.movie_list)

        self.__undo_redo_service.redo()
        self.assertTrue(movie not in self.__movie_repository.movie_list)

    def test_undo_redo_remove_client(self):
        client = Client(10001, "Luca")
        self.__client_repository.add_client(client)
        self.assertTrue(client in self.__client_repository.client_list)

        self.__client_repository.remove_client(client.client_id)
        self.assertTrue(client not in self.__client_repository.client_list)

        undo_command = FunctionCall(self.__client_repository.add_client, client)
        redo_command = FunctionCall(self.__client_repository.remove_client, client.client_id)
        undo_redo_operation = Operation(undo_command, redo_command)
        self.__undo_redo_service.record(undo_redo_operation)

        self.__undo_redo_service.undo()
        self.assertTrue(client in self.__client_repository.client_list)

        self.__undo_redo_service.redo()
        self.assertTrue(client not in self.__client_repository.client_list)
