#include "controller.h"

Controller::Controller(const string& filepath, const string& filetype) {
    if(filetype == "CSV") {
        this->repository = new CSVRepository(filepath);
    } else {
        this->repository = new HTMLRepository(filepath);
    }
    // this->generateMovies();
}

void Controller::addMovieController(Movie* movie) {
    if (this->repository->getMovieIndex(movie) != -1) {
        throw CustomException("Movie already in the list.\n");
    } else {
        this->repository->addMovieToRepository(movie);
    }
}

void Controller::updateController(int index, Movie* movie) {
    if(index - 1 > this->repository->getNumberOfMovies()) {
        throw CustomException("Movie index out of bounds.\n");
    } else {
        this->repository->updateMovieInRepository(index, movie);
    }
}

void Controller::removeMovieByNameController(const string& name) {
    int index = this->repository->getMovieIndexByName(name);

    if(index == -1) {
        throw CustomException("Movie does not exist.\n");
    } else {
        this->repository->removeMovieFromRepositoryByIndex(index);
    }
}

bool Controller::handleWatchlistOperation(Movie* movie){
    movie->setWatchlistStatus();
    this->repository->saveDataToTextFile();
    return movie->getWatchlistStatus();
}

vector<Movie*> Controller::getAllMovies() const {
    return this->repository->getAllMovies();
}

vector<Movie*> Controller::getAllMoviesByGenre(const string& genre) const {
    vector<Movie*> allMovies = this->repository->getAllMovies();
    vector<Movie*> selectedMovies;

    for(int i = 0; i < allMovies.size(); i++)
        if(allMovies[i]->getGenre() == genre)
            selectedMovies.push_back(allMovies[i]);

    return selectedMovies;
}

void Controller::readData() {
    // this->repository->readData();
}

void Controller::writeData() {
    this->repository->writeDataToSelectedFile();
    this->repository->saveDataToTextFile();
}

void Controller::openFileController() {
    this->repository->openSelectedFile();
}

void Controller::generateMovies() {
    srand(time(nullptr));

    auto *movie1 = new Movie("Harakiri", "History", "https://youtu.be/gfABwM-Ppng?si=tbWo9Yy7Syv_NhCk", 1962, rand() % 100 + 1, false);
    auto *movie2 = new Movie("Come-and-See", "History", "https://youtu.be/UHaSQU-4wss?si=MEeaZosrbh8B1GMx", 1985, rand() % 100 + 1, true);
    auto *movie3 = new Movie("12-Angry-Men", "Drama", "https://youtu.be/TEN-2uTi2c0?si=V5axgNwsrRDl3xX6", 1957, rand() % 100 + 1, false);
    auto *movie4 = new Movie("Seven-Samurai", "Action", "https://youtu.be/wJ1TOratCTo?si=_zs5RithlkNdCRvR", 1954, rand() % 100 + 1, true);
    auto *movie5 = new Movie("The-Godfather:-Part-II", "Crime", "https://youtu.be/9O1Iy9od7-A?si=P7DMkZb9ETwIVP78", 1974, rand() % 100 + 1, false);
    auto *movie6 = new Movie("High-and-Low", "Crime", "https://youtu.be/LV3z2Ytxu90?si=YcZEU6cJSFJQWJQF", 1963, rand() % 100 + 1, true);
    auto *movie7 = new Movie("Parasite", "Drama", "https://youtu.be/5xH0HfJHsaY?si=7jIVe7Hfk6htsnU3", 2019, rand() % 100 + 1, false);
    auto *movie8 = new Movie("The-Godfather", "Crime", "https://youtu.be/UaVTIH8mujA?si=U9640-BFD74SW5o8", 1972, rand() % 100 + 1, true);
    auto *movie9 = new Movie("The-Godfather:-Part-III", "Thriller", "https://youtu.be/mS8YraEXC9c?si=40aw8nZo3-DOh6TD", 1961, rand() % 100 + 1, false);
    auto *movie10 = new Movie("The-Shawshank-Redemption", "Drama", "https://youtu.be/PLl99DlL6b4?si=D12ENJvFb1SLz4ss", 1994, rand() % 100 + 1, false);
    auto *movie11 = new Movie("Yi-Yi", "Drama", "https://youtu.be/f46txO0dlOo?si=I-6i-rfY-kJMbKfn", 2000, rand() % 100 + 1, false);
    auto *movie12 = new Movie("Dune:-Part-Two", "Sci-Fi", "https://youtu.be/U2Qp5pL3ovA?si=2u3w6-lUpAdK43If", 2024, rand() % 100 + 1, true);
    auto *movie13 = new Movie("City-of-God", "Romance", "https://youtu.be/dcUOO4Itgmw?si=_2E0CZOr_TtJirFA", 2002, rand() % 100 + 1, false);
    auto *movie14 = new Movie("Schindler's-List", "History", "https://youtu.be/gG22XNhtnoY?si=omIIekTjLdF6EUnp", 1993, rand() % 100 + 1, false);
    auto *movie15 = new Movie("Ikiru", "Drama", "https://youtu.be/2VeLN3IDjzQ?si=jE1uJgtbPV82KxLC", 1952, rand() % 100 + 1, true);

    this->repository->addMovieToRepository(movie2);
    this->repository->addMovieToRepository(movie1);
    this->repository->addMovieToRepository(movie3);
    this->repository->addMovieToRepository(movie4);
    this->repository->addMovieToRepository(movie5);
    this->repository->addMovieToRepository(movie6);
    this->repository->addMovieToRepository(movie7);
    this->repository->addMovieToRepository(movie8);
    this->repository->addMovieToRepository(movie9);
    this->repository->addMovieToRepository(movie10);
    this->repository->addMovieToRepository(movie11);
    this->repository->addMovieToRepository(movie12);
    this->repository->addMovieToRepository(movie13);
    this->repository->addMovieToRepository(movie14);
    this->repository->addMovieToRepository(movie15);
}