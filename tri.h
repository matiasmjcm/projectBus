#ifndef TRI_H_INCLUDED
#define TRI_H_INCLUDED

#include "types.h" // para Tstation, TlisteStation, etc.
#define FILTRE_TOUT -1


// Fonction principale de tri
void trierListe(TlisteStation liste, int (*compar)(Tstation*, Tstation*), TypeNoeud filtre);

// Fonctions de comparaison
int comparerCoutMaintenance(Tstation *a, Tstation *b);
int comparerDateMaintenance(Tstation *a, Tstation *b);

#endif // TRI_H_INCLUDED
