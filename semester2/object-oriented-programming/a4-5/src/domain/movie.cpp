#include "movie.h"
#include <utility>

Movie::Movie(string title, string genre, string trailerLink, int releaseYear, int numberOfLikes, bool inWatchlist){
    this->title = std::move(title);
    this->genre = std::move(genre);
    this->trailerLink = std::move(trailerLink);

    this->releaseYear = releaseYear;
    this->numberOfLikes = numberOfLikes;
    this->inWatchlist = inWatchlist;
}

Movie::Movie(const Movie& secondMovie){
    this->title = secondMovie.title;
    this->genre = secondMovie.genre;
    this->trailerLink = secondMovie.trailerLink;

    this->releaseYear = secondMovie.releaseYear;
    this->numberOfLikes = secondMovie.numberOfLikes;
    this->inWatchlist = secondMovie.inWatchlist;
}

bool Movie::operator==(const Movie &other){
    return this->title == other.title && this->genre == other.genre &&
           this->trailerLink == other.trailerLink && this->releaseYear == other.releaseYear &&
           this->numberOfLikes == other.numberOfLikes;
}

istream& operator>>(istream& fin, Movie& movie) {
    std::string line;

    getline(fin, line);
    std::stringstream linestream(line);
    char comma;

    getline(linestream, movie.title, ',');
    getline(linestream, movie.genre, ',');
    getline(linestream, movie.trailerLink, ',');
    linestream >> movie.releaseYear >> comma;
    linestream >> movie.numberOfLikes >> comma;
    linestream >> movie.inWatchlist;

    return fin;
}

ostream& operator<<(ostream& fout, Movie& movie) {
    fout << movie.title << ","
         << movie.genre << ","
         << movie.trailerLink << ","
         << movie.releaseYear << ","
         << movie.numberOfLikes << ","
         << movie.inWatchlist << "," << '\n';

    return fout;
}

string Movie::getTitle() const{
    return this->title;
}

string Movie::getGenre() const{
    return this->genre;
}

string Movie::getTrailerLink() const{
    return this->trailerLink;
}

int Movie::getReleaseYear() const{
    return this->releaseYear;
}

int Movie::getNumberOfLikes() const{
    return this->numberOfLikes;
}

void Movie::setGenre(const string newGenre){
    this->genre = newGenre;
}

void Movie::setTrailerLink(const string newTrailerLink){
    this->trailerLink = newTrailerLink;
}

void Movie::setReleaseYear(const int newReleaseYear){
    this->releaseYear = newReleaseYear;
}

void Movie::setNumberOfLikes(const int newNumberOfLikes){
    this->numberOfLikes = newNumberOfLikes;
}

string Movie::toString() const{
    return "Title: " + this->title + "\nGenre: " + this->genre +
           "\nRelease Year: " + to_string(this->releaseYear) +
           "\nNumber of likes: " + to_string(this->numberOfLikes);
}

bool Movie::getWatchlistStatus() {
    return this->inWatchlist;
}

void Movie::setWatchlistStatus() {
    this->inWatchlist = 1 - this->inWatchlist;
}

string Movie::toStringExtended() const {
    string movieString;
    movieString += "|----------------------------------------------------|\n";
    movieString += "|--------------> Local Movie Database <--------------|\n";
    movieString += "|----------------------------------------------------|\n";
    movieString += "| Title:"+ string(44 - this->title.size(), ' ') + this->title + " |\n";
    movieString += "| Genre:" + string(44 - this->genre.size(), ' ') + this->genre + " |\n";
    movieString += "| Release Year:" + string(37 - to_string(this->releaseYear).size(), ' ') + to_string(this->releaseYear) + " |\n";
    movieString += "| Number of likes:" + string(34 - to_string(this->numberOfLikes).size(), ' ') + to_string(this->numberOfLikes) + " |\n";
    if(!this->inWatchlist)
        movieString += "| In watchlist:" + string(35, ' ') + "No" + " |\n";
    else
        movieString += "| In watchlist:" + string(34, ' ') + "Yes" + " |\n";

    return movieString;
}
