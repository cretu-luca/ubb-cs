#include <iostream>
using namespace std;

class HospitalDepartment {
protected:
    string hospitalName;
    int numberOfDoctors;
public:
    HospitalDepartment(string name, int doctors) :
        hospitalName(name), numberOfDoctors(doctors) {};
    virtual bool isEfficient() = 0;
    virtual string toString() = 0;
    string getName() {
        return this->hospitalName;
    }
};

class NeonataUnit: public HospitalDepartment {
public:
    NeonataUnit(string name, int doctors, double grade) :
            HospitalDepartment(name, doctors), averageGrade(grade) {};
    double averageGrade;

    bool isEfficient() override {
        return averageGrade > 8.5;
    }
    string toString() override {
        return "Name:" + this->hospitalName + '\n' +
                "Doctors:" + to_string(this->numberOfDoctors) + '\n' +
                "Grade:" + to_string(this->averageGrade) + '\n';
    }
};

class Surgery: public HospitalDepartment {
private:
    int numberOfPatients;
public:
    Surgery(string name, int doctors, int numberOfPatients) :
            HospitalDepartment(name, doctors), numberOfPatients(numberOfPatients) {};

    bool isEfficient() override {
        return numberOfPatients / numberOfDoctors >= 2;
    }
    string toString() override {
        return "Name:" + this->hospitalName + '\n' +
               "Doctors:" + to_string(this->numberOfDoctors) + '\n' +
               "Grade:" + to_string(this->numberOfPatients) + '\n';
    }
};