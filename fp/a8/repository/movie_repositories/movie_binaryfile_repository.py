import pickle
from src.repository.movie_repositories.movie_memory_repository import MovieMemoryRepository
from src.domain.movie import Movie


class MovieBinaryFileRepository(MovieMemoryRepository):
    def __init__(self, file_path):
        super().__init__()
        self.movie_list = []
        self.file_path = file_path
        self.read_from_file()

    def read_from_file(self):
        with open(self.file_path, 'rb') as file:
            movie_information = pickle.load(file)

        movie_id_index = 0
        title_index = 1
        genre_index = -1

        for movie in movie_information:
            movie_details = movie.split(',')
            movie_id = int(movie_details[movie_id_index])
            title = movie_details[title_index]
            description = ','.join(movie_details[2:-1])
            genre = movie_details[genre_index]

            movie_data_from_file = Movie(movie_id, title, description, genre)
            self.add_movie(movie_data_from_file)

    def write_to_file(self):
        file = open(self.file_path, 'wb')
        file.truncate(0)
        movie_information = []
        for movie in self.movie_list:
            movie_string = str(movie.movie_id) + "," + movie.title + "," + movie.description + "," + movie.genre
            movie_information.append(movie_string)
        pickle.dump(movie_information, file)
        file.close()