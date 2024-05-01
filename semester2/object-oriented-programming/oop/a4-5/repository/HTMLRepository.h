#include "repository.h"

class HTMLRepository: public Repository {
public:
    HTMLRepository(string filepath) : Repository(filepath) {};

    void readData() {};

    void writeData() override {
        ofstream fout(this->filepath);

        fout << "<!DOCTYPE html>\n<html>\n<head>\n<title>Movies</title>\n<head><body>\n<table border=\"1\">";
        for(auto const& movie: this->movies) {
            fout << "<tr>\n<td>" << movie->getTitle() << "</td>\n<td>" << movie->getGenre() << "</td>\n<td>"
                 << movie->getTrailerLink() << "</td>\n<td>" << movie->getNumberOfLikes() << "</td>\n<td>"
                 << movie->getReleaseYear() << "</td>\n</tr>\n";
        }
    }

    void openFile() override {
        std::string command = "start " + std::string(this->filepath);
        system(command.c_str());
    }
};