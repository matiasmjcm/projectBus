#include <stdio.h>
#include <stdlib.h>

#include "listeDouble.h"


//initListe ne fait pas de malloc, juste une initialisation à NULL du pointeur de liste
void initListe(T_liste *l){
*l=NULL;
}


bool listeVide( T_liste l){
    return (l==NULL);
}

void afficheListe( T_liste l){
    T_liste courant = l;
    while (courant!=NULL){
        afficheStation(courant->pdata);  //fourni par types.h
        courant=courant->suiv;
    }
}

T_liste ajoutEnTete(T_liste l, Tstation* mydata){
    T_liste nouv = (T_liste)malloc(sizeof(struct T_cell));

    //CHANGEMENT par rapport à la partie2 d'updago
    //nouv->pdata = (int*)malloc(sizeof(int)); ATTENTION PLUS DE RECOPIE de mydata, donc plus d'allocation mémoire sur ce champ

    //SIMPLE BRANCHEMENT EN MEMOIRE ENTRE POINTEURS (SUR LA STATION EXISTANTE)
    nouv->pdata=mydata;

    if (l==NULL) // on cree en fait la premiere cellule de la liste
    {
        nouv->suiv = NULL;  //sécurise la présence de NULL sur le champ suiv, au cas où le ptr l n'aurait pas été  initialisé correctement via initListe
        nouv->prec = NULL;
    }
    else  // la lste n'etait pas vide, on doit donc faire les branchements
    {
        nouv->suiv = l;
        nouv->prec = NULL;
        l->prec = nouv;
    }
    return nouv;
}

T_liste ajoutEnFin(T_liste l, Tstation* mydata){
    T_liste nouv, courant=l;  //remarque: pas de malloc si on appelle ajoutEnTete

    if (l==NULL) // on cree en fait la premiere cellule de la liste
    {
        return ajoutEnTete(l, mydata);
    }
    else  // la liste n'etant pas vide,déplacment sur la derniere cellule, malloc et branchements
    {
        while (courant->suiv != NULL){
            courant=courant->suiv;
        }
        nouv = (T_liste)malloc(sizeof(struct T_cell));
        nouv->pdata=mydata;

        nouv->suiv = NULL;
        nouv->prec = courant;
        courant->suiv = nouv;
    }
    return l;  //la tête d'origine, qui n'a pas changé
}

Tstation* getPtrData(T_liste l){
    if (l==NULL)
    {
        printf("\nERREUR ptr pdata non alloué");
        return NULL;
    }
    else
    {
        return l->pdata;
    }
}

T_liste getNextCell(T_liste l){
    if (l==NULL)
    {
        return NULL;  //convention
    }
    else{
        return l->suiv;
    }
}

T_liste getPrevCell(T_liste l){
    if (l==NULL)
    {
        return NULL;  //convention
    }
    else{
        return l->prec;
    }
}

//MATIAS CASTRO MENDOZA

T_liste ajoutEnN(T_liste l, int pos, Tstation* mydata){
    T_cellule* new_cell = malloc(sizeof(T_cellule));
    //si no hay nada en la nueva celula, pues retornamos la misma T_liste
    if (!new_cell) return l;

    new_cell->pdata = mydata;
    new_cell->suiv = NULL;
    new_cell->prec = NULL;

    // si la nueva pos es menor o igual a 0 o si no hay nada en la T_liste l, agregamos al incio
    if (pos <= 0 || l == NULL) {
        return ajoutEnTete(l, mydata);
    }

    //posicionandonos en el nodo donde agregaremos el neuvo nodo
    T_cellule* temp = l;
    int i = 0;
    while (i < pos - 1 && temp->suiv != NULL) {
        temp = temp->suiv;
        i++;
    }

    //insertamos la nueva celda despujes de temp
    new_cell->suiv = temp->suiv;
    new_cell->prec = temp;

    //Si no es NULL
    if (temp->suiv){
        temp->suiv->prec = new_cell;
    }
    temp->suiv = new_cell;
    return l;
}

T_liste suppEnTete(T_liste l){
    if(!l) return NULL;

    T_cellule* temp = l->suiv;
    if(l->pdata) free(l->pdata);
    free(l);

    if(temp) temp->prec = NULL;
    return temp;
}

T_liste suppEnFin(T_liste l){
    //Si es nula retornamos NULL
    if(!l) return NULL;

    //Si el siguiente de l es NULL, estamos en el ultimo
    if(!l->suiv){
        //liberamos la data
        if(l->pdata) free(l->pdata);
        //liberamo l
        free(l);
        return NULL;
    }

    //despues tenemos que eliminar la data dentro de l
    T_cellule *temp = l;
    //si la data dentro de temp que es un puntero de l no es NULL
    while(temp->pdata) free(temp->pdata);
    //liberamos/eliminamos el temp
    free(temp);

    return l;
}

T_liste suppEnN(T_liste l, int pos){
    //si l es NULL
    if(!l) return NULL;
    //si es el primer elemento
    if(pos<=0) return suppEnTete(l);

    //puntero a l, tipo T_cellule
    T_cellule* temp = l;
    //ubicamos temp en la posicion de la celula que queremos eliminar
    int i = 0;
    while(i < pos && temp != NULL){
        temp = temp->suiv;
        i++;
    }
    //Si el temp es NULL pues no eliminamos nada, porque es muy grande y no existio
    if(!temp) return l;
    //Si hay un nodo anterior, pues hacemos que salte el nodo temp para que apunte al siguiente del nodo temp
    if(temp->prec) temp->prec->suiv = temp->suiv;
    //Si hay un nodo siguiente, pues hacemos que salte el nodo temp para que aputne al anterior del nodo temp
    if(temp->suiv) temp->suiv->prec = temp->prec;

    //si el temp es la cabeza actualizamos para que apunte al siguiente de la cabeza.
    if(temp == l) l = temp->suiv;
}

//puntero a la primera cell
T_liste getptrFirstCell(T_liste l){
    //Ubicandonos en la priemra cell
    while(l && l->prec != NULL){
        l = l->prec;
    }
    return l;
}

T_liste getptrLastCellx(T_liste l){
    //Ubicnadonos en la ultima cell
    while(l && l->suiv != NULL){
        l = l->suiv;
    }
    return l;
}

T_liste getptrLastCell(T_liste l) {
    T_liste temp = l;
    if (!temp) return NULL;
    while (temp->suiv != NULL) {
        temp = temp->suiv;
    }
    return temp;
}


T_liste getptrNextCell(T_liste l){
    if(!l) return NULL;
    return l->suiv;
}
T_liste getptrPrevCell(T_liste l){
    if(!l) return NULL;
    return l->prec;
}

void swapPtrData( T_liste source, T_liste destination ){
    //Si source o el destino son NULL pues no hace nada
    if(!source || !destination) return;

    //cramos un temp que apunte a la data de source
    Tstation *temp = source->pdata;
    //la data de source ahora sera la data de destination
    source->pdata = destination->pdata;
    //la data de destination sera la daa de temp que es la data de source
    destination->pdata = temp;
}

int getNbreCell(T_liste l){
    int count = 0;
    //mientra que l sea no NULL, osea hasta que termine
    while(l){
        count ++;
        l = l->suiv;
    }
    return count;
}

//tamaño de memoria bytes
int getSizeBytes(T_liste l){
    int total = 0;
    while(l){
        total += sizeof(T_cellule); //suma el tamaño de cada cell
        l = l->suiv;
    }
    return total;
} //utilisation de sizeof

T_liste creatNewListeFromFusion(T_liste l1, T_liste l2){
    T_liste fusion = NULL;
    T_liste temp;

    //Copiar l1
    temp = l1;
    while(temp){
        //duplicamos el espacio para que entre en la copia
        Tstation* copy = malloc(sizeof(Tstation));
        //copiamos el pdata de temp que es de l1
        *copy = *(temp->pdata);
        //agregamos al final de fusion la copia
        fusion = ajoutEnFin(fusion, copy);
    }

    //Copiar l2 - lo mismo
    temp = l2;
    while(temp){
        Tstation* copy = malloc(sizeof(Tstation));
        *copy = *(temp->pdata);
        fusion = ajoutEnFin(fusion, copy);
        temp = temp->suiv;
    }

    return fusion;
} //on souhaite CREER une nouvelle liste sans modifier l1 et l2

//concatenamos la lsita suite detras de debut
T_liste addBehind(T_liste debut, T_liste suite){
    //si son nulos cualquiera de los dos pues retornamos el que no respectivamente
    if(!debut) return suite;
    if(!suite) return debut;

    //Obtenemos la ultima cell de el debut para empezar a concatenar desde ahi
    T_liste last = getptrLastCell(debut);
    //el siguiente de la ultima cell sera el inicio de suite
    last->suiv = suite;
    //el anterior de suite sera el last del anterior
    suite->prec = last;

    //retornamos el debut que es donde estan todos
    return debut;
}

T_liste findCell(T_liste l, Tstation* data){
    //mientras que l no es NULL
    while(l){
        //si la pdata de l es igual a la data que buscamos retornamos l donde etas esa data
        if(l->pdata == data) return l;
        //si no pasamos la siguiente y seguimos buscando
        l = l->suiv;
    }
    //si no encontro retornamos NULL
    return NULL;
}

int getOccurences(T_liste l, Tstation* data){
    //iniciamos el contador
    int count = 0;
    //mientras que l no sea NULL
    while(l){
        //si la data de l es igual a la daa que buscamos aumentamos el contador
        if(l->pdata == data) count++;
        //pasamos al sigueitne para comparar
        l = l->suiv;
    }
    //retornmaos el contador final de ocurrencias de data en pdata para l's
    return count;
}  //nbre de fois que data est présent dans toute la liste l1

void afficheListeV2( T_liste l){
    //obtenemos la primera cell
    T_liste current = getptrFirstCell(l);
    //iteramos hasta que current sea NULL, osea que current llegue al final
    while(current){
        //obtenemos la data de current para imprimir
        Tstation* data = getPtrData(current);
        //imprimimos la id y el nombre
        printf("Station ID: %d, Nom: %s\n", getIdStation(data), getNomStation(data));
        //pasamos a la siguiente cell
        current = getptrNextCell(current);
    }
}

//A vous la suite si besoin
