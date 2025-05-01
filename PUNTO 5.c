#include <stdio.h>
#include <stdlib.h>

#include "listeDouble.h"

//Hace una linea de bus en circular
T_liste LoopTliste(T_liste l, Tbus b){
    int loop;
    //si es nulo retornamos NULL
    if(!debut) return NULL;

    //Obtenemos la ultima cell de el debut para empezar a concatenar desde ahi
    T_liste last = getptrLastCell(debut);
    //el siguiente de la ultima cell sera el inicio de la linea
    last->suiv = l;
    //el anterior de la ultima sigue siendo la penultima
    last->prec = getptrPrevCell(last);

    //contador de loops del bus en la linea circular
    while (1){
        if getActualStation(b)=(l){
            loop++;
        }
    }
    fprintf("Le bus a fait %d loop(s)",loop);

    //retornamos el debut que es donde estan todos
    return l;
}

