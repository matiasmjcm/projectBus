#include <stdio.h>
#include <stdlib.h>

#include "types.h"

void afficheStation( Tstation *station){
    if (station == NULL){
        printf("\nerreur station non allouée!\n");
    }
    else{
        if (station->arret_ou_troncon == ARRET){
            printf("\nSTATION idStation: %d, Station : %s, posX = %d, posY = %d", station->idStation, station->nomStation, station->posX, station->posY);
        }
        else{ //alors le noeud est un tronçon
            printf("\n\nTRONCON idLigneBus: %d, temps: %d sec, distance à parcourir: %d mètres", station->idLigneBus, station->coutTemps, station->coutDistance);
            afficheStation(station->depart);
            afficheStation(station->arrivee);
            printf("\nfin tronçon\n");
        }
    }
}

// Getteurs

int getIdStation( Tstation *myStation){
    return myStation->idStation;
}

char *getNomStation( Tstation *myStation){
    return myStation->nomStation;
}

int getPosXStation( Tstation *myStation ){
    return myStation->posX;
}
int getPosYStation( Tstation *myStation ){
    return myStation->posY;
}

int getIdLigneTroncon(Tstation *myStation){
    //une station n'est pas liée à une ligne, seulement le troncon
    if (getTypeNoeud(myStation)==TRONCON)
        return myStation->idLigneBus;
    else{
        printf("\n(getIdLigneTroncon) Erreur algo, vous n etes pas sur un troncon");
        return -1;
    }
}

TypeNoeud getTypeNoeud(Tstation *myStation){
    return myStation->arret_ou_troncon;
}



int getPosXBus( Tbus myBus ){
    return myBus->posXBus;
}
int getPosYBus( Tbus myBus ){
    return myBus->posYBus;
}
int getIdBus( Tbus myBus ){
    return myBus->idBus;
}
int getIdLigneActuelleDuBus( Tbus myBus ){
    return myBus->idLigneBusActuelle;
}

int getIdLigneBus(Tbus myBus){
    return myBus->idLigneBusActuelle;
}

TsensParcours getSensParcours(Tbus myBus){
    return myBus->sensParcours;
}

//new get MATIAS
int getCoutMaintenance(Tstation *myStation){
    return myStation -> coutMaintenance;
}
t_date getDateDerniereMaintenance(Tstation *myStation){
    //Si myStation es NULL
    t_date dateVide = {0,0,0};
    if (myStation != NULL){
        return myStation -> dateDerniereMaintenance;
    }
    return dateVide;
}
t_date getDateDerniereMaintenance_annee(Tstation *myStation){
    if (myStation != NULL){
        return myStation -> dateDerniereMaintenance.annee;
    }
    //Si myStation es NULL
    return 0;
}
t_date getDateDerniereMaintenance_mois(Tstation *myStation){
    if (myStation != NULL){
        return myStation -> dateDerniereMaintenance.mois;
    }
    //Si myStation es NULL
    return 0;
}
t_date getDateDerniereMaintenance_jour(Tstation *myStation){
    if (myStation != NULL){
        return myStation -> dateDerniereMaintenance.jour;
    }
    //Si myStation es NULL
    return 0;
}

// Setteurs

void setActualStation( Tbus myBus, TlisteStation arrivalStation ){
    myBus->positionSurLaLigneDeBus = arrivalStation;
}

TlisteStation getActualStation( Tbus myBus ){
    return myBus->positionSurLaLigneDeBus;
}

void setPosXBus(Tbus myBus, int newX){
    myBus->posXBus = newX;
}

void setPosYBus(Tbus myBus, int newY){
    myBus->posYBus = newY;
}

void setIdLigneBus(Tbus myBus, int idLigne){
    myBus->idLigneBusActuelle = idLigne;
}

void setSensParcours(Tbus myBus, TsensParcours sens ){
    myBus->sensParcours = sens;
}

void setPositionSurLaLigneDeBus( Tbus myBus, TlisteStation myStation){
    myBus->positionSurLaLigneDeBus = myStation;
}

//New set MATIAS
int setCoutMaintenance(Tstation *myStation, int cout){
    if (myStation == NULL){
        myStation -> coutMaintenance = cout;
    }
}
void setDateDerniereMaintenance(Tstation *myStation, t_date new_date){
    if(myStation != NULL){
        myStation -> dateDerniereMaintenance = new_date;
    }
}
void setDateDerniereMaintenance_annee(Tstation *myStation, int new_annee){
    if(myStation != NULL){
        myStation -> dateDerniereMaintenance.annee = new_annee;
    }
}
void setDateDerniereMaintenance_mois(Tstation *myStation, int new_mois){
    if(myStation != NULL){
        myStation -> dateDerniereMaintenance.mois = new_mois;
    }
}
void setDateDerniereMaintenance_jour(Tstation *myStation, int new_jour){
    if(myStation != NULL){
        myStation -> dateDerniereMaintenance.jour = new_jour;
    }
}
