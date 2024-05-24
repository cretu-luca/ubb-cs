#pragma once
#include <memory>
#include <stack>

#include "action.h"
#include "../repository/CSVRepository.h"
#include "../repository/HTMLRepository.h"

class Controller {
public:
    Repository* repository;
    std::stack<std::unique_ptr<Action>> undoStack;
    std::stack<unique_ptr<Action>> redoStack;

public:
    Controller(const string& filepath, const string& filetype);

    vector<Movie*> getAllMovies() const;
    vector<Movie*> getAllMoviesByGenre(const string& genre) const;
    vector<Movie*> getWatchlist() const;

    Movie* getMovieAtGivenIndex(int index);

    bool handleWatchlistOperation(Movie* movie);

    void undo();
    void redo();

    void generateMovies();
    void readData();
    void writeData();
    void addMovieController(Movie* movie);
    void removeMovieByNameController(const string& name);
    void updateController(int index, Movie* movie);
    void openFileController();
    void likeMovieAtGivenIndex(int index);
};