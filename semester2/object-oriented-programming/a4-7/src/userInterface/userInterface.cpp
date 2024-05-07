#include "userInterface.h"
#include <algorithm>

UserInterface::UserInterface() {
    this->controller = nullptr;
    this->getFile();
    this->controller->readData();
    // this->controller.generateMovies();
    this->chooseProfileMenu();
}

void UserInterface::getFile() {
    int option;
    cout << "1. CSV\n"
            "2. HTML\n";

    cin >> option;
    if(option == 1) {
        this->controller = new Controller(R"(C:\Users\lucac\uni\ubb-cs\semester2\object-oriented-programming\a4-5\src\input-output\movies.csv)", "CSV");
    } else {
        this->controller = new Controller(R"(C:\Users\lucac\uni\ubb-cs\semester2\object-oriented-programming\a4-5\src\input-output\movies.html)", "HTML");
    }
}

void UserInterface::chooseProfileMenu() {
    int option;

    cout << "1. Admin\n"
            "2. User\n";

    cout << ">";
    cin >> option;

    if(option == 1)
        this->selectOptionAdministratorMenu();
    if(option == 2)
        this->selectOptionUserMenu();
}

void UserInterface::printAdministratorMainMenu(){
    cout << "1. Add movie\n";
    cout << "2. Remove movie\n";
    cout << "3. Update movie\n";
    cout << "4. List movies\n";
    cout << "5. Switch to user\n";
    cout << "0. Exit\n";
}

void UserInterface::printUserMainMenu(){
    cout << "1. Get movies by genre\n";
    cout << "2. Display Watchlist\n";
    cout << "3. Switch to admin\n";
    cout << "4. Open file\n";
    cout << "0. Exit\n";
}

void UserInterface::addUI(){
    string title, genre, trailerLink;
    int numberOfLikes, releaseYear;

    cout << "Title:";
    cin >> title;
    cout << "Genre:";
    cin >> genre;
    cout << "Trailer link:";
    cin >> trailerLink;
    cout << "Number of likes:";
    cin >> numberOfLikes;
    cout << "Release year:";
    cin >> releaseYear;

    auto *newMovie = new Movie(title, genre, trailerLink, releaseYear, numberOfLikes, false);
    try {
        this->controller->addController(newMovie);
    } catch (const CustomException& e) {
        cout << e.what();
    }
}

void UserInterface::removeByNameUI() {
    string title;

    cout << "Title:";
    cin >> title;

    try {
        this->controller->removeByName(title);
    } catch (const CustomException& e) {
        cout << e.what();
    }
}

void UserInterface::updateMovieUI(){
    int index, releaseYear, numberOfLikes;
    string title, genre, trailerLink;
    cout << "Enter the index of the movie to update:\n";
    cin >> index;

    cout << "Title:";
    cin >> title;
    cout << "Genre:";
    cin >> genre;
    cout << "Trailer link:";
    cin >> trailerLink;
    cout << "Release year:";
    cin >> releaseYear;
    cout << "Number of likes:";
    cin >> numberOfLikes;

    auto *newMovie = new Movie(title, genre, trailerLink, releaseYear, numberOfLikes, false);
    try {
        this->controller->updateController(index, newMovie);
    } catch (const CustomException& e) {
        cout << e.what();
    }

}

void UserInterface::listMoviesUI(){
    vector<Movie*> movieVector = this->controller->getAllMovies();
    for(int index = 0; index < movieVector.size(); index++)
        cout << to_string(index + 1) << "." << '\n' << ((Movie *) movieVector[index])->toString() << "\n\n";
}

void UserInterface::displayWatchlist() {
    vector<Movie*> movieVector = this->controller->getAllMovies();
    for(int index = 0; index < movieVector.size(); index++)
        if(movieVector[index]->getWatchlistStatus())
            cout << to_string(index + 1) << "." << '\n' << ((Movie *) movieVector[index])->toString() << "\n\n";
}

void UserInterface::printMenu() {
    cout << '\n';
    cout << "|----------------------------------------------------|\n";
    cout << "|  <  | Trailer (T) | Watchlist (W) | Like (L) |  >  |\n";
    cout << "|----------------------------------------------------|\n";
}

void UserInterface::displayMoviesByGenre() {
    vector<Movie*> movieVector;
    string genre;
    char option;
    cin.get();
    cout << "Genre:\n";
    std::getline(std::cin, genre);

    if(genre.empty())
        movieVector = this->controller->getAllMovies();
    else
        movieVector = this->controller->getAllMoviesByGenre(genre);

    for(int i = 0; i < movieVector.size(); i++) {
        cout << movieVector[i]->toStringExtended();
        cout << "|" + string(52, ' ') + "|\n";
        cout << "|" + string((48 - to_string(i + 1).size()) / 2 + 1, ' ') +
                string(2 - to_string(i + 1).size(), ' ') + to_string(i + 1) + "/" +
                to_string(movieVector.size()) + string((30 - to_string(i).size()) / 2, ' ') +
                string(2 - to_string(i + 1).size(),' ') + "Exit (E)|";
        this->printMenu();

        bool running = true;
        while(running) {
            cin >> option;

            if (option == '<') {
                if (i == 0) {
                    i = movieVector.size() - 2;
                } else
                    i -= 2;

                running = false;
            }
            if (option == '>') {
                if (i == movieVector.size() - 1)
                    i = -1;

                running = false;
            }
            if (option == 'T')
                ShellExecute(0, 0, movieVector[i]->getTrailerLink().c_str(), 0, 0, SW_SHOW);
            if(option == 'W') {
                if (this->controller->handleWatchlistOperation(movieVector[i]))
                    cout << "Movie added to watchlist.\n";
                else
                    cout << "Movie removed from watchlist.\n";

                cout << movieVector[i]->toStringExtended();
                cout << "|" + string(52, ' ') + "|\n";
                cout << "|" + string((48 - to_string(i + 1).size()) / 2 + 1, ' ') +
                        string(2 - to_string(i + 1).size(), ' ') + to_string(i + 1) + "/" +
                        to_string(movieVector.size()) + string((30 - to_string(i).size()) / 2, ' ') +
                        string(2 - to_string(i + 1).size(), ' ') + "Exit (E)" + " |";
                this->printMenu();
            }
            if(option == 'L') {
                cout << "Movie received a like.\n";
                movieVector[i]->setNumberOfLikes(movieVector[i]->getNumberOfLikes() + 1);

                cout << movieVector[i]->toStringExtended();
                cout << "|" + string(52, ' ') + "|\n";
                cout << "|" + string((48 - to_string(i + 1).size()) / 2 + 1, ' ') +
                        string(2 - to_string(i + 1).size(), ' ') + to_string(i + 1) + "/" +
                        to_string(movieVector.size()) + string((30 - to_string(i).size()) / 2, ' ') +
                        string(2 - to_string(i + 1).size(), ' ') + "Exit (E)" + " |";
                this->printMenu();
            }

            if(option == 'E') {
                cout << "Exiting...\n";
                return;
            }
        }
    }
}

void UserInterface::selectOptionUserMenu() {
    int option;

    while(true) {
        printUserMainMenu();
        cout << ">";
        cin >> option;

        if(option == 0) {
            this->controller->writeData();
            return;
        }
        if(option == 1)
            this->displayMoviesByGenre();
        if(option == 2)
            this->displayWatchlist();
        if(option == 3) {
            this->selectOptionAdministratorMenu();
            return;
        }
        if(option == 4) {
            this->controller->openFileController();
        }
    }
}

void UserInterface::selectOptionAdministratorMenu(){
    int option;

    while(true){
        printAdministratorMainMenu();
        cout << ">";
        cin >> option;

        if(option == 0)
            return;
        if(option == 1)
            this->addUI();
        if(option == 2)
            this->removeByNameUI();
        if(option == 3)
            this->updateMovieUI();
        if(option == 4)
            this->listMoviesUI();
        if(option == 5) {
            this->selectOptionUserMenu();
            return;
        }
    }
}
