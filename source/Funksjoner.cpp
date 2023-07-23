#include <iostream>
#include "Funksjoner.h"
#include "kunder.h"
#include <algorithm>
#include <ctime>
#pragma warning(disable : 4996) // Ignorerer warning ifm. lesing av maskindato 

using namespace std;


/**
 *  Skriver meny valg
*/
void skrivMeny() {
    cout << "\nF�lgende kommandoer er tilgjengelig:"
         << "\n\n\tU A\t\t - Skriv alle kunder"
         << "\n\tU S <knr>\t - Skriv en gitt kunde"
         << "\n\tU N\t\t - Ny kunde"
         << "\n\tU F <knr>\t - Fjern/slett kunde"
         << "\n\n\tA A\t\t - Skriv alle kategoirer"
         << "\n\tA S <navn>\t - Skriv en gitt kategori"
         << "\n\tA N\t\t - Ny kategori"
         << "\n\n\tT N\t\t - Ny Ting til salgs"
         << "\n\tT E\t\t - Endre antall av en Ting"
         << "\n\tT F <dato>\t - Slette ting FOR dato"
         << "\n\n\tK\t\t - Kj�p en gjenstand"
         << "\n\n\tQ\t\t - Quit\n\n";
}


/**
 *  Henter n�v�rende tid.
 * 
 *  @return maskindato (AAAAMMDD) 
*/
int getMaskinTid() {
    time_t tidNaa = time(0);                                 // N�v�rende tid

    char datoString[9];
    strftime(datoString, 9, "%Y%m%d", localtime(&tidNaa));   // Formater dato som AAAAMMDD

    int dato = stoi(datoString);                             // Konverter til int

    return dato;
}


/**
 *  Sjekker innskreet dato er rimelig.
 * 
 *  @param  dag, mnd, aar - dato som skal skjekkes
 *  @return om datoen er OK eller ikke
*/
bool sjekkDato(int dag, int mnd, int aar) {
    return (dag >= 1 && dag <= 31) && (mnd >= 1 && mnd <= 12)
           && (aar >= 2000 && aar <= 2030);
}


/**
 *  Leser dato.
 * 
 *  @see bool sjekkDato(...)
 *  @return dato 
*/
int lesDato() {
    int dag = 0, mnd = 0, aar = 0;

    do {
        cout << "\tUtlopsdato (<DD> <MM> <AAAA>): "; cin >> dag >> mnd >> aar;
    } while (!sjekkDato(dag, mnd, aar));

    return (aar * 10000 + mnd * 100 + dag);
}


/**
 * Omforer gitt stringtil store bokstaver
 * 
 * @return up-caset string 
*/
string toUpper(string& navn) {
    for (auto it = navn.begin(); it != navn.end(); it++) {
        *it = toupper(*it);
    }
    return navn;
}