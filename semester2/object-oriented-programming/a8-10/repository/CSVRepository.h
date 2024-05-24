#include "repository.h"

class CSVRepository: public Repository {
public:
    CSVRepository(string filepath) : Repository(filepath) {};

    void writeDataToSelectedFile() override {
        ofstream fout(this->filepath);
        for(const auto& movie: this->movies)
            if(movie->getWatchlistStatus()){
                fout << *movie;
        }

        fout.close();
    }

    void openSelectedFile() override {
        string command = "start excel \"" + this->filepath;
        system(command.c_str());
    }
};