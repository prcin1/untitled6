//
// Created by PC on 2. 1. 2024.
//
#include "Mriezka.h"

Mriezka::Mriezka() {
    srand(time(NULL)); // Inicializácia generátoru náhodných čísel
    this->riadok = 100;
    this->stlpec = 100;
    // Alokácia pamäte pre pole ukazovateľov
    znaky = (bool**)malloc(riadok * sizeof(bool*));

    // Alokácia pamäte pre každý riadok
    for (int i = 0; i < riadok; ++i) {
        znaky[i] = (bool*)malloc(stlpec * sizeof(bool));
    }

    // Inicializácia hodnôt v poli
    for (int i = 0; i < riadok; ++i) {
        for (int j = 0; j < stlpec; ++j) {
            znaky[i][j] = false;
        }
    }
}

Mriezka::Mriezka(int r, int s) {
    this->riadok = r;
    this->stlpec = s;
    // Alokácia pamäte pre pole ukazovateľov
    znaky = (bool**)malloc(riadok * sizeof(bool*));

    // Alokácia pamäte pre každý riadok
    for (int i = 0; i < riadok; ++i) {
        znaky[i] = (bool*)malloc(stlpec * sizeof(bool));
    }

    // Inicializácia hodnôt v poli
    for (int i = 0; i < riadok; ++i) {
        for (int j = 0; j < stlpec; ++j) {
            znaky[i][j] = false;
        }
    }
}

// Funkcia pre získanie hodnoty na daných súradniciach s ošetrením chýb
bool Mriezka::getZnak(int riadok, int stlpec) {
    if (jePlatnaSuradnica(riadok, stlpec)) {
        return znaky[riadok][stlpec];  // Vráti hodnotu na daných súradniciach
    } else {
        // Error handling - vracia predvolenú hodnotu alebo vyhodí chybu
        throw std::out_of_range("Neplatné súradnice");
    }
}

// Funkcia na zmenu hodnoty na daných súradniciach s ošetrením chýb
void Mriezka::zmenZnak(int riadokIndex, int stlpecIndex, bool zije) {
    if (jePlatnaSuradnica(riadokIndex, stlpecIndex)) {
        znaky[riadokIndex][stlpecIndex] = zije;  // Zmení hodnotu na daných súradniciach
    } else {
        // Error handling - môže vyhodiť chybu, vypísať upozornenie, atď.
        std::cout << "Neplatné súradnice" << std::endl;
    }
}

Mriezka::~Mriezka() {
    for (int i = 0; i < riadok; ++i) {
        free(znaky[i]);
    }
    free(znaky);
}


int Mriezka::pocetZivychSusedov(int r, int s) {
    int pocetZivychSusedov = 0;
    for (int i = r - 1; i <= r + 1; ++i) {
        for (int j = s - 1; j <= s + 1; ++j) {
            if (i >= 0 && i < riadok && j >= 0 && j < stlpec && (i != r || j != s)) {
                if (znaky[i][j]) {
                    pocetZivychSusedov++;
                }
            }
        }
    }
    return pocetZivychSusedov;
}

void Mriezka::generujNahodneRozlozenie() {

    for (int i = 0; i < riadok; ++i) {
        for (int j = 0; j < stlpec; ++j) {
            // Nastavenie stavu bunky na základe náhodného čísla
            bool stav = rand() % 2 == 0; // True alebo False náhodne
            znaky[i][j] = stav;
        }
    }
}
