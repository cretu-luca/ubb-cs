#ifndef SQLITEREPOSITORY_H
#define SQLITEREPOSITORY_H

#include "repository.h"
#include <sqlite3.h>

class SQLiteRepository : public Repository {
private:
    sqlite3* db;
    std::string dbPath;

public:
    SQLiteRepository(const std::string& dbPath);
    ~SQLiteRepository();

    void openDatabase();
    void closeDatabase();
    void initializeTable();
    
    void addMovieToRepository(Movie* movie) override;
    void removeMovieFromRepositoryByIndex(int index) override;
    void updateMovieInRepository(int index, Movie* updatedMovie) override;
    const vector<Movie*>& getAllMovies() const override;

    void writeDataToSelectedFile() override;
    void openSelectedFile() override;
};

#endif
