from unittest import TestCase
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
        self.__services = Services(self.__movie_repository, self.__client_repository, self.__rental_repository)

    def test_add_client(self):
        client = Client(10001, "Luca")
        self.__client_repository.add_client(client)
        self.assertTrue(client in self.__client_repository.client_list)

    def test_add_movie(self):
        movie = Movie(10, "Fight Club", "funny, entertaining", "action")
        self.__movie_repository.add_movie(movie)
        self.assertTrue(movie in self.__movie_repository.movie_list)

    def test_retrieve_clients_list(self):
        client1 = Client(1001, "Tom")
        client2 = Client(1002, "Christopher")
        client3 = Client(1003, "Jane")
        self.__services.add_client_service(client1)
        self.__services.add_client_service(client2)
        self.__services.add_client_service(client3)
        client_list = self.__services.retrieve_clients_list()
        for client in client_list:
            self.assertIn(client, client_list)

    def test_retrieve_movies_list(self):
        movie1 = Movie(11, "Fight Club", "fast-paced", "action")
        movie2 = Movie(12, "The Oak", "slow-paced", "drama")
        movie3 = Movie(13, "Spider-Man", "fast-paced", "action")
        self.__services.add_movie_service(movie1)
        self.__services.add_movie_service(movie2)
        self.__services.add_movie_service(movie3)
        movie_list = self.__services.retrieve_movies_list()
        for movie in movie_list:
            self.assertIn(movie, movie_list)

    def test_find_client_service_by_field(self):
        client1 = Client(1001, "Luca")
        self.__services.add_client_service(client1)

        found_client_by_name1 = self.__services.find_client_service_by_field('name', "Luca")
        self.assertEqual(found_client_by_name1, [client1])

        found_client_by_name2 = self.__services.find_client_service_by_field('name', "Andrei")
        self.assertTrue(found_client_by_name2 == [])

        found_client_by_id1 = self.__services.find_client_service_by_field('client_id', 1001)
        self.assertEqual(found_client_by_id1, [client1])

        found_client_by_id2 = self.__services.find_client_service_by_field('client_id', '10001')
        self.assertTrue(found_client_by_id2 == [])

    def test_find_movie_service_by_field(self):
        movie1 = Movie(10000, "movie_to_find", "description_to_find",
                       "genre_to_find")
        self.__services.add_movie_service(movie1)
        found_movie_by_name1 = self.__services.find_movie_service_by_field('title',
                                                                           "movie_to_find")
        self.assertEqual(found_movie_by_name1, [movie1])
        found_movie_by_name2 = self.__services.find_movie_service_by_field('title',
                                                                           "name_of_no_movie")
        self.assertEqual(found_movie_by_name2, [])
        found_movie_by_description1 = self.__services.find_movie_service_by_field('description',
                                                                                  "description_to_find")
        self.assertEqual(found_movie_by_description1, [movie1])
        found_movie_by_description2 = self.__services.find_movie_service_by_field('description',
                                                                                  "xxxxxxxxx")
        self.assertEqual(found_movie_by_description2, [])
