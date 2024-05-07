#include <sstream>
#include "repository.h"

Repository::Repository(string filepath) {
    this->filepath = filepath;
    this->getDataFromTextFile();
}

Repository::~Repository(){
    this->saveDataToTextFile();
    for(auto &movie : this->movies) {
        delete movie;
    }
}

void Repository::addMovieToRepository(Movie* movie) {
    this->movies.push_back(movie);
}

void Repository::removeMovieFromRepositoryByIndex(int index) {
    if(index != -1) {
        delete this->movies[index];
        this->movies.erase(this->movies.begin() + index);
    }
}

void Repository::updateMovieInRepository(int index, Movie* updatedMovie) {
    index--;
    delete this->movies[index];
    this->movies[index] = updatedMovie;
    this->writeDataToSelectedFile();
    this->saveDataToTextFile();
}

int Repository::getMovieIndex(Movie *movie) {
    for(int i = 0; i < this->movies.size(); i++) {
        if (*this->movies[i] == *movie)
            return i;
    }
    return -1;
}

int Repository::getMovieIndexByName(const string& name) {
    for(int i = 0; i < this->movies.size(); i++)
        if(this->movies[i]->getTitle() == name)
            return i;

    return -1;
}

int Repository::getNumberOfMovies() {
    return this->movies.size();
}

const vector<Movie*>& Repository::getAllMovies() const {
    return this->movies;
}

void Repository::getDataFromTextFile() {
    std::ifstream file(R"(C:\Users\lucac\CLionProjects\oop-a4-5-kpunkk_67\src\input_output\movies.txt)");
    std::string line;

    auto *movie = new Movie();

    while (file >> *movie) {
        this->movies.push_back(movie);
        movie = new Movie();
    }

    file.close();
}

void Repository::saveDataToTextFile() {
    ofstream fout(R"(C:\Users\lucac\CLionProjects\oop-a4-5-kpunkk_67\src\input_output\movies.txt)");
    for(const auto& movie: this->movies) {
        fout << *movie;
    }

    fout.close();
}

