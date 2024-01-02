//
// Created by PC on 2. 1. 2024.
//
#include "Hra.h"
#include "Mriezka.h"
#include <ncurses.h>

Hra::Hra(int riadky, int stlpce) {
    this->pocetRiadkov = riadky;
    this->pocetStlpcov = stlpce;
    this->mriezka = new Mriezka(riadky, stlpce);
    rychlost = 2;
    initscr(); // Inicializácia nCurses
    cbreak(); // Aktivuje line buffering
    noecho(); // Nezobrazuje znaky z klávesnice
    curs_set(0); // Skryje kurzor
    mriezka->generujNahodneRozlozenie();
    this->pocetVykresleni = 0;
}

void Hra::vykresliHernyPlan() {
    mvprintw(0, 0, "Rychlost = %d sekund", rychlost);
    // Vykreslenie hracieho plánu
    for (int i = 0; i < pocetRiadkov; ++i) {
        for (int j = 0; j < pocetStlpcov; ++j) {
            char znak =  this->mriezka->getZnak(i, j) ? '#' : '.'; // Získanie stavu bunky

            // Vykreslenie znaku na daných súradniciach
            mvaddch(i + 6, j, znak);
        }
    }
    mvprintw(1, 0, "pocet vykresleni = %d", this->getPocetVykresleni());
    sleep(rychlost);
    refresh();
}

void Hra::updateHry() {
    Mriezka novaMriezka(mriezka->getPocetRiadkov(), mriezka->getPocetStlpcov()); // Nová mriežka pre update

    // Prechod cez všetky bunky
    for (int i = 0; i < mriezka->getPocetRiadkov(); ++i) {
        for (int j = 0; j < mriezka->getPocetStlpcov(); ++j) {
            int pocetZivychSusedov = mriezka->pocetZivychSusedov(i, j); // Zistíme počet živých susedov pre bunku (i, j)
            bool aktualnyStav = mriezka->getZnak(i, j); // Získať aktuálny stav bunky

            // Pravidlá Game of Life pre update
            if (aktualnyStav && (pocetZivychSusedov < 2 || pocetZivychSusedov > 3)) {
                novaMriezka.zmenZnak(i, j, false); // Bunka umiera z osamelosti alebo preplnenia
            } else if (!aktualnyStav && pocetZivychSusedov == 3) {
                novaMriezka.zmenZnak(i, j, true); // Bunka ožíva, ak má presne 3 živých susedov
            } else {
                novaMriezka.zmenZnak(i, j, aktualnyStav); // Bunka zostáva v aktuálnom stave
            }
        }
    }

    // Aplikácia zmien na pôvodnú mriežku
    for (int i = 0; i < mriezka->getPocetRiadkov(); ++i) {
        for (int j = 0; j < mriezka->getPocetStlpcov(); ++j) {
            mriezka->zmenZnak(i, j, novaMriezka.getZnak(i, j));
        }
    }
    this->pocetVykresleni++;
}

Hra::~Hra() {
    endwin(); // Ukončenie nCurses
    delete mriezka;
}

void Hra::zvysRychlost() {
    if (rychlost > 1) rychlost--;
}

int Hra::getPocetVykresleni() {
    return this->pocetVykresleni;
}

void Hra::revertUpdateHry(int pocetKrokov) {
    Mriezka predoslaMriezka(mriezka->getPocetRiadkov(), mriezka->getPocetStlpcov());

    for (int k = 0; k < pocetKrokov; ++k) {
        for (int i = 0; i < mriezka->getPocetRiadkov(); ++i) {
            for (int j = 0; j < mriezka->getPocetStlpcov(); ++j) {
                int pocetZivychSusedov = mriezka->pocetZivychSusedov(i, j);
                bool aktualnyStav = mriezka->getZnak(i, j);

                if (!aktualnyStav && (pocetZivychSusedov < 2 || pocetZivychSusedov > 3)) {
                    predoslaMriezka.zmenZnak(i, j, false);
                } else if (aktualnyStav || (aktualnyStav && pocetZivychSusedov == 3)) {
                    predoslaMriezka.zmenZnak(i, j, true);
                }
            }
        }

        for (int i = 0; i < mriezka->getPocetRiadkov(); ++i) {
            for (int j = 0; j < mriezka->getPocetStlpcov(); ++j) {
                bool znak = predoslaMriezka.getZnak(i, j);
                mriezka->zmenZnak(i, j, znak);
            }
        }
        this->pocetVykresleni--;
    }
}
