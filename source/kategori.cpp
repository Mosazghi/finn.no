#include <iostream>
#include <algorithm>
#include "kategori.h"
#include "LesData3.h"
#include "BruktTing.h"
#include "Funksjoner.h"
#include "nyting.h"
#include "kunder.h"

using namespace std;

extern Kunder gKundebase;

/**
 * Kategori decontructor. 
*/
Kategori::~Kategori() {
    for (auto& i : gjenstander)
        delete i; // sletter ALLE gjenstander (Ny/Brukt ting)
    gjenstander.clear();
}


/**
 *  Tom Kategori contructor.
*/
Kategori::Kategori() {

}


string Kategori::getNavn() {
    return navn;
}

/**
 *  Leser inn data fra filen Kategorier.dta.
 * 
 *  @param inn - put pointer (plassering)
 *  @param katNavn - unik kategori navn
*/
Kategori::Kategori(ifstream& inn, string katNavn) {
    navn = katNavn;
    int size = 0;
    char type;

    inn >> size;

    for (int i = 1; i <= size; i++) {
        inn >> type;
        switch (type) {
            case 'N': gjenstander.push_back(new NyTing(inn, 'N'));		   break;
            case 'B': gjenstander.push_back(new BruktTing(inn, 'B'));    break;
        }
    }
}



/**
 *  Skriver til filen Kategorier.dta kategori navn og resten av dataene.  
 * 
 *  @param ut - put pointer (plassering)
 *  @param kategoriNavn - navnet til hoved kategorien
 *  @see virtual void NyTing::skrivTilFil(...)
*/
void Kategori::skrivTilFil(ofstream& ut) {
    ut << gjenstander.size() << '\n';
    for (const auto& i : gjenstander)
        i->skrivTilFil(ut);
}


/**
 *  Returnerer antall gjenstander.
 * 
 *  @return antall ting i kategorien
*/
int Kategori::getAntTing() {
    return gjenstander.size();
}


/**
 *  Skriver antall Ny/Brukt ting.
 * 
 *  @param type - type til gjenstanden (Ny/Brukt)
 *  @return n eller b - antallet nye eller brukte ting i kategorien 
*/
int Kategori::skrivAntallTypeTing(char type) {
    int n = 0, b = 0;													// ant. nye og brukte ting

    // Finner og returnerer (om mulig) antall nye ting
    n = count_if(gjenstander.begin(), gjenstander.end(),
                 [](const auto& val) {return !dynamic_cast<BruktTing*>(val); });

    return (type == 'N' ? n : (getAntTing() - n));
}


/**
 *  Leser inn dataene til en Ny/Brukt ting.
 * 
 *  @param kunde - kundenummeret
 *  @param neste - neste nummer i gjenstand listen
 *  @see NyTing::NyTing(...)
 *  @see BruktTing::BruktTing(...)
*/
void Kategori::lesDataTing(int kunde, int neste) {
    char type;

    do {
        type = lesChar("B(rukt) eller N(y) gjenstand?");
    } while (type != 'N' && type != 'B');

    switch (type) {
        case 'N':	gjenstander.push_back(new NyTing(kunde, neste, 'N'));    break;
        case 'B':	gjenstander.push_back(new BruktTing(kunde, neste, 'B')); break;
    }
}


/**
 *  Lar brukeren endre en Ny/Brukt ting.
 * 
 *  @see int          Kategori::getHoyesteTingNr()
 *  @see virtual int  NyTing::getNr()
 *  @see virtual void NyTing::endreData()
 *  @see void         skrivMeny()
*/
void Kategori::endreTing() {
    int nr;
    bool funn = false;

    if (!gjenstander.empty()) {
        nr = lesInt("\nVelg tingnr", 0, getHoyesteTingNr());

        if (nr) {
            for (const auto& val : gjenstander) {
                if (val->getInfo('N') == nr) {
                    val->endreData();
                    funn = true;
                }
            }
            if(!funn)
                cout << "\nUgylidg nummer!\n";
        }
        else
            skrivMeny();
    }
    else
        cout << "\nTom for gjenstander for denne kategorien!\n";
}


/**
 *  Skriver dataene til en Ny/Brukt ting.
 * 
 *  @param viseKNr - hjelpe variabel for � vise kundenummer
 *  @see virtuall void NyTing::skrivdata() const
*/
void Kategori::skrivTing() const {

    if (!gjenstander.empty()) {
        for (const auto& val : gjenstander)
            val->skrivData();
    }
    else
        cout << "\nTom for gjenstander!\n";
}


/**
 *  Henter den h�yeste unike Ny/Brukt ting nummer.
 * 
 *  @see virtual int NyTing::getNr()
 *  @return max - st�rste unike nummer
*/
int Kategori::getHoyesteTingNr() {
    int max = 0;

    for (const auto& val : gjenstander) {
        if (val->getInfo('N') > max)
            max = val->getInfo('N');
    }
    return max;
}


/**
 *  Lar brukeren velge en Ny/Brukt ting til � kj�pe. 
 * 
 *  @param kundeNr - kundenummeret til brukeren
 *  @see int  Kategori::lesInt(...)
 *  @see bool NyTing::sjekkKunde(...)
 *  @return den valgte gjenstanden
*/
int Kategori::kjop(int kundeNr) {
    int valg = 0;
    bool sjekk = false;

    valg = lesInt("\n\tVelg gjenstand?"
            , 0, getHoyesteTingNr());

    for (auto& i : gjenstander) {
        if (kundeNr == i->sjekkKunde(kundeNr, valg))
            sjekk = true;
    }

    return (!sjekk ? valg : -1);
}


/**
 *  Oppdatterer kunde info og antall til salg etter kjp.
 *
 *  @param valgNr - unike ting nummer
 *  @param kjoperNr - kjperens kundenummer
 *  @see void         Kategori::oppdatter(...)
 *  @see virtual int  NyTing::getNr()
 *  @see virtual void NyTing::oppdatter(...)
 *  @see void         Kategori::slett(...)
*/
void Kategori::oppdatter(int valgNr, int kjoperNr) {
    auto it = gjenstander.front();

    for (auto& i : gjenstander) {
        if (valgNr == i->getInfo('N'))
            i->kjopGjenstand(kjoperNr);
    }
    slett(1); // random int inni for  oppfylle argumentet
}


/**
 *  Skriver ut dataene til en gjenstand basert p� typen.
 * 
 *  @param type - hva salgs type gjenstand den er
 *  @see virtual void NyTing::skrivData() const 
 *  @see virtual void BruktTing::skrivData() const 
*/
void Kategori::skrivDataTypeTing(char type) const {
    for (const auto & val : gjenstander) {
        switch(type) {
            case 'N':
                if (auto bruktTing = dynamic_cast<BruktTing*>(val)) // Hvis nyTing
                    continue;
                val->skrivData();									break;

            case 'B':
                if (auto bruktTing = dynamic_cast<BruktTing*>(val)) // Hvis BruktTing
                    bruktTing->skrivData();				break;

            default: val->skrivData();					break;
        }
    }
}


/**
 * Fjerner alle utl�pte/utsolgte gjenstander fra gjenstand listen. 
 *  
 * @param const long int dato - datoen til gjenstanden
 * @see int getUtlopsDato()
 * @see int getInfo(...)
*/
void Kategori::slett(const long int dato) {
    int antall = 0;		// Antall slettede ting

    // Flytter alle ikke-utl�pte-ting forrest i listen (sortert)
    // og returnerer en ny iterator som peker ETTER siste ikke-utl�pt-ting (new end)
    auto it = remove_if(gjenstander.begin(), gjenstander.end(),
                        [&dato](const auto& val)-> bool {
                            return (val->getUtlopsDato() < dato || val->getInfo('A') == 0); });

    auto n = it;																// Orginal new end

    if (it != gjenstander.end()) {
        for (; it != gjenstander.end(); it++) {		// Finner aktuell kunde
            // Mislykkede fors�k p� � oppdatere aktuell kunder med utg�tte ting.
            //auto kunde = gKundebase.finnesKunde((*it)->getInfo('S'));
            //(*kunde).synkSalgsAntall();							// Oppdaterer aktuell kunder
            delete* it;															// Sletter tilpekt objekter
        }

        //SLETTER alle peker fom. new end tom. siste utl�pte-ting.
        gjenstander.erase(n, gjenstander.end());
    }
}


/**
 * Funksjonen kj�res bare hvis kunden har ting i systemet. 
 * Hvis funn, lar brukeren slette tingene f�rst. 
 * Hvis ikke funn, sletter brukeren umiddelbart.
 * 
 * @param kNr - kundenummer som ting skal s�kes med 
 * @see int getInfo(...)
 * @return true hvis enten det er funnet noe, eller hvis brukeren sletter dem
 *				 false hvis brukeren angrer 
*/
bool Kategori::slettTingMedKNr(const int kNr) {
    char bekreft;
    int antall = 0;

    // Finner (om mulig) antall til salgs av kunden
    antall = count_if(gjenstander.begin(), gjenstander.end(),
                      [&kNr](const auto& val) {return val->getInfo('S') == kNr; });

    if (!antall) return true;			// Hopper rett ut (og sletter kunden) hvis ikke noe funn

    // "Skyver" vekk alle tingene av kunden etter nye end
    auto it = remove_if(gjenstander.begin(), gjenstander.end(),
                        [&kNr](const auto & val) {return val->getInfo('S') == kNr; });

    cout << "\tOops.. Du har " << antall << " usolgt(e) ting. "
         << "VIL DU FORSETTE/SLETTE DEM?\n ";

    do {
        bekreft = lesChar("\t\tVELG (J/N)");
    } while (bekreft != 'J' && bekreft != 'N');

    if (bekreft == 'J')  {
        gjenstander.erase(it, gjenstander.end());
        cout << "\nTing(ene) i denne kategorien er fjernet!\n";
        return true;
    }
    else {
        cout << "\nOK - hverken kunden eller ting(ene) i denne kategorien er fjernet!\n";
        return false;
    }
}