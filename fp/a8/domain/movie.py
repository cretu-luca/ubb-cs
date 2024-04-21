class Movie:
    def __init__(self, new_movie_id: int, new_title: str, new_description: str, new_genre: str):
        self.__movie_id = new_movie_id
        self.__title = new_title
        self.__description = new_description
        self.__genre = new_genre

    @property
    def movie_id(self):
        return self.__movie_id

    @movie_id.setter
    def movie_id(self, new_movie_id: int):
        self.__movie_id = new_movie_id

    @property
    def title(self):
        return self.__title

    @title.setter
    def title(self, new_title: int):
        self.__movie_id = new_title

    @property
    def description(self):
        return self.__description

    @description.setter
    def description(self, new_description: int):
        self.__description = new_description

    @property
    def genre(self):
        return self.__genre

    @genre.setter
    def genre(self, new_genre):
        self.__genre = new_genre

    @property
    def to_string(self):
        return (f"Movie ID: {self.__movie_id}\n"
                f"Title: {self.__title}\n"
                f"Description: {self.__description}\n"
                f"Genre: {self.__genre}\n")

    @property
    def to_dictionary(self):
        return {
            'Movie ID': self.__movie_id,
            'Title': self.__title,
            'Description': self.__description,
            'Genre': self.__genre
        }
