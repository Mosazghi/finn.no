#include <iostream>
#include <fstream>
#include "kunde.h"
#include <iomanip>
#include "LesData3.h"

using namespace std;


/**
 * Default Kunde constructor.
*/
Kunde::Kunde() {
    postNr = mobilNr = kundeNr = antKjopt = antSolgt = antTilSalgs = 0;
}

/**
 *  Kunde constructor med innlesning av fil.
 * 
 *  @param inn - filobjektet 
*/
Kunde::Kunde(ifstream& inn) {
    inn >> kundeNr >> mobilNr >> postNr >> antKjopt >> antSolgt >> antTilSalgs;
    inn.ignore();

    getline(inn, navn);
    getline(inn, gateadresse);
    getline(inn, poststed);
    getline(inn, email);
    inn.ignore();
}


/**
 *  Henter kundenummeret.
*/
int Kunde::getKundeNr() {
    return kundeNr;
}


/**
 *  Skriver til fil. kunder.dta.
 * 
 *  @param ut - put pointer til filen
*/
void Kunde::skrivTilFil(ofstream& ut) {
    ut << kundeNr << ' ' << mobilNr << ' ' << postNr  << ' '
       << antKjopt << ' ' << antSolgt << ' ' << antTilSalgs
       << '\n' << navn << '\n' << gateadresse << '\n' << poststed
       << '\n' << email << '\n';
}


/**
 *  Henter antall salgs av kunden.
*/
int Kunde::getAntTilSalgs() {
    return antTilSalgs;
}


/**
 *  Skriver alle data om kunden.
*/
void Kunde::skrivAlleData() const {
    cout << "\n\t\tNavn: " << navn
         << "\n\t\tPoststed: " << poststed << "\n\t\tPostnummer: "
         << postNr << "\n\t\tGateadresse: " << gateadresse <<  "\n\t\tEmail: "
         << email << ", tlf.: " << mobilNr << "\n\t\tAntall kjopt: "
         << antKjopt << ", antall solgt: " << antSolgt
         << ", antall til salg: " << antTilSalgs << "\n\n";
}


/**
 *  Skriver kun kundenr., navn og tlf.nr.
*/
void Kunde::skrivData() const {
    cout << "\n\t" << kundeNr << ": " << navn
         <<",   tlf: " << mobilNr;
}


/**
 *  Leser alle data om kunden.
 * 
 *  @param nr - hjelpevariabel
*/
void Kunde::lesData(int nr) {
    cin.ignore();

    kundeNr = nr; // fyller inn med nummere
    cout << "\n\tNavnet ditt: "; getline(cin, navn);
    cout << "\tE-post adressen din: "; getline(cin, email);
    mobilNr = lesInt("\tTlf.nummeret ditt", 11111111, 99999999); // var en ekstra nummer her
    cout << "\tGateadresse: "; getline(cin, gateadresse);
    cout << "\tPoststed: "; getline(cin, poststed);
    postNr = lesInt("\tPostnummer", 1000, 9999);

    antKjopt = antSolgt = antTilSalgs = 0;
}


/**
 *  �ker antall til salgs.
*/
void Kunde::endreAntTilSalg() {
    antTilSalgs++;
}


/**
 *  �ker antall kjpt.
*/
void Kunde::okAntKjopt() {
    antKjopt++;
}


/**
 *  �ker antall solgt.
*/
void Kunde::okAntSolgt() {
    antSolgt++;
}


/**
 *  Minker antall til salgs.
*/
void Kunde::synkSalgsAntall() {
    antTilSalgs--;
}


/**
 * Henter kundens ID.
*/
int Kunde::hentID() {
    return kundeNr;
}