from src.repository.movie_repositories.movie_memory_repository import MovieMemoryRepository
from src.repository.movie_repositories.movie_textfile_repository import MovieTextFileRepository
from src.repository.movie_repositories.movie_binaryfile_repository import MovieBinaryFileRepository
from src.repository.client_repositories.client_memory_repository import ClientMemoryRepository
from src.repository.client_repositories.client_textfile_repository import ClientTextFileRepository
from src.repository.client_repositories.client_binaryfile_repository import ClientBinaryFileRepository
from src.repository.rental_repositories.rental_memory_repository import RentalMemoryRepository
from src.repository.rental_repositories.rental_textfile_repository import RentalTextFileRepository
from src.repository.rental_repositories.rental_binaryfile_repository import RentalBinaryFileRepository
from src.services.services import Services
from src.ui.ui import UserInterface
from configparser import ConfigParser
from src.services.undo_redo_service import UndoRedo


def main():
    movie_repository = ""
    client_repository = ""
    rental_repository = ""
    undo_redo_repository = UndoRedo()
    configs = ConfigParser()
    configs.read('settings.properties')

    repository_type = configs['settings']['repository']
    if repository_type == "memory":
        movie_repository = MovieMemoryRepository()
        client_repository = ClientMemoryRepository()
        rental_repository = RentalMemoryRepository(movie_repository, client_repository)
    elif repository_type == "textfile":
        movie_repository = MovieTextFileRepository(configs['settings']['movies'])
        client_repository = ClientTextFileRepository(configs['settings']['clients'])
        rental_repository = RentalTextFileRepository(configs['settings']['rentals'], movie_repository, client_repository)
    elif repository_type == "binaryfile":
        movie_repository = MovieBinaryFileRepository(configs['settings']['movies'])
        client_repository = ClientBinaryFileRepository(configs['settings']['clients'])
        rental_repository = RentalBinaryFileRepository(configs['settings']['rentals'], movie_repository, client_repository)

    services = Services(movie_repository, client_repository, rental_repository, undo_redo_repository)
    user_interface = UserInterface(services, undo_redo_repository)

    user_interface.main_menu()

main()