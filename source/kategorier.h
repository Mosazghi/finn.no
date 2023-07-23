#ifndef __KATEGORIER_H
#define __KATEGORIER_H

#include <map>
#include <string>
#include "kategori.h"


/**
 * Kategori (med siste ting nummer og map av alle kategorier).
*/
class Kategorier {
private:
    int sisteNr,
            antKat;					// Antall kategorier
    std::map <std::string, Kategori*> gKategorier;
public:
    void handling(char valg);
    void lesFraFil();
    void skrivTilFil();
    void skrivTypeKategorier() const;
    void nyKategori();
    void opprettTing();
    void endreTingKategorier();
    void skrivKategori(const std::string kategori) const;
    void skrivOmEnKategori();
    void slettTing(const long int dato);
    void kjop();
    void deAlloker();
    Kategori* finnesKat(std::string& katNavn);
    bool funnetEllerFjernetTing(const int kNr);
};
#endif