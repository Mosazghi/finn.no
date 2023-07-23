#ifndef __BRUKTTING_H
#define __BRUKTTING_H

#include "nyting.h"
#include "enum.h"


/**
 * BruktTing (med to tilleggs datamedlemmer).
*/
class BruktTing : public NyTing {
private:
    int alder;
    Tilstand ting;
    char typeGjenstand;

public:
    BruktTing();
    BruktTing(int plass, int nesteNr, char type);
    BruktTing(std::ifstream& inn, char type);
    virtual void skrivTilFil(std::ofstream& ut);
    virtual void skrivData() const;
    virtual void endreData();
    virtual void kjopGjenstand(int kjopNr);
    virtual int getInfo(char valgInfo);
    virtual int getUtlopsDato();
};
#endif