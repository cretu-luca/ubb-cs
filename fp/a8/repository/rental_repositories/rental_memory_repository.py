import datetime
from random import randint, choice
from src.domain.rental import Rental
from src.repository.movie_repositories.movie_memory_repository import MovieMemoryRepository
from src.repository.client_repositories.client_memory_repository import ClientMemoryRepository


class RentalMemoryRepository:
    def __init__(self, movie_repository: MovieMemoryRepository, client_repository: ClientMemoryRepository):
        self.__rental_data = self.generated_rentals(20, movie_repository.movie_list,
                                                    client_repository.client_list)

    @property
    def rental_list(self):
        return self.__rental_data[:]

    @rental_list.setter
    def rental_list(self, other):
        self.__rental_data = other

    def add_rental(self, new_rental: Rental):
        self.__rental_data.append(new_rental)

    def find_by_client_id(self, client_id):
        return [rental for rental in self.rental_list if rental.client_id == client_id]

    def find_by_movie_id(self, movie_id):
        return [rental for rental in self.rental_list if rental.movie_id == movie_id]

    def remove_rental(self, rental_id):
        self.__rental_data = [rental for rental in self.__rental_data if rental.rental_id != rental_id]

    def fill_return_status(self, rental_id, returned_date, status_value):
        for rental in self.__rental_data:
            if rental.rental_id == rental_id:
                rental.returned_in_time = status_value
                rental.returned_date = returned_date

    @staticmethod
    def generated_rentals(number_of_rentals_to_generate, movie_list, client_list):
        lower_bound = 1
        upper_bound = 20
        first_day_of_the_year = datetime.date(2023, 1, 1)
        day_lower_bound = 1
        day_upper_bound = 365

        available_movie_ids = []
        available_client_ids = []
        for movie in movie_list:
            available_movie_ids.append(movie.movie_id)

        for client in client_list:
            available_client_ids.append(client.client_id)

        rentals_list = []
        while number_of_rentals_to_generate > 0:
            returned_in_time = True
            rental_id = randint(lower_bound, upper_bound)
            movie_id = choice(available_movie_ids)
            client_id = choice(available_client_ids)

            rented_date_days = randint(day_lower_bound, day_upper_bound)
            rented_date = first_day_of_the_year + datetime.timedelta(days=rented_date_days)

            due_date_days = randint(rented_date_days, day_upper_bound)
            due_date = first_day_of_the_year + datetime.timedelta(days=due_date_days)

            returned_date_days = randint(rented_date_days, day_upper_bound)
            returned_date = first_day_of_the_year + datetime.timedelta(days=returned_date_days)

            if returned_date_days > due_date_days:
                returned_in_time = False

            if not any(rental_id == rental.rental_id for rental in rentals_list):
                new_rental = Rental(rental_id, movie_id, client_id, rented_date, due_date,
                                    returned_date, returned_in_time)
                rentals_list.append(new_rental)
                number_of_rentals_to_generate -= 1

        return rentals_list
