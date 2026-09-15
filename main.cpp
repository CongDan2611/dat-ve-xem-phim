#include "Menu.h"

int main() {
    AccountManager accountManager("users.txt");
    runMainMenu(accountManager);
    return 0;
}