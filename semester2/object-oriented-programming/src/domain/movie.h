#pragma once
#include <iostream>
#include <sstream>

using namespace std;

class Movie {
private:
    string title, genre, trailerLink;
    int releaseYear, numberOfLikes;
    bool inWatchlist;

public:
    Movie(string title, string genre, string trailerLink, int releaseYear, int numberOfLikes, bool inWatchlist);
    Movie(const Movie& secondMovie);
    Movie() = default;

    bool operator==(const Movie &other);
    bool getWatchlistStatus();

    friend istream& operator>>(istream& fin, Movie& movie);
    friend ostream& operator<<(ostream& fout, Movie& movie);

    string getTitle() const;
    string getGenre() const;
    string getTrailerLink() const;
    string toString() const;
    string toStringExtended() const;

    int getReleaseYear() const;
    int getNumberOfLikes() const;

    void setNumberOfLikes(const int newNumberOfLikes);
    void setWatchlistStatus();
};