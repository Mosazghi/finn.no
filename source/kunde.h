#ifndef __KUNDE_H
#define __KUNDE_H

#include <fstream>
#include <string>

/**
 * Kunde (kundenummer, tlf.nr., postnr., antall (kjpt, solgt og til salgs),
         navn, gateadresse, poststed og epost).
*/
class Kunde {
private:
    int kundeNr,
            mobilNr,
            postNr,
            antKjopt,
            antSolgt,
            antTilSalgs;

    std::string navn,
            gateadresse,
            poststed,
            email;
public:
    Kunde();
    Kunde(std::ifstream& inn);
    int getKundeNr();
    int getAntTilSalgs();
    void skrivData() const;
    void skrivAlleData() const;
    void lesData(int nr);
    void skrivTilFil(std::ofstream& ut);
    void okAntKjopt();
    void synkSalgsAntall();
    void okAntSolgt();
    void endreAntTilSalg();
    int hentID();
};
#endif