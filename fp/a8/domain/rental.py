import datetime


class Rental:
    def __init__(self, rental_id: int, movie_id: int, client_id: int,
                 rented_date: datetime, due_date: datetime, returned_date: datetime, returned_in_time: bool):
        self.__rental_id = rental_id
        self.__movie_id = movie_id
        self.__client_id = client_id
        self.__rental_date = rented_date
        self.__due_date = due_date
        self.__returned_date = returned_date
        self.__returned_in_time = returned_in_time

    @property
    def rental_id(self):
        return self.__rental_id

    @property
    def movie_id(self):
        return self.__movie_id

    @property
    def client_id(self):
        return self.__client_id

    @property
    def rental_date(self):
        return self.__rental_date

    @property
    def due_date(self):
        return self.__due_date

    @property
    def returned_date(self):
        return self.__returned_date

    @returned_date.setter
    def returned_date(self, new_date):
        self.__returned_date = new_date

    @property
    def returned_in_time(self):
        return self.__returned_in_time

    @returned_in_time.setter
    def returned_in_time(self, status_value):
        self.__returned_in_time = status_value

    @property
    def to_string(self):
        return (f"Rental ID: {self.__rental_id}\n"
                f"Movie ID: {self.__movie_id}\n"
                f"Client ID: {self.__client_id}\n"
                f"Rental Date: {self.__rental_date}\n"
                f"Due Date: {self.__due_date}\n"
                f"Returned Date: {self.__returned_date}\n"
                f"Returned in time: {self.__returned_in_time}\n")

    @property
    def to_dictionary(self):
        return {
            'Rental ID': self.__rental_id,
            'Movie ID': self.__movie_id,
            'Client ID': self.__client_id,
            'Rental Date': self.__rental_date,
            'Due Date': self.__due_date,
            'Returned Date': self.__returned_date,
            'Returned in time': self.__returned_in_time
        }
