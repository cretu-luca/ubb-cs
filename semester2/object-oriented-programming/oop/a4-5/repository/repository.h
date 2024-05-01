#pragma once
#include "../domain/movie.h"
#include "../exception.h"
#include <vector>
#include <fstream>

class Repository{
protected:
    string filepath;
    vector<Movie*> movies;
public:
    Repository(string filepath);
    ~Repository();

    virtual void readData() = 0;
    virtual void writeData() = 0;
    virtual void openFile() = 0;

    const vector<Movie*>& getAllMovies() const;
    void addMovieToRepository(Movie* movie);
    void updateMovieInRepository(int index, Movie* movie);
    void removeMovieFromRepositoryByIndex(int index);

    int getMovieIndex(Movie* movie);
    int getMovieIndexByName(const string& name);
    int getNumberOfMovies();
};