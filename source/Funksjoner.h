#ifndef __FUNKSJONER_H
#define __FUNKSJONER_H

/**
*  Globale funksjoner. 
*/
void skrivMeny();
int getMaskinTid();
int lesDato();
bool sjekkDato(int dag, int mnd, int aar);
std::string toUpper(std::string & navn);
#endif