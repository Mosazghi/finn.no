#include <iostream>
#include "nyting.h"
#include "LesData3.h"
#include "Funksjoner.h"
#include "const.h"
#include "BruktTing.h"
#include "kunder.h"
#include "kategorier.h"



using namespace std;

extern Kunder gKundebase;					// Global Kunder-constaier-objekt, hentet fra main.
extern Kategorier gKategoribase;	// Global Kategori-constaier-objekt, hentet fra main.

/**
 *  Default NyTing constructor.
*/
NyTing::NyTing() {
    utlopsDato = antTilSalg = selgerNr = nr = pris = 0; // Nullstiller
}

/**
 *  Henter tingens unike nummer, antallet og selgernummer.
*/
int NyTing::getInfo(char valgInfo) {
    switch (valgInfo) {
        case 'N': return nr;			    break;
        case 'A': return antTilSalg;  break;
        case 'S': return selgerNr;	  break;
        default:  return -1;				  break;
    }
}

/**
 *  Henter utlpsdato til tingen.
*/
int NyTing::getUtlopsDato() {
    return utlopsDato;
}


/**
 *  NyTing constructor for å legge til en ny gjenstand.
 *
 *  @param	plass, nesteNr, type - hjelpevariabler
 *  @see		int  lesDato(...)
*/
NyTing::NyTing(int kundeNum, int nesteNr, char type) {
    int dag = 0, mnd = 0, aar = 0;
    cin.ignore();

    nr = nesteNr;			// nye plass til gjenstanden
    selgerNr = kundeNum;
    typeGjenstand = type;

    do {
        cout << "\n\tHva heter den? ";
        getline(cin, navn);
    } while (navn.empty());

    pris = lesInt("\tPris ", 1, MAXPRIS);
    antTilSalg = lesInt("\tAntall som selges ", 1, MAXANTALL);

    do {
        cout << "\tSkriv en liten beskrivelse: ";
        getline(cin, beskrivelse);
    } while (beskrivelse.empty());

    utlopsDato = lesDato();
}


/**
 *  NyTing constructor for å lese inn data fra fil.
 *
 *  @param inn, type - hjelpevariabler
*/
NyTing::NyTing(ifstream& inn, char type) {
    typeGjenstand = type;
    inn.ignore();
    getline(inn, navn);
    getline(inn, beskrivelse);
    inn >> nr >> selgerNr >> antTilSalg >> pris >> utlopsDato;
}


/**
 *  Skriver til fil kategorier.dta.
 *
 *  @param ut - filobjektet/put pointer
*/
void NyTing::skrivTilFil(ofstream& ut) {
    ut << '\n' << typeGjenstand << '\n' << navn << '\n' << beskrivelse << '\n'
       << nr << ' '  << selgerNr << ' ' << antTilSalg << ' ' << pris
       << '\n' << utlopsDato << '\n';
}


/**
 *  Skriver data om tingen, type NyTing
*/
void NyTing::skrivData() const {
    cout << "\n\t" << nr << ": NY - " << navn
         << "\n\t\t Pris: " << pris
         << ", Antall tilgjengelig: " << antTilSalg
         << "\n\t\t " << beskrivelse;
}


/**
 *  Skjekker om en kunden eier gjenstanden.
 *
 *  @param	kunde, valgNNr - verdiene som skjekkes
 *  @return true hvis begge er like
*/
bool NyTing::sjekkKunde(int kunde, int valgNr) {
    return  (kunde == selgerNr) && (valgNr == nr);
}

/**
 *  Endrer data av typen NyTing.
 *
 *  @see int lesDato()
 *  @see void skrivMeny()
*/
void NyTing::endreData() {
    int valg = lesInt("1=navn, 2=beskrivelse, 3=pris, 4=antall, 5=dato", 0, 5);

    switch (valg) {
        case 1: cout << "\n\tNytt navn: "; getline(cin, navn);									break;
        case 2: cout << "\n\tNy beskrivelse:\n\t\t"; getline(cin, beskrivelse); break;
        case 3: pris = lesInt("\n\tNy pris", 1, MAXPRIS);												break;
        case 5: utlopsDato = lesDato();																					break;
        case 4:	antTilSalg = lesInt("\n\tNytt antall", 1, MAXANTALL);           break;
        default: skrivMeny();																										break;
    }
}


/**
 *  kjøper gjenstanden og oppdatterer informasjonen til kunden og selgeren.
 *
 *  @param	kjopNr - kjperens kundenummer 
 *  @see		void Kunde::oppdatter(...)
*/
void NyTing::kjopGjenstand(int kjoperNr) {
    antTilSalg--; // synker ned gjenstandens antall
    gKundebase.oppdatterInfo(kjoperNr, selgerNr, antTilSalg);
    cout << "\nFullfrt Handelen!\n";
}