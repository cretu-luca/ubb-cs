#pragma once
#include "../repository/CSVRepository.h"
#include "../repository/HTMLRepository.h"

class Controller {
public:
    Repository* repository;

public:
    Controller(const string& filepath, const string& filetype);

    vector<Movie*> getAllMovies() const;
    vector<Movie*> getAllMoviesByGenre(const string& genre) const;

    bool handleWatchlistOperation(Movie* movie);

    void generateMovies();
    void readData();
    void writeData();
    void addMovieController(Movie* movie);
    void removeMovieByNameController(const string& name);
    void updateController(int index, Movie* movie);
    void openFileController();
};