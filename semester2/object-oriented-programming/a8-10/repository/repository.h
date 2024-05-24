#pragma once
#include "../domain/movie.h"
#include "../exceptions/exception.h"
#include <vector>
#include <fstream>

class Repository{
protected:
    string filepath;
    vector<Movie*> movies;

public:
    Repository(string filepath);
    ~Repository();

    virtual void writeDataToSelectedFile() = 0;
    virtual void openSelectedFile() = 0;

    Movie* getMovieAtGivenIndexRepository(int index);

    void getDataFromTextFile();
    void saveDataToTextFile();

    const vector<Movie*>& getAllMovies() const;
    void addMovieToRepository(Movie* movie);
    void updateMovieInRepository(int index, Movie* movie);
    void removeMovieFromRepositoryByIndex(int index);
    void removeMovieFromRepository(Movie* movie);
    void likeMovieAtGivenIndexRepository(int index);
    void UpdateMovieInRepository(Movie* oldMovie, Movie* newMovie);

    int getMovieIndex(Movie* movie);
    int getMovieIndexByName(const string& name);
    int getNumberOfMovies();
};