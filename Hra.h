//
// Created by PC on 2. 1. 2024.
//

#ifndef UNTITLED6_HRA_H
#define UNTITLED6_HRA_H
#include "Mriezka.h"
#include <ncurses.h>
#include <unistd.h>


class Hra {
private:
    int pocetRiadkov;
    int pocetStlpcov;
    Mriezka *mriezka;
    int rychlost;
    int pocetVykresleni;

public:
    Hra(int riadky, int stlpce);
    void setMriezka(Mriezka *m) {*mriezka = *m;};
    void vykresliHernyPlan();
    void znizRychlost() {rychlost++;};
    void zvysRychlost();
    void updateHry();
    int getPocetVykresleni();
    void revertUpdateHry(int pocetKrokov);
    ~Hra();
};

#endif //UNTITLED6_HRA_H
