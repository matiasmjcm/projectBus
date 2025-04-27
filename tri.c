#include <stdio.h>
#include "tri.h"


void trierListe(TlisteStation liste, int (*compar)(Tstation*, Tstation*), TypeNoeud filtre) {
    if (liste == NULL) return;

    TlisteStation i, j;
    for (i = liste; i != NULL; i = i->suiv) {
        for (j = i->suiv; j != NULL; j = j->suiv) {
            if (getTypeNoeud(i->pdata) == getTypeNoeud(j->pdata)) { // solo si son del mismo tipo ARRET ou TRONCO
                //filtre == -1 - FILTRE_TOUT, para que no ordene nada, solo ordenara si son del mismo tipo arrete o tronco
                if (filtre == FILTRE_TOUT || getTypeNoeud(i->pdata) == filtre) {
                    if (compar(i->pdata, j->pdata) > 0) {
                        // Intercambiar sólo si tienen el mismo tipo
                        Tstation *temp = i->pdata;
                        i->pdata = j->pdata;
                        j->pdata = temp;
                    }
                }
            }
        }
    }
}

// Comparar por coût de maintenance (orden decreciente)
int comparerCoutMaintenance(Tstation *a, Tstation *b) {
    return getCoutMaintenance(b) - getCoutMaintenance(a);
}
// 0 = iguales
// negativo = a mayor que b
// positivo = a menor que b

// Comparar por fecha de maintenance (orden creciente)
int comparerDateMaintenance(Tstation *a, Tstation *b) {
    t_date dateA = getDateDerniereMaintenance(a);
    t_date dateB = getDateDerniereMaintenance(b);

    if (dateA.annee != dateB.annee)
        return dateA.annee - dateB.annee;
    if (dateA.mois != dateB.mois)
        return dateA.mois - dateB.mois;
    return dateA.jour - dateB.jour;
}
