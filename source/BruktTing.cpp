#include <iostream>
#include "LesData3.h"
#include "BruktTing.h"
#include "Funksjoner.h"
#include "const.h"
#include "kategori.h"
#include "kategorier.h"

using namespace std;

extern Kategorier gKategoribase;

/**
 * Default BruktTing constructor.
*/
BruktTing::BruktTing() {
    alder = 0;
    ting = static_cast<Tilstand>(-1);
}


/**
*  Henter tingens unike nummer, antallet og selgernummer.
*/
int BruktTing::getInfo(char valgInfo){
    switch (valgInfo) {
        case 'N': return nr;			    break;
        case 'A': return antTilSalg;		break;
        case 'S': return selgerNr;			break;
        default:  return -1;				break;
    }
}


/**
 *  Henter utl�psdato til tingen.
*/
int BruktTing::getUtlopsDato() {
    return utlopsDato;
}


/**
 *  BruktTing constructor for � lese inn data fra fil.
 *
 *  @param inn, type - hjelpevariabler
*/
BruktTing::BruktTing(ifstream& inn, char type) : NyTing(inn, type) {
    int tilstand = 0;
    typeGjenstand = type;

    inn >> alder >> tilstand;
    ting = static_cast<Tilstand>(tilstand);		// Caster til enum verdi
}


/**
 *  BruktTing constructor for � legge til en brukt ting.
 */
BruktTing::BruktTing(int plass, int nesteNr, char type) : NyTing(plass, nesteNr, type){
    int tilstand = 0;
    typeGjenstand = type;

    cin.ignore();
    alder = lesInt("\tHvor gammel (i mnd.)? ", 1, MAXALDER);
    tilstand = lesInt("\tTilstand? 0 (best) - 4 (vaerst)", 0, 4);
    ting = static_cast<Tilstand>(tilstand);		// Caster til enum verdi
}


/**
 * Skriver til fil kategorier.dta.
 *
 * @param ut - filobjektet/put pointer
 * 
 * @see virtual void NyTing::skrivTilFil(...)
*/
void BruktTing::skrivTilFil(ofstream& ut) {
    NyTing::skrivTilFil(ut);
    ut << alder << " " << ting << '\n';
}


/**
 *  Skriver data om tingen, type BruktTing
*/
void BruktTing::skrivData() const {
    cout << "\n\t" << nr << ": BRUKT - " << navn
         << "\n\t\t Pris: " << pris
         << ", Antall tilgjengelig: " << antTilSalg
         << "\n\t\t " << alder << " mnd. gammel,";
    switch (ting) {
        case somNy: cout << " Som Ny";         break;
        case PentBrukt: cout << "Pent Brukt";  break;
        case Brukt: cout << " Brukt";          break;
        case GodtBrukt: cout << " Godt Brukt"; break;
        case Sliten: cout << " Sliten";        break;
    };
    cout << "\n\t\t " << beskrivelse;
}


/**
 *  Endrer data av typen BruktTing.
 *
 *  @see int  lesDato()
 *  @see void skrivMeny()
*/
void BruktTing::endreData() {
    int tilstand = 0;
    int valg = 0;

    valg = lesInt("1=navn, 2=beskrivelse, 3=pris, 4=antall, 5=alder, 6=kvalitet"
            , 0, 6);

    switch (valg) {
        case 1: cout << "\n\tNytt navn: ";           getline(cin, navn);        break;
        case 2: cout << "\n\tNy beskrivelse:\n\t\t"; getline(cin, beskrivelse); break;
        case 3: pris     = lesInt("\n\tNy pris", 1, MAXPRIS);	                  break;
        case 4:	antTilSalg = lesInt("\n\tNytt antall (0=slett)", 0, MAXANTALL); break;
        case 5: alder    = lesInt("\n\tNy alder (i mnd.)", alder, MAXALDER);	  break;
        case 6: tilstand = lesInt("\n0=Som Ny, 1=Pent Brukt, 2=Brukt, 3=Godt Brukt, 4=Sliten"
                    , 0, 4);
            ting = static_cast<Tilstand>(tilstand);		                      break;
        default: skrivMeny();                                                   break;
    }
}


/**
 *  kj�per den brukte gjenstanden.
 *
 *  @param kjopNr - kj�perens kundenummer
 *  @see virtual void  NyTing::kjopGjenstand(...)
*/
void BruktTing::kjopGjenstand(int kjoperNr) {
    NyTing::kjopGjenstand(kjoperNr);
}