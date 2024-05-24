#include <iostream>
#include <utility>
using namespace std;

class CustomException: public exception {
private:
    string message;
public:
    CustomException(const string& message) : message(message) {};
    const char* what() const noexcept override { return message.c_str(); };
};