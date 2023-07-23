#ifndef __NYTING_H
#define __NYTING_H

#include <string>
#include <fstream>
#include <list>


/**
 * NyTing (med UNIKT nummer, navn, pris, antall til salgs, utlpsdato, og beskr.).
*/
class NyTing {
protected:
    int		nr,
            selgerNr,
            pris,
            antTilSalg,
            utlopsDato;
    std::string navn,					// navnet til gjenstanderen
    beskrivelse;
    char typeGjenstand;

public:
    NyTing();
    NyTing(int kundeNum, int nesteNr, char type);
    NyTing(std::ifstream& inn, char type);
    virtual void skrivData() const;
    virtual void skrivTilFil(std::ofstream& ut);
    virtual void endreData();
    virtual void kjopGjenstand(int kjoperNr);
    virtual int getInfo(char valgtInfo);
    int getUtlopsDato();
    bool sjekkKunde(int kunde, int valgNr);
};
#endif