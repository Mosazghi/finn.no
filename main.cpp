/**
 *   Hovedprogrammet for OOP-prosjektet V23 med et Miniatyr-Finn<dot>no
 *      med salg av "Leker og Spill".
 * 
 *   Programmet:
 *      - inneholder to Kunder og Kategorier objekter, 
          hvor  de henholdvis inneholder en <liste> med kunder 
          og en <map> med ulike kategorier.
        - lar opprette ny kunde, vise en og alle kunder og fjerne en kunde.
        - vise frem alle tilgjengelige kategorier, og opprette en ny en.
        - lar kunden legge inn EN ny ting (med alle sine data)
        - lar en kunde kj�pe EN tinng
        - sletter ut�pte ting
        - leser og skriver HELE datastrukturene til/fra fil
 * 
 *   @date     11.04.2023
 *   @file     main.cpp
 *   @author   Abdirahman A. Yusuf, Mosazghi Y. Tesfazghi, Emil Johansen
*/

#include <iostream>
#include "source/Funksjoner.h"
#include "source/kunder.h"
#include "source/kategorier.h"
#include "source/LesData3.h"

using namespace std;


/**
 *  Globale container-objekter med ALLE kundene og kategoriene
*/
Kunder     gKundebase;  // Global container for ALLE kundene
Kategorier gKategoribase;  /// Global container for ALLE kategoriene


/**
 *  Hovedprogramet:
*/
int main() {
    char valg;

    gKategoribase.lesFraFil();
    gKundebase.lesFraFil();
    gKategoribase.slettTing(getMaskinTid()); // Sletter utl�pte ting

    skrivMeny();

    valg = lesChar("\nKommando");

    while (valg != 'Q') {
        switch (valg) {
            case 'U': gKundebase.handling();         break;
            case 'A': case 'K':  case 'T':
                gKategoribase.handling(valg);  break;
            default:  skrivMeny();                   break;
        }
        valg = lesChar("\nKommando");
    }

    cout << "\n\n";

    gKundebase.skrivTilFil();
    gKategoribase.skrivTilFil();

    gKundebase.deAlloker();
    gKategoribase.deAlloker();

    return 0;
}