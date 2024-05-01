import datetime
from src.services.services import Services
from src.domain.client import Client
from src.domain.movie import Movie
from src.domain.rental import Rental
from src.services.service_exception import ServiceException
from src.services.undo_redo_service import UndoRedo, UndoRedoError, FunctionCall, Operation, CascadedOperation
from src.start.magic_numbers import (search_movie_by_id_option, search_movie_by_title_option,
                                     search_movie_by_description_option, search_movie_by_genre_option,
                                     search_client_by_id_option, search_client_by_name_option,
                                     manage_clients_and_movies_option, rent_or_return_option,
                                     list_clients_movies_rentals_options, statistics_option, manage_clients_option,
                                     search_by_field, manage_movies_option, add_option, remove_option, update_option,
                                     list_clients_option, list_movies_option, list_rentals_option,
                                     search_movie_option, search_client_option, rent_option,
                                     return_option, exit_option, most_rented_movies_option, most_active_clients_option,
                                     late_rentals_option, undo_option, redo_option)


class UserInterface:
    def __init__(self, services: Services, undo_redo_service):
        self.__services = services
        self.__undo_redo_service = undo_redo_service

    def main_menu(self):
        while True:
            try:
                self.print_main_menu()
                option = int(input("> "))

                if not isinstance(option, int):
                    print("Option must be an integer!")

                if option == manage_clients_and_movies_option:
                    self.print_main_management_menu()
                    option = int(input("> "))

                    if option == manage_clients_option:
                        self.print_secondary_management_menu("clients")
                        option = int(input("> "))
                        if option == add_option:
                            self.add_client_ui()
                        elif option == remove_option:
                            self.remove_client_ui()
                        elif option == update_option:
                            self.update_client_ui()

                    elif option == manage_movies_option:
                        self.print_secondary_management_menu("movies")
                        option = int(input("> "))
                        if option == add_option:
                            self.add_movie_ui()
                        elif option == remove_option:
                            self.remove_movie_ui()
                        elif option == update_option:
                            self.update_movie_ui()

                elif option == rent_or_return_option:
                    self.print_renting_or_returning_menu()
                    option = int(input("> "))

                    if option == rent_option:
                        self.rent_ui()

                    elif option == return_option:
                        self.return_ui()

                elif option == list_clients_movies_rentals_options:
                    self.print_listing_menu()
                    option = int(input("> "))

                    if option == list_clients_option:
                        self.list_clients_ui()
                    if option == list_movies_option:
                        self.list_movies_ui()
                    if option == list_rentals_option:
                        self.list_rentals_ui()

                elif option == search_by_field:
                    self.print_search_menu()
                    option = int(input("> "))

                    if option == search_client_option:
                        self.search_client_by_field()
                    elif option == search_movie_option:
                        self.search_movie_by_field()

                elif option == statistics_option:
                    self.print_statistics_menu()
                    option = int(input("> "))

                    if option == most_rented_movies_option:
                        most_rented_movies = self.__services.sort_movies_by_rents()
                        headers = ["Number of rents", "Movie ID", "Title", "Genre", "Description"]
                        table_format = "{:<17} | {:<10} | {:<20} | {:<12} | {:<30}"
                        print(table_format.format(*headers))
                        print("------------------------------------------------------------------------"
                              "---------------------------------------------------------")

                        for movie in most_rented_movies:
                            if self.__services.get_number_of_rents(movie):
                                movie_information = [str(self.__services.get_number_of_rents(movie)),
                                                     str(movie.movie_id), str(movie.title), str(movie.genre),
                                                     str(movie.description)]
                                print(table_format.format(*movie_information))
                        print('\n')

                    elif option == most_active_clients_option:
                        most_active_clients = self.__services.sort_clients_by_renting()
                        headers = ["Days of renting", "Client ID", "Client Name", "Renting Eligibility"]
                        table_format = "{:<15} | {:<10} | {:<10} | {:<10}"
                        print(table_format.format(*headers))
                        print("-------------------------------------------------------------------")

                        for client in most_active_clients:
                            if self.__services.get_days_of_renting(client):
                                client_information = [str(self.__services.get_days_of_renting(client)),
                                                      str(client.client_id), str(client.name),
                                                      str(self.is_eligible_for_renting(client.client_id))]
                                print(table_format.format(*client_information))
                        print('\n')

                    elif option == late_rentals_option:
                        rentals_list = self.__services.retrieve_rentals_list()
                        headers = ["Rental ID", "Movie ID", "Client ID", "Rental Date", "Due Date",
                                   "Returned Date", "Returned in time"]
                        table_format = "{:<10} | {:<10} | {:<10} | {:<15} | {:<15} | {:<15} | {:<5}"
                        print(table_format.format(*headers))
                        print("------------------------------------------------------------------------"
                              "------------------------------------")

                        for rental in rentals_list:
                            if rental.returned_in_time is False:
                                rental_information = [str(rental.rental_id), str(rental.movie_id),
                                                      str(rental.client_id), str(rental.rental_date),
                                                      str(rental.due_date), str(rental.returned_date),
                                                      "Yes" if rental.returned_in_time else "No"]
                                print(table_format.format(*rental_information))

                elif option == undo_option:
                    try:
                        self.__undo_redo_service.undo()
                        print("Last operation has been undone")
                    except UndoRedoError as ure:
                        print(ure)

                elif option == redo_option:
                    try:
                        self.__undo_redo_service.redo()
                        print("Last operation has been redone")
                    except UndoRedoError as ure:
                        print(ure)

                elif option == exit_option:
                    if not self.__services.retrieve_repository_type() == "memory":
                        self.__services.save_to_file()
                    exit(0)

            except ValueError as ve:
                print(ve)

    def add_client_ui(self):
        while True:
            try:
                client_id = int(input("Client ID: "))
                break
            except ValueError:
                print("Client ID must be an integer!")

        client_name = str(input("Client Name: "))
        new_client = Client(client_id, client_name)

        try:
            self.__services.add_client_service(new_client)
        except ServiceException as re:
            print(re)

    def remove_client_ui(self):
        while True:
            try:
                client_id = int(input("Client ID: "))
                break
            except ValueError:
                raise ValueError("Client ID must be an integer!")

        try:
            self.__services.remove_client_service(client_id)
        except ServiceException as ve:
            print(ve)

    def update_client_ui(self):
        while True:
            try:
                client_id = int(input("Client ID: "))
                break
            except ValueError:
                raise ValueError("Client ID must be an integer!")

        found_client = self.__services.find_client_service(client_id)
        if not found_client:
            raise ValueError(f"Client with ID {client_id} does not exist.")

        found_client = found_client[0]
        new_name = input("New name: ")

        updated_client = Client(client_id, new_name)

        try:
            self.__services.update_client_service(found_client, updated_client)
        except ServiceException as se:
            print(se)

    def add_movie_ui(self):
        while True:
            try:
                movie_id = int(input("Movie ID: "))
                break
            except ValueError:
                raise ValueError("Movie ID must be an integer!")

        title = str(input("Title: "))
        description = str(input("Description: "))
        genre = str(input("Genre: "))

        try:
            new_movie = Movie(movie_id, title, description, genre)
            self.__services.add_movie_service(new_movie)
        except ServiceException as re:
            print(re)

    def remove_movie_ui(self):
        while True:
            try:
                movie_id = int(input("Movie ID: "))
                break
            except ValueError:
                raise ValueError("Movie ID must be an integer!")

        try:
            self.__services.remove_movie_service(movie_id)
        except ValueError as ve:
            print(ve)

    def update_movie_ui(self):
        while True:
            try:
                movie_id = int(input("Movie ID: "))
                break
            except ValueError:
                raise ValueError("Movie ID must be an integer!")

        found_movie = self.__services.find_movie_service(movie_id)
        found_movie = found_movie[0]
        if found_movie:
            title = input("Enter new title: ")
            description = input("Enter new description: ")
            genre = input("Enter new genre: ")
            updated_movie = Movie(movie_id, title, description, genre)
            self.__services.update_movie_service(found_movie, updated_movie)
        else:
            raise ValueError(f"Movie with ID {movie_id} does not exist")

    def rent_ui(self):
        try:
            client_id = int(input("Client ID: "))
            movie_id = int(input("Movie ID: "))
            rental_date_day = int(input("Day of the rental: "))
            rental_date_month = int(input("Month of the rental: "))
            rental_date_year = int(input("Year of the rental: "))

            due_date_day = int(input("Day of the due date: "))
            due_date_month = int(input("Month of the due date: "))
            due_date_year = int(input("Year of the due date: "))

            rental_date = datetime.date(rental_date_year, rental_date_month, rental_date_day)
            due_date = datetime.date(due_date_year, due_date_month, due_date_day)

            if not self.is_eligible_for_renting(client_id):
                print(f"Client with ID {client_id} is not eligible for renting.")

            if not self.__services.find_client_service(client_id):
                print(f"Client with ID {client_id} does not exist")

            new_rental = Rental(len(self.__services.retrieve_rentals_list()) + 1, movie_id, client_id,
                                rental_date, due_date, None, True)
            self.__services.add_rental_service(new_rental)

        except ValueError as ve:
            print("Invalid input type!")

    def return_ui(self):
        try:
            rental_id = int(input("Rental ID: "))
            returned_date_day = int(input("The day the movie was returned: "))
            returned_date_month = int(input("The month the movie was returned: "))
            returned_date_year = int(input("The year the movie was returned: "))

            returned_date = datetime.date(returned_date_year, returned_date_month, returned_date_day)

            rental = self.__services.find_rental_service(rental_id)
            if rental:
                if rental.returned_date:
                    print("This movie has already been returned ")

                elif rental.rental_date > returned_date:
                    print("A movie cannot be returned before the rental date.")

                elif rental.due_date > returned_date:
                    self.__services.fill_return_status_service(rental_id, returned_date, True)
                else:
                    self.__services.fill_return_status_service(rental_id, returned_date, False)

            else:
                print("No rental with this ID available for return.")

        except ValueError as ve:
            print(ve)

    def is_eligible_for_renting(self, client_id):
        for rental in self.__services.retrieve_rentals_list():
            if rental.client_id == int(client_id) and rental.returned_in_time is False:
                return False

        return True

    def search_client_by_field(self):
        print("Search by: \n"
              "1. Client ID\n"
              "2. Client Name\n")

        option = int(input("> "))
        if option == search_client_by_id_option:
            try:
                id_to_search = int(input("ID: "))
                clients = self.__services.find_client_service_by_field('client_id', id_to_search)
                if clients:
                    for client in clients:
                        print(f"Client ID: {client.client_id}\nName: {client.name}")
                else:
                    print("No clients found.")

            except ValueError:
                print("Client ID must be an integer!")
        elif option == search_client_by_name_option:
            name_to_search = input("Name: ")
            clients = self.__services.find_client_service_by_field("name", name_to_search)
            if clients:
                for client in clients:
                    print(client.to_string)
            else:
                print("No clients found.")
        else:
            print("Invalid option selected.")

    def search_movie_by_field(self):
        print("Search by: \n"
              "1. Movie ID\n"
              "2. Title\n"
              "3. Description\n"
              "4. Genre\n")

        option = int(input("> "))
        if option == search_movie_by_id_option:
            try:
                id_to_search = int(input("ID: "))
                movies = self.__services.find_movie_service_by_field('movie_id', id_to_search)
                if movies:
                    for movie in movies:
                        print(movie.to_string)
                else:
                    print("No movies found.")

            except ValueError:
                print("Movie ID must be an integer!")

        elif option == search_movie_by_title_option:
            title_to_search = input("Title: ")
            movies = self.__services.find_movie_service_by_field('title', title_to_search)
            if movies:
                for movie in movies:
                    print(movie.to_string)
            else:
                print("No movies found.")

        elif option == search_movie_by_description_option:
            description_to_search = input("Description: ")
            movies = self.__services.find_movie_service_by_field('description', description_to_search)
            if movies:
                for movie in movies:
                    print(movie.to_string)
            else:
                print("No movies found")

        elif option == search_movie_by_genre_option:
            genre_to_search = input("Genre: ")
            movies = self.__services.find_movie_service_by_field('genre', genre_to_search)
            if movies:
                for movie in movies:
                    print(movie.to_string)
            else:
                print("No movies found.")

        else:
            print("Invalid option selected.")

    def list_clients_ui(self):
        clients_list = self.__services.retrieve_clients_list()
        headers = ["Client ID", "Client Name", "Renting Eligibility"]
        table_format = "{:<10} | {:<10} | {:<10}"

        print(table_format.format(*headers))
        print("----------------------------------------")

        for client in clients_list:
            client_information = [str(client.client_id), str(client.name),
                                  str(self.is_eligible_for_renting(client.client_id))]
            print(table_format.format(*client_information))
        print('\n')

    def list_movies_ui(self):
        movies_list = self.__services.retrieve_movies_list()
        headers = ["Movie ID", "Title", "Genre", "Description"]
        table_format = "{:<10} | {:<20} | {:<12} | {:<30}"
        print(table_format.format(*headers))
        print("------------------------------------------------------------------------"
              "------------------------------------")

        for movie in movies_list:
            movie_information = [str(movie.movie_id), str(movie.title), str(movie.genre), str(movie.description)]
            print(table_format.format(*movie_information))
        print('\n')

    def list_rentals_ui(self):
        rentals_list = self.__services.retrieve_rentals_list()
        headers = ["Rental ID", "Movie ID", "Client ID", "Rental Date", "Due Date",
                   "Returned Date", "Returned in time"]
        table_format = "{:<10} | {:<10} | {:<10} | {:<15} | {:<15} | {:<15} | {:<5}"
        print(table_format.format(*headers))
        print("------------------------------------------------------------------------"
              "------------------------------------")

        for rental in rentals_list:
            rental_information = [str(rental.rental_id), str(rental.movie_id),
                                  str(rental.client_id), str(rental.rental_date),
                                  str(rental.due_date), str(rental.returned_date),
                                  "Yes" if rental.returned_in_time else "No"]
            print(table_format.format(*rental_information))
        print('\n')

    @staticmethod
    def print_main_menu():
        print(f"1. Manage client and movies\n"
              f"2. Rent or return a movie\n"
              f"3. List clients, movies or rentals\n"
              f"4. Search client or movie\n"
              f"5. Statistics\n"
              f"6. Undo\n"
              f"7. Redo\n"
              f"8. Exit\n")

    @staticmethod
    def print_main_management_menu():
        print(f"1. Manage clients\n"
              f"2. Manage movies\n")

    @staticmethod
    def print_secondary_management_menu(type_of_class_instance_to_modify):
        print(f"Following functionalities address {type_of_class_instance_to_modify}")
        print(f"1. Add\n"
              f"2. Remove\n"
              f"3. Update\n")

    @staticmethod
    def print_renting_or_returning_menu():
        print(f"1. Rent\n"
              f"2. Return\n")

    @staticmethod
    def print_listing_menu():
        print(f"1. List clients\n"
              f"2. List movies\n"
              f"3. List rentals\n")

    @staticmethod
    def print_search_menu():
        print("1. Search client\n"
              "2. Search movie\n")

    @staticmethod
    def print_statistics_menu(): 
        print(f"1. Most rented movies\n"
              f"2. Most active clients\n"
              f"3. Late rentals\n")
