#include <sstream>
#include "repository.h"

Repository::Repository(string filepath) {
    this->filepath = filepath;
}

Repository::~Repository(){
    for(auto &movie : this->movies) {
        delete movie;
    }
}

void Repository::addMovieToRepository(Movie* movie) {
    this->movies.push_back(movie);
    this->writeData();
}

void Repository::removeMovieFromRepositoryByIndex(int index) {
    if(index != -1) {
        delete this->movies[index];
        this->movies.erase(this->movies.begin() + index);
    }
    this->writeData();
}

void Repository::updateMovieInRepository(int index, Movie* updatedMovie) {
    index--;
    delete this->movies[index];
    this->movies[index] = updatedMovie;
    this->writeData();
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