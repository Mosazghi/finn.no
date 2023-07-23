#include <iostream>
#include <fstream>
#include "kategorier.h"
#include "LesData3.h"
#include "kunder.h"
#include "Funksjoner.h"
#include "const.h"
#include <iomanip>
#include <algorithm>

using namespace std;


extern Kunder gKundebase; // Global container for ALLE kundene


/**
 *  Lar brukeren skrive en type kategori, lage en ny og srkive om en kategori.
 *  Lar brukeren ogs lage en ny ting, endre en ting og kjpe en ting.
 *
 *  @param char valg - hjelpevariabel for valget mellom nyTing, kategori og kjp.
 *  @see void Kategorier::skrivTypeKategorier()
 *  @see void Kategorier::nyKategori()
 *  @see void Kategorier::skrivOmEnkategori()
 *  @see void Kategorier::opprettTing()
 *  @see void Kategorier::endreTingKategorier()
 *  @see int  lesDato()
 *  @see void Kategorier::slettTing(...)
 *  @see void Kategorier::kjop()
*/
void Kategorier::handling(char valg) {
    char kommando;
    int dato = 0;

    if (valg != 'K') {
        cin >> kommando;
        kommando = toupper(kommando);

        switch (valg) {
            case 'A':
                switch (kommando) {
                    case 'A': skrivTypeKategorier();							break;
                    case 'N': nyKategori();												break;
                    case 'S': skrivOmEnKategori();								break;
                    default: cout << "\nUdefinert kommando!\n";		break;
                } break;

            case 'T':
                switch (kommando) {
                    case 'N': opprettTing();											break;
                    case 'E': endreTingKategorier();							break;
                    case 'F': dato = lesDato(); slettTing(dato);	break;
                    default: cout << "\nUdefinert kommando!\n";		break;
                } break;

            default: cout << "\nUdefinert valg!\n";						break;
        }
    }
    else {
        cin.ignore();
        kjop();
    }
}


/**
 *  Leser fra filen Kategorier.dta.
 *
 *  @see string toUpper(...)
 *  @see Kategori::Kategori(...)
*/
void Kategorier::lesFraFil() {
    string katNavn;
    ifstream fil("/home/mosazghi/CLionProjects/finn.no-copy/finn.no/source/kategorier.dta");

    if (fil) {
        cout << "\n\nLESER FRA 'KATEGORIER.DTA'...\n\n";
        fil >> sisteNr >> antKat;

        for (int i = 1; i <= antKat; i++) {			// Opptil antall kategorier
            fil >> katNavn; toUpper(katNavn);
            gKategorier[katNavn] = new Kategori(fil, katNavn);
        }

        fil.close();
    }
    else
        cout << "\n\nFINNER IKKE 'KATEGORIER.DTA'!\n\n";
}


/**
 *  Skriver til filen Kategorier.dta.
 *
 *  @see void Kategori::skrivTilFil(...)
*/
void Kategorier::skrivTilFil() {
    ofstream fil("/home/mosazghi/CLionProjects/finn.no-copy/finn.no/source/kategorier.dta");

    if (fil) {
        cout << "\n\nSKRIVER TIL 'KATEGORIER.DTA'...\n\n";
        fil << sisteNr << ' ' << antKat << '\n';

        for (const auto& val : gKategorier) {
            fil << '\n' << val.first << '\n';
            val.second->skrivTilFil(fil);
        }
    }
    else
        cout << "\n\nFINNER IKKE 'KATEGORIER.DTA'!\n\n";
}


/**
 *  Skriver alle, kun nye eller kun brukte kategorier.
 *
 *  @see int Kategori::skrivAntallTypeTing(...)
 *  @see int Kategori::getAntTing()
*/
void Kategorier::skrivTypeKategorier() const {
    char valg;
    bool ting					= false,
            nyEllerBrukt = false;

    if (!gKategorier.empty()) {
        do {
            valg = lesChar("a(lle), n(ye) eller b(rukte)?");
        } while (valg != 'A' && valg != 'N' && valg != 'B');

        nyEllerBrukt = valg == 'N' || valg == 'B';

        cout << (nyEllerBrukt ? (valg == 'N' ? "\n\nAntall nye ting:\n\n"
                                             : "\n\nAntall brukte ting:\n\n")
                              : "\n\nFolgende tilgjengelige kategorier:\n\n");

        for (const auto& val : gKategorier) {
            cout << "\t" << left << setw(15) << val.first
                 << setw(40) << "Antall ting til salgs:"
                 << (nyEllerBrukt ? (val.second)->skrivAntallTypeTing(valg)
                                  : (val.second)->getAntTing()) << '\n';
        }
    }
    else
        cout << "\nIngen tilgjengelige kategorier!\n";
}


/**
 *  Lar brukeren lage en ny kategori.
 *
 *  @see string toUpper(...)
 *  @see Kategori::Kategori()
*/
void Kategorier::nyKategori() {
    string katNavn;
    cin.ignore();

    cout << "\nOPPRETTER EN NY KATEGORI...\n\n";
    do {
        cout << "\tKategori navn: ";
        getline(cin, katNavn);
    } while (katNavn.empty());

    katNavn = toUpper(katNavn);
    auto it = gKategorier.find(katNavn);

    if (it == gKategorier.end())
        gKategorier[katNavn] = new Kategori();
    else
        cout << "\nKategorien finnes allerede!\n";
}


/**
 *  Lar brukeren opprette en ny ting innenfor en valgt kategori.
 *
 *  @see string Kategorier::finnesKat(...)
 *  @see Kunde* Kunder::finnesKunde(...)
 *  @see void   Kategori::lesDataTing(...)
*/
void Kategorier::opprettTing() {
    string katNavn;
    int kundeNr = 0;
    cin.ignore();

    if (!gKategorier.empty()) {
        do {
            cout << "\nTast inn kategori navn du vil fylle: ";
            getline(cin, katNavn);
        } while (katNavn.empty());

        if (auto it = finnesKat(katNavn)) {				// Finnes/entydig kategori(navn)
            kundeNr = lesInt("Hva er kundenr. ditt?", 1, MAXANTALLKUNDER);

            auto kunde = gKundebase.finnesKunde(kundeNr);

            if (kunde) {
                sisteNr++;
                (*it).lesDataTing(kundeNr, sisteNr);
                kunde->endreAntTilSalg();
            }
            else
                cout << "\nKundenummeret finnes ikke...\n";
        }
        else
            cout << "\nKategorien er ikke entydig/finnes ikke!\n";
    }
    else
        cout << "\nIngen tilgjengelige kategorier!\n";
}


/**
 *  Lar brukeren endre en gjenstand i en valgt kategori.
 *
 *  @see Kategori*	Kategori::finnesKat(...)
 *  @see void				Kategorier::skrivKategori(...) const
 *  @see string			KAtegori::getNavn()
 *  @see void				Kategori::endreTing()
*/
void Kategorier::endreTingKategorier() {
    string kategori;

    if (!gKategorier.empty()) {
        cin.ignore();
        do {
            cout << "Hvilken kategori befinner den seg i?: ";
            getline(cin, kategori);
        } while (kategori.empty());

        if (auto it = finnesKat(kategori)) {
            skrivKategori((*it).getNavn());
            (*it).endreTing();
        }
        else
            cout << "\nKategorien er ikke entydig/finnes ikke!\n";
    }
    else
        cout << "\nIngen tilgjengelige kategorier!\n";
}


/**
 *  Skriver ut en valgt kategori.
 *
 *  @param  kategori - kategori navnet
 *  @see		void Kategori::skrivTing(...)
*/
void Kategorier::skrivKategori(const string kategori) const {
    cout << "\nSkriver '" << kategori << "'s ting...\n" ;
    auto it = gKategorier.find(kategori);

    if (it != gKategorier.end())
        (*it).second->skrivTing();
}


/**
 *  Skriver ut data til tingen til en valgt kategori.
 *
 *  @see Kategori*	Kategori::finnesKat(...)
 *  @see string			Kategori::getNavn(...)
 *  @see void				Kategori::skrivDataTypeTing(...)
*/
void Kategorier::skrivOmEnKategori()  {
    string kategori;
    char valg;
    bool nyEllerBrukt = false;
    cin.ignore();

    if (!gKategorier.empty()) {
        do {
            cout << "\nTast inn kategori: ";
            getline(cin, kategori);
        } while (kategori.empty());

        if (auto it  = finnesKat(kategori)) {
            do {
                valg = lesChar("a(lle), n(ye) eller b(rukte)?");
            } while (valg != 'A' && valg != 'B' && valg != 'N');

            nyEllerBrukt = valg == 'N' || valg == 'B';

            cout << (nyEllerBrukt ? (valg == 'N' ? "\n\nAlle tilgjengelige nye ting"
                                                 : "\n\nAlle tilgjengelige brukte ting")
                                  : "\n\nALLE tilgjengelige ting") << " i '" << (*it).getNavn()
                 << "' (" << (*it).getAntTing() << " ting):\n";

            (*it).skrivDataTypeTing(valg);
        }
        else
            cout << "\nKategorien er ikke entydig/finnes ikke!\n";
    }
    else
        cout << "\nIngen tilgjengelige kategorier!\n";
}


/**
 *  Lar brukeren kjpe en gjenstand fra en valgt kategori.
 *
 *  @see Kunde*			Kunder::finnesKunde(...)
 *  @see Kategori*	Kategorier::finnesKat(...)
 *  @see void				Kategorier::skrivKategori(...) const
 *  @see int				Kategori::kjop(...)
 *  @see void				Kategori::oppdatter(...)
*/
void Kategorier::kjop() {
    string katNavn;
    int kjopValg = 0;
    int kunde = 0;

    if (!gKategorier.empty()) {
        kunde = lesInt("\tHva er kundenummeret ditt? ", 1, 100);
        auto sjekk = gKundebase.finnesKunde(kunde);					// Sjekker om kunden finnes

        if (sjekk) {

            do {
                cout << "\tHvilken kategori har du lyst til aa kjope fra? ";
                getline(cin, katNavn);
            } while(katNavn.empty());


            if (auto it = finnesKat(katNavn)) {
                skrivKategori((*it).getNavn());
                cout << '\n';

                kjopValg = (*it).kjop(kunde);

                if (kjopValg != 0 && kjopValg != -1)
                    (*it).oppdatter(kjopValg, kunde);
                else
                    cout << (kjopValg == -1 ? "\nDu kan ikke kjope noe du eier!\n"
                                            : "\nIngenting ble kjopt!\n");
            }
            else
                cout << "\nKategorien er ikke entydig/finnes ikke!\n";
        }
        else
            cout << "\nDenne kunden finnes ikke!\n";
    }
    else
        cout << "\nIngen tilgjengelige kategorier!\n";
}



/**
 * Returnerer (om mulig) gjenstand med hel/delvis match kateogri navn.
 *
 * @param    katNavn -  kategori det skes etter
 * @return   Peker til funnet kategori, nullptr eller
 * @see      string toUpper(...)
*/
Kategori* Kategorier::finnesKat(string& katNavn) {
    int funn = 0;
    Kategori* kategori = nullptr;
    katNavn = toUpper(katNavn);

    for (const auto& val : gKategorier) {
        if (!val.first.compare(0, katNavn.size(), katNavn)) {
            ++funn;
            kategori = dynamic_cast<Kategori*>(val.second);		// Henter funnet kategori peker
        }
    }

    return funn == 1 ? kategori : nullptr;			// Returnerer funnet kategroi hvis entydig
    // (ikke flere enn en funn)
}



/**
 *  Sletter ting i ulike kategorier som er FR dato.
 *
 * @param  dato - angitt dato
 * @see    void Kategori::slettUtlopteTingz(...)
*/
void Kategorier:: slettTing(const int long dato) {
    for (const auto& val : gKategorier) {
        val.second->slett(dato);
    }
}


/**
 * Ser kundens ting i ulike kategorier.
 *
 * @param   kNr - ting med kundenummer det skal skes etter
 * @see     bool Kategori::slettTingMedKNr()
 * @return  sann hvis enten det ikker er funn etter ting,
            eller hvis kunden har fjernet de
*/
bool Kategorier::funnetEllerFjernetTing(const int kNr) {
    for (auto& val : gKategorier) {
        cout << "\nSer etter om du har ting i '" << val.first << "'...\n\n";
        if (!val.second->slettTingMedKNr(kNr))
            return false;
    }
    return true;
}


/**
 *  Deallokerer minne
 *
 *  @see ~Kategori()
*/
void Kategorier::deAlloker() {
    for (auto& i : gKategorier) {
        i.second->~Kategori();
    }
    gKategorier.clear();
}
