#include "SQLiteRepository.h"
#include <sstream>

SQLiteRepository::SQLiteRepository(const std::string& dbPath) {
    this->dbPath = dbPath;
    openDatabase();
    initializeTable();
}

SQLiteRepository::~SQLiteRepository() {
    closeDatabase();
}

void SQLiteRepository::openDatabase() {
    if (sqlite3_open(dbPath.c_str(), &db)) {
        throw std::runtime_error("Failed to open SQLite database");
    }
}

void SQLiteRepository::closeDatabase() {
    if (db) {
        sqlite3_close(db);
    }
}

void SQLiteRepository::initializeTable() {
    const char* sql = R"(
        CREATE TABLE IF NOT EXISTS movies (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            title TEXT,
            genre TEXT,
            trailerLink TEXT,
            releaseYear INTEGER,
            numberOfLikes INTEGER,
            inWatchlist INTEGER
        );
    )";

    char* errorMessage = nullptr;
    if (sqlite3_exec(db, sql, nullptr, nullptr, &errorMessage) != SQLITE_OK) {
        throw std::runtime_error("Failed to create movies table: " + std::string(errorMessage));
    }
}

void SQLiteRepository::addMovieToRepository(Movie* movie) {
    std::string sql = "INSERT INTO movies (title, genre, trailerLink, releaseYear, numberOfLikes, inWatchlist) VALUES (?, ?, ?, ?, ?, ?);";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        throw std::runtime_error("Failed to prepare SQL statement");
    }

    sqlite3_bind_text(stmt, 1, movie->getTitle().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, movie->getGenre().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, movie->getTrailerLink().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 4, movie->getReleaseYear());
    sqlite3_bind_int(stmt, 5, movie->getNumberOfLikes());
    sqlite3_bind_int(stmt, 6, movie->getWatchlistStatus());

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        throw std::runtime_error("Failed to insert movie into SQLite database");
    }

    sqlite3_finalize(stmt);
}

void SQLiteRepository::removeMovieFromRepositoryByIndex(int index) {
    std::string sql = "DELETE FROM movies WHERE id = ?;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        throw std::runtime_error("Failed to prepare SQL statement");
    }

    sqlite3_bind_int(stmt, 1, index);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        throw std::runtime_error("Failed to remove movie from SQLite database");
    }

    sqlite3_finalize(stmt);
}

void SQLiteRepository::updateMovieInRepository(int index, Movie* updatedMovie) {
    std::string sql = "UPDATE movies SET title = ?, genre = ?, trailerLink = ?, releaseYear = ?, numberOfLikes = ?, inWatchlist = ? WHERE id = ?;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        throw std::runtime_error("Failed to prepare SQL statement");
    }

    sqlite3_bind_text(stmt, 1, updatedMovie->getTitle().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, updatedMovie->getGenre().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, updatedMovie->getTrailerLink().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 4, updatedMovie->getReleaseYear());
    sqlite3_bind_int(stmt, 5, updatedMovie->getNumberOfLikes());
    sqlite3_bind_int(stmt, 6, updatedMovie->getWatchlistStatus());
    sqlite3_bind_int(stmt, 7, index);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        throw std::runtime_error("Failed to update movie in SQLite database");
    }

    sqlite3_finalize(stmt);
}

const vector<Movie*>& SQLiteRepository::getAllMovies() const {
    std::string sql = "SELECT * FROM movies;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        throw std::runtime_error("Failed to prepare SQL statement");
    }

    movies.clear();

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        auto* movie = new Movie(
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)),
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)),
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)),
            sqlite3_column_int(stmt, 4),
            sqlite3_column_int(stmt, 5),
            sqlite3_column_int(stmt, 6)
        );
        movies.push_back(movie);
    }

    sqlite3_finalize(stmt);
    return movies;
}

void SQLiteRepository::writeDataToSelectedFile() {
    
}

void SQLiteRepository::openSelectedFile() {

}
