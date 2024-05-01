#include "../ui/ui.h"

int main(){
    UserInterface * userInterface = createUserInterface();
    mainMenu(userInterface);
    destroyUserInterface(userInterface);
}