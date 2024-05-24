#pragma once
#include "../repository/repository.h"

class Action {
protected:
    Repository& repository;
public:
    Action(Repository& r): repository(r) {};
    virtual ~Action() {};
    virtual void executeUndo() = 0;
    virtual void executeRedo() = 0;
};

class ActionAdd: public Action {
private:
    Movie* addedMovie;
public:
    ActionAdd(Repository& r, Movie* movie): Action(r) {
        this->addedMovie = new Movie(*movie);
    }
    ~ActionAdd() {
        delete addedMovie;
    }
    void executeUndo() override {
        this->repository.removeMovieFromRepository(addedMovie);
    }
    void executeRedo() override {
        this->repository.addMovieToRepository(new Movie(*addedMovie));
    }
};

class ActionRemove: public Action {
private:
    Movie* removedMovie;
public:
    ActionRemove(Repository& r, Movie* movie): Action(r) {
        this->removedMovie = new Movie(*movie);
    }
    ~ActionRemove() {
        delete removedMovie;
    }
    void executeUndo() override {
        this->repository.addMovieToRepository(new Movie(*removedMovie));
    }
    void executeRedo() override {
        this->repository.removeMovieFromRepository(removedMovie);
    }
};

class ActionUpdate: public Action {
private:
    Movie* newMovie;
    Movie* oldMovie;
public:
    ActionUpdate(Repository& r, Movie* newMovie, Movie* oldMovie): Action(r) {
        this->newMovie = new Movie(*newMovie);
        this->oldMovie = new Movie(*oldMovie);
    }
    ~ActionUpdate() {
        delete newMovie;
        delete oldMovie;
    }
    void executeUndo() override {
        int index = this->repository.getMovieIndex(newMovie);
        if (index != -1) {
            this->repository.updateMovieInRepository(index, new Movie(*oldMovie));
        }
    }
    void executeRedo() override {
        int index = this->repository.getMovieIndex(oldMovie);
        if (index != -1) {
            this->repository.updateMovieInRepository(index, new Movie(*newMovie));
        }
    }
};
