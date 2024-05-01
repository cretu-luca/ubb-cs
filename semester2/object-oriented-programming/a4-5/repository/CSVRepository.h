#include "repository.h"

class CSVRepository: public Repository {
public:
    CSVRepository(string filepath) : Repository(filepath) {};

    void readData() override {
        std::ifstream fin(this->filepath);
        auto *movie = new Movie();

        while (fin >> *movie) {
            this->movies.push_back(movie);
            movie = new Movie();
        }

        fin.close();
    }

    void writeData() override {
        ofstream fout(this->filepath);
        for(const auto& movie: this->movies) {
            fout << *movie;
        }

        fout.close();
    }

    void openFile() override {
        string command = "start excel \"" + this->filepath;
        system(command.c_str());
    }
};