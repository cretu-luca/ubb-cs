from src.domain.movie import Movie
from random import choice, randint
from src.start.movie_list import movies


class MovieMemoryRepository:
    def __init__(self):
        self.__movie_data = self.generated_movies(20)

    @property
    def movie_list(self):
        return self.__movie_data[:]

    @movie_list.setter
    def movie_list(self, other):
        self.__movie_data = other

    def add_movie(self, new_movie: Movie):
        self.__movie_data.append(new_movie)

    def remove_movie(self, movie_id: int):
        self.__movie_data = [movie for movie in self.__movie_data if movie.movie_id != movie_id]

    def update_movie(self, movie: Movie):
        for i, existing_movie in enumerate(self.movie_list):
            if existing_movie.movie_id == movie.movie_id:
                self.__movie_data[i] = movie

    def find_movie(self, search_key, **kwargs):
        movie_list = []
        if not isinstance(search_key, int):
            search_key = search_key.lower()
        for movie in self.__movie_data:
            if kwargs['search_criteria'] == 'movie_id' and search_key == movie.movie_id:
                movie_list.append(movie)
            if kwargs['search_criteria'] == 'title' and search_key in movie.title.lower():
                movie_list.append(movie)
            if kwargs['search_criteria'] == 'description' and search_key in movie.description.lower():
                movie_list.append(movie)
            if kwargs['search_criteria'] == 'genre' and search_key in movie.genre.lower():
                movie_list.append(movie)

        return movie_list

    @staticmethod
    def generated_movies(number_of_movies_to_generate: int):
        lower_bound = 1
        upper_bound = 1001
        movie_list = []
        movie_pace_types = ["slow-burn", "fast-paced"]
        movie_tone_types = ["light-hearted", "dark"]
        movie_thematic_depth = ["though-provoking", "surface-level"]
        movie_movie_style = ["visually-stunning", "minimalist"]
        movie_genre = ["action", "adventure", "comedy", "drama", "fantasy",
                       "documentary", "western", "biographic", "musical"]

        while number_of_movies_to_generate > 0:
            movie_id = randint(lower_bound, upper_bound)
            title = choice(movies)
            movie_description = (choice(movie_pace_types) + ", " + choice(movie_tone_types) + ", " +
                                 choice(movie_thematic_depth) + ", " + choice(movie_movie_style))
            genre = choice(movie_genre)
            if (not any(movie_id == movie.movie_id for movie in movie_list)
                    and not any(title == movie.title for movie in movie_list)):
                new_movie = Movie(movie_id, title, movie_description, genre)
                movie_list.append(new_movie)
                number_of_movies_to_generate -= 1

        return movie_list
