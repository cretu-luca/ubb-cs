#include "domain.cpp"
#include <vector>
#include <algorithm>
#include <fstream>

class Controller {
private:
    vector<HospitalDepartment *> departments;
public:
    void addDepartment(HospitalDepartment* hd) {
        this->departments.push_back(hd);
    }

    vector<HospitalDepartment*> getAllDepartments() {
        return this->departments;
    }

    vector<HospitalDepartment*> getAllEfficientDepartments() {
        vector<HospitalDepartment*> efficientDepartments;

        for(auto dept: this->departments)
            if(dept->isEfficient())
                efficientDepartments.push_back(dept);

        return efficientDepartments;
    }

    void addInitialValuesController() {
        HospitalDepartment* a = new NeonataUnit("Neonata1", 10, 9.8);
        HospitalDepartment* b = new NeonataUnit("Neonata2", 15, 8.4);
        HospitalDepartment* c = new Surgery("Surgery1", 7, 20);
        HospitalDepartment* d = new Surgery("Surgery2", 8, 15);
        HospitalDepartment* e = new NeonataUnit("Neonata3", 13, 30);

        this->addDepartment(b);
        this->addDepartment(a);
        this->addDepartment(c);
        this->addDepartment(d);
        this->addDepartment(e);
    }

    void writeToFile(string filename) {
        ofstream fout(filename);
        vector<HospitalDepartment*> sortedDepartments = this->departments;

        sort(sortedDepartments.begin(), sortedDepartments.end(), [](HospitalDepartment* a, HospitalDepartment* b) {
            return a->getName() < b->getName();
        });

        for(auto department: sortedDepartments)
            fout << department->toString() << "Efficient:" + to_string(department->isEfficient()) << "\n\n";
    }
};