#include <iostream>
#include "Hra.h"
#include <ncurses.h>

int main() {
    bool hraj = true;
    Hra *hra = new Hra(20, 50);
    timeout(100); // Set a timeout in milliseconds

    while (hraj && hra->getPocetVykresleni() < 10) {
        int ch = getch();
        switch (ch) {
            case 'q':
                hraj = false;
                break;
            case 'p':
                continue;
            case KEY_UP:
                hra->zvysRychlost();
                break;
            case KEY_DOWN:
                hra->znizRychlost();
                break;
        }
        hra->updateHry();
        hra->vykresliHernyPlan();
    }

    hra->revertUpdateHry(2);
    hra->vykresliHernyPlan();


    //delete hra;  // Free allocated memory
    return 0;
}