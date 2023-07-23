#ifndef __KUNDER_H
#define __KUNDER_H

#include <list>
#include "kunde.h"


/**
 * Kunder (med siste kundenummer og liste av alle kundene).
*/
class Kunder{
private:
    int sisteNr; // Fortløpende økende automatisk nummerering av alle nye kunder
    std::list <Kunde*> gKunderbase; //Sortert kundeliste
public:
    Kunde* finnesKunde(int kunde);
    void handling();
    void lesFraFil();
    void nyKunde();
    void skrivTilFil();
    void skrivAlleKunder() const;
    void skrivDataKundeNr(const int kNr) const;
    void slettKundeNr(const int kNr);
    void oppdatterInfo(int kjoperNr, int selgerNr, int salgsAntForSelger);
    void deAlloker();
};
#endif