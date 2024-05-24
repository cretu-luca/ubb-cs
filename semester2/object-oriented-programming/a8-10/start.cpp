#include "GUI/gui.h"
#include "UI/userInterface.h"

int main(int argc, char** argv) {
    // UserInterface userInterface;

    QApplication app(argc, argv);
    MainWindow mainWidget;
    mainWidget.show();
    return app.exec();
}