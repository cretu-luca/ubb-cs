from src.repository.movie_repositories.movie_memory_repository import MovieMemoryRepository
from src.domain.movie import Movie


class MovieTextFileRepository(MovieMemoryRepository):
    def __init__(self, file_path):
        super().__init__()
        self.movie_list = []
        self.file_path = file_path
        self.read_from_file()

    def read_from_file(self):
        movie_id_index = 0
        title_index = 1
        description_index = 2
        genre_index = 3

        file = open(self.file_path, 'r')
        current_line_in_file = file.readline()

        while current_line_in_file != "":
            current_line_in_file = current_line_in_file.strip().split(',')
            client_id = int(current_line_in_file[movie_id_index])
            name = current_line_in_file[title_index]
            description = current_line_in_file[description_index]
            genre = current_line_in_file[genre_index]

            self.add_movie(Movie(client_id, name, description, genre))
            current_line_in_file = file.readline()

        file.close()

    def write_to_file(self):
        with open(self.file_path, 'w') as file:
            file.truncate(0)

        file = open(self.file_path, 'w')
        movie_list = self.movie_list

        for movie in movie_list:
            file.write(str(movie.movie_id) + "," + movie.title + "," + movie.description + "," + movie.genre)
            file.write('\n')

        file.close()