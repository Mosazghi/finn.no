#ifndef __KATEGORI_H
#define __KATEGORI_H

#include <list>
#include "nyting.h"
#include "BruktTing.h"

/**
 * Kategori (med liste av gjenstander).
*/
class Kategori {
private:
    std::list <NyTing*> gjenstander;
    std::string navn;
public:
    ~Kategori();
    Kategori();
    Kategori(std::ifstream& inn, std::string kategoriNavn);
    void lesDataTing(int kunde, int neste);
    void KategoriLes(std::ifstream& inn, std::string navn);
    void skrivTilFil(std::ofstream& ut);
    void endreTing();
    void skrivTing() const;
    void oppdatter(int valgNr, int kjoperNr);
    void skrivDataTypeTing(char type) const;
    void slett(const long int dato);
    int skrivAntallTypeTing(char type);
    int getHoyesteTingNr();
    int kjop(int kundeNr);
    int getAntTing();
    bool slettTingMedKNr(const int kNr);
    std::string getNavn();
};
#endif