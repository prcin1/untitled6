//
// Created by PC on 2. 1. 2024.
//

#ifndef UNTITLED6_MRIEZKA_H
#define UNTITLED6_MRIEZKA_H
#include <cstdlib>
#include <iostream>
#include <stdlib.h>

class Mriezka {
private:
    int riadok;
    int stlpec;
    bool** znaky;

public:
    Mriezka();
    Mriezka(int riadok, int stlpec);
    bool getZnak(int riadok, int stlpec);
    void zmenZnak(int riadok, int stlpec, bool zije);
    int getPocetRiadkov() {return riadok;};
    int getPocetStlpcov() {return stlpec;};
    int pocetZivychSusedov(int riadok, int stlpec);
    void generujNahodneRozlozenie();
    ~Mriezka();
private:
    bool jePlatnaSuradnica(int riadokIndex, int stlpecIndex) {return (riadokIndex >= 0 && riadokIndex < riadok &&
                                                                      stlpecIndex >= 0 && stlpecIndex < stlpec);};
};


#endif //UNTITLED6_MRIEZKA_H
