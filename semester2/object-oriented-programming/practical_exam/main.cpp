#include <iostream>
#include <QApplication>

#include "GUI.h"
using namespace std;

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    GUI gui;
    return app.exec();
}
