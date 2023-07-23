#include <iostream>
#include <fstream>
#include "kunder.h"
#include "LesData3.h"
#include "kategorier.h"
#include "Funksjoner.h"
#include <algorithm>

using namespace std;

extern Kategorier gKategoribase;  /// Global container for ALLE kategoriene


/**
 *  Lar brukeren skrive alle/en kunde, lage en kunde, og slette en kunde.
 * 
 *  @see void Kunder::nyKunde()
 *  @see void Kunder::skrivAlleKunder() const
 *  @see void Kunder::skrivDataKundeNr(...) const
 *  @see void Kunder::slettKundeNr(...)
*/
void Kunder::handling() {
    char kommando;
    cin.ignore();
    cin >> kommando;                            // Leser inn neste char
    kommando = toupper(kommando);
    int kundeNr = 0;


    switch (kommando) {
        case 'N': nyKunde();                             break;
        case 'A': skrivAlleKunder();                     break;
        case 'S': cin.ignore(); kundeNr = lesInt("Kundenummer:", 0, sisteNr);
            skrivDataKundeNr(kundeNr);             break;
        case 'F': cin.ignore(); kundeNr = lesInt("Kundenummer:", 0, sisteNr);
            slettKundeNr(kundeNr);                 break;
        default: cout << "\nUdefinert kommando!\n";      break;
    }

}


/**
 *  Leser data fra filen Kunder.dta.
 * 
 *  @see Kunde::Kunde(...)
*/
void Kunder::lesFraFil() {
    ifstream fil("/home/mosazghi/CLionProjects/finn.no-copy/finn.no/source/kunder.dta");

    if (fil) {
        cout << "\n\nLESER FRA 'KUNDER.DTA'...\n\n";
        fil >> sisteNr;

        while (!fil.eof()) {
            gKunderbase.push_back(new Kunde(fil));
        }
        fil.close();
    }
    else
        cout << "\n\nFINNER IKKE 'KUNDER.DTA'!\n\n";
}


/**
 *  Sammenligner parametern med alle kundenummrene lagret og returner resultatet.
 * 
 *  @param kunde - angitt kundenummer
 *  @see int Kunde::getKundeNr()
 *  @return - pekeren til objektet hvis funnet, nullptr ellers
*/
Kunde* Kunder::finnesKunde(int kunde) {
    auto it = find_if(gKunderbase.begin(), gKunderbase.end(),
                      [&kunde](const auto& val) {return val->getKundeNr() == kunde; });

    return (it != gKunderbase.end() ? (*it) : nullptr);
}


/**
 *  Lar brukren opprette en ny kunde. 
 * 
 *  @see void Kunde::lesData(...)
*/
void Kunder::nyKunde() {
    cout << "\nOPPRETTER EN NY KUNDE..."
         << "\n\n\t\tDitt kundenummer er: " << ++sisteNr << endl;

    Kunde* nyKunde = new Kunde();
    nyKunde->lesData(sisteNr);
    gKunderbase.push_back(nyKunde);

    gKunderbase.sort([](Kunde* k1, Kunde* k2)       // Sorterer
                     { return (k1->hentID() < k2->hentID()); });
}


/**
 *  Skriver ut alle kunder info, antallet kunder og det siste kundenummret brukt.
 * 
 *  @see void Kunde::skrivData()
*/
void Kunder::skrivAlleKunder() const {
    int i = 0;

    cout << "\nSiste kundenummer brukt hittil: " << sisteNr
         << "\nDet er foreløpig " << gKunderbase.size() << " kunder.\n";

    for (const auto& val : gKunderbase) {
        val->skrivData();
        if ((i % 5) == 0) getchar();
        i++;
    }
}


/**
 *  Skriver til filen Kunder.dta.
 * 
 *  @see void Kunder::skrivTilFil(...)
*/
void Kunder::skrivTilFil() {
    ofstream fil("/home/mosazghi/CLionProjects/finn.no-copy/finn.no/source/kunder.dta");

    if (fil) {
        cout << "\n\nSKRIVER TIL 'KUNDER.DTA'...\n\n";
        fil << sisteNr << '\n';

        for (auto& i : gKunderbase) {
            fil << "\n";
            i->skrivTilFil(fil);
        }
        fil.close();
    }
    else
        cout << "\n\nFINNER IKKE 'KUNDER.DTA'!...\n\n";
}


/**
 *  Skriver dataen til en valgt kunde.
 * 
 *  @param kNr - valgt kundenummer 
 *  @see int Kunde::getKundeNr()
 *  @see void Kunde::skrivAlleData()
*/
void Kunder::skrivDataKundeNr(const int kNr) const {
    if (kNr) {
        bool finnes = false;

        if (!gKunderbase.empty()) {
            // Finner (om mulig kunden)
            auto it = find_if(gKunderbase.begin(), gKunderbase.end(),
                              [&kNr](const auto& val) {return val->getKundeNr() == kNr; });

            if (it != gKunderbase.end()) {
                cout << "\nINFO OM KUNDENR. " << kNr << ":\n";
                (*it)->skrivAlleData();
            }
            else
                cout << "\nFinner ingen med dette kundenummeret!\n";
        }
        else
            cout << "\nDet er foreløpig ingen registrerte kunder!\n";
    }
    else
        skrivMeny();
}


/**
 *  Fjerne (hvis ønsket) en valgt kunde.
 * 
 *  @param const int kNr - valgt kundenummer
 *  @see Kunde* Kunde::finnesKundeNr(...)
 *  @see void Kunde::skrivAlleData()
 *  @see bool Kategorier::slettTingMedKNr(...)
 *  @see int Kunde::getKundeNr(...)
*/
void Kunder::slettKundeNr(const int kNr) {
    bool finnes = false;
    char bekreft;
    auto kunde = finnesKunde(kNr);      // Leter etter kunden
    bool fjernetNoe = false;

    if (!gKunderbase.empty()) {

        if (kunde) {                     // Hvis funn:
            kunde->skrivAlleData();
            do {
                bekreft = lesChar("\n\tVil du VIRKELIG slette? (j/n)");
            } while (bekreft != 'J' && bekreft != 'N');

            if (bekreft == 'J') {
                fjernetNoe = gKategoribase.funnetEllerFjernetTing(kNr);

                if (fjernetNoe) {
                    cout << "\n--Kunde med nr. " << kunde->getKundeNr()
                         << " er nå slettet fra systemet!!--\n";
                    delete kunde;
                    gKunderbase.remove(kunde);
                }
            }
            else
                cout << "\nOK - ikke slettet.\n";
        }
        else
            cout << "\nIngen kunde med dette numeret finnes!\n";
    }
    else
        cout << "\nDet er foreløpig ingen registrerte kunder!\n";
}


/**
 *  Oppdatterer antall kjøpt, solgt og antall til salg til selgeren og kunden.
 * 
 *  @param int kjoperNr - kundens nummer
 *  @param int selgerNr - selgerens nummer
 *  @param int salgsAntForSelger - antall gjenstander til salg
 *  @see int Kunde::getKundeNr()
 *  @see void Kunde::oppdatterKunde()
 *  @see void Kunde::oppdatterSalg()
 *  @see void Kunde::oppdatterSalgsAntall
*/
void Kunder::oppdatterInfo(int kjoperNr, int selgerNr, int salgsAntForSelger) {
    for (auto& i : gKunderbase) {
        // Oppdatterer info til kunden
        if (kjoperNr == i->getKundeNr())
            i->okAntKjopt();

        // Oppdatterer info til selgeren
        if (selgerNr == i->getKundeNr()) {
            i->okAntSolgt();
            if (salgsAntForSelger == 0)
                i->synkSalgsAntall();
        }
    }
}


/**
 * Deallokerer minne 
*/
void Kunder::deAlloker() {
    for (auto& i : gKunderbase)
        delete i;
    gKunderbase.clear();
}