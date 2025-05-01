#ifndef GESTIONFICHER_H_INCLUDED
#define GESTIONFICHER_H_INCLUDED

#include "types.h"

void sauvegarderDonnees(const char *nomFichier, TligneBus *lignes, int nbLignes, Tbus *bus, int nbBus);
void chargerDonnees(const char *nomFichier, TligneBus *lignes, int *nbLignes, Tbus *bus, int *nbBus);

#endif // GESTIONFICHER_H_INCLUDED
