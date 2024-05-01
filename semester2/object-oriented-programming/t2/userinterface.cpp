#include "controller.cpp"

class UserInterface {
private:
    Controller controller;
public:
    void addInitialValuesUI() {
        this->controller.addInitialValuesController();
    }

    void menu() {
        cout << "1. Add new department\n"
                "2. Show all departments\n"
                "3. Show all efficient departments\n"
                "4. Save hospitals to a file\n";
    }

    void getUserInput() {
        int option;
        while(true) {
            this->menu();
            cout << ">";
            cin >> option;

            if(option == 0)
                exit(0);
            if(option == 1)
                this->addUI();
            if(option == 2)
                this->showAll();
            if(option == 3)
                this->showEfficient();
            if(option == 4)
                this->saveToFileUI();
        }
    }

    void saveToFileUI() {
        this->controller.writeToFile("file.txt");
    }

    void showEfficient() {
        vector<HospitalDepartment*> efficient = this->controller.getAllEfficientDepartments();

        for(auto department: efficient)
            cout << department->toString() << '\n';
     }

    void addUI() {
        int option;
        cout << "1. NeonataUnit\n"
                "2. Surgery\n";

        cin >> option;

        if(option == 1) {
            string name;
            int doctors;
            double grade;

            cout << "Hospital Name:\n";
            cin >> name;
            cout << "Number of doctors:\n";
            cin >> doctors;
            cout << "Grade:\n";
            cin >> grade;

            HospitalDepartment* a = new NeonataUnit(name, doctors, grade);
            this->controller.addDepartment(a);
        }
        else
            if(option == 2) {
                string name;
                int doctors, numberOfPatients;

                cout << "Name:\n";
                cin >> name;
                cout << "Doctors:\n";
                cin >> doctors;
                cout << "Patients:\n";
                cin >> numberOfPatients;

                HospitalDepartment* b = new Surgery(name, doctors, numberOfPatients);
                this->controller.addDepartment(b);
            }
    }

    void showAll() {
        vector<HospitalDepartment *> all = this->controller.getAllDepartments();

        for(auto dept: all)
            cout << dept->toString() << '\n';
    }
};