#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gestionficher.h"
#include "ligneBus.h"
#include "listeDouble.h"
#include "types.h"

// Función auxiliar para imprimir una
void printDate(FILE *f, t_date date) {
    fprintf(f, "%02d/%02d/%04d", date.jour, date.mois, date.annee);
}

// Guarda todas las líneas y buses en un archivo de texto
void sauvegarderDonnees(const char *nomFichier, TligneBus lignes[], int nbLignes, Tbus bus[], int nbBus) {
    FILE *f = fopen(nomFichier, "w");
    if (!f) {
        perror("Erreur lors de l'ouverture du fichier en écriture");
        return;
    }

    for (int i = 0; i < nbLignes; i++) {
        TligneBus l = lignes[i];
        fprintf(f, "LIGNE %d \"%s\"\n", l.idLigneBus, l.nomLigne);

        TlisteStation courante = l.depart;
        while (courante != NULL) {
            Tstation *s = courante->pdata;
            if (s->arret_ou_troncon == ARRET) {
                fprintf(f, "ARRET %d \"%s\" %d %d %d ", s->idStation, s->nomStation, s->posX, s->posY, s->coutMaintenance);
                printDate(f, s->dateDerniereMaintenance);
                fprintf(f, "\n");
            } else if (s->arret_ou_troncon == TRONCON) {
                fprintf(f, "TRONCON %d %d %d %d %d\n", s->idLigneBus, s->depart->idStation, s->arrivee->idStation, s->coutTemps, s->coutDistance);
            }
            courante = courante->suiv;
        }
    }

    for (int i = 0; i < nbBus; i++) {
        Tbus b = bus[i];
        fprintf(f, "BUS %d %d %d %d\n", b->idBus, b->idLigneBusActuelle, b->posXBus, b->posYBus);
    }

    fclose(f);
    printf("Données sauvegardées dans \"%s\"\n", nomFichier);
}
/*
void chargerDonnees(const char *nomFichier, TligneBus lignes[], int *nbLignes, Tbus bus[], int *nbBus){
    FILE *f = fopen(nomFichier, "r");
    if(!f){
        perror("Error al abrir el archivo");
        return;
    }

    char ligne[256];
    TligneBus *currentLine = NULL;
    TlisteStation *currentLigne = NULL;
    Tstation *dep , *arr ;
    Tstation *troncon = NULL;
    t_date date;
    int ligneID, idStation, x, y, cout, busId, ligneBusActuelle, posXBus, posYBus;
    char nombre[50], nombreEstation[50], fecha[11];

    while(fgets(ligne, sizeof(ligne), f)){
        if(sscanf(ligne, "LIGNE %d \"%[^\"]\"", &ligneID, nombre) == 2){
            //creamos nueva linea
            currentLigne = &lignes[*nbLignes];
            currentLine->idLigneBus = ligneID;
            strcpy(currentLine->nomLigne, nombre);
            //terminamos para esta linea su lista de estaciones y su bus
            currentLigne = NULL;
            (*nbLignes)++;
            //ARRET 1 "Charles de Gaulle" 10 10 82 10/04/2023
        } else if (sscanf(ligne, "ARRET %d \"%[^\"]\" %d %d %d %s", &idStation, nombreEstation, &x, &y, &cout, fecha) == 6){
            //leer estacion ARRET
            sscanf(fecha, "%2d/%2d/%4d", &date.jour, &date.mois, &date.annee);
            dep = creeArret(x, y, nombreEstation, idStation);
            currentLigne = ajoutEnFin(currentLigne, dep);
            //TRONCON 1 1 2 492 492
        } else if (sscanf(ligne, "TRONCON %d %d %d %d %d", &ligneID, &dep, &arr, &cout, &cout) == 5){
            //leer el troncon
            troncon = creeTroncon(ligneID, dep, arr, cout, cout);
            currentLigne = ajoutEnFin(currentLigne, troncon);
            //BUS 1 1 10 10
        } else if (sscanf(ligne, "BUS %d %d %d %d"), &busId, &ligneBusActuelle, &posXBus, &posYBus == 4){
            //leer informacion del bus
            bus[*nbBus]->idBus = busId;
            bus[*nbBus]->idLigneBusActuelle = ligneBusActuelle;
            bus[*nbBus]->posXBus;
            bus[*nbBus]->posYBus;
            (*nbBus)++;
        }
    }
    fclose(f);
}
*/

void chargerDonnees(const char *nomFichier, TligneBus lignes[], int *nbLignes, Tbus bus[], int *nbBus) {
    //abrimos el archivo y r para leer
    FILE *f = fopen(nomFichier, "r");
    //si f es NULL, retornamos error
    if (!f) {
        perror("Error al abrir el archivo");
        return;
    }

    //creamos las variables donde guardaremos los datos leido
    char ligne[256];
    TligneBus *currentLine = NULL;
    TlisteStation listeStations = NULL;
    Tstation *dep = NULL, *arr = NULL, *troncon = NULL;
    t_date date;
    int ligneID, idStation, x, y, cout, cout2, busId, ligneBusActuelle, posXBus, posYBus;
    char nombre[50], nombreStation[50], fecha[11];

    //aca entramos a leer linea por linea, donde ligne es la variable linea de tamaño ligne que es 256 y f es el archivo donde se lee
    while (fgets(ligne, sizeof(ligne), f)) {

        // LIGNE <id> "nom"
        if (sscanf(ligne, "LIGNE %d \"%[^\"]\"", &ligneID, nombre) == 2) {
            //linea actual en la lista de lineas, donde nos ubicamos en la nbLignes que es la actual
            currentLine = &lignes[*nbLignes];
            //asignamos el idLigneBus al id leido
            currentLine->idLigneBus = ligneID;

            // malloc para nomLigne porque es un char*
            currentLine->nomLigne = malloc(strlen(nombre) + 1);
            strcpy(currentLine->nomLigne, nombre);

            listeStations = NULL; // reiniciar la lista para la nueva línea
            currentLine->depart = NULL;
            currentLine->arrivee = NULL;

            (*nbLignes)++;//Pasamos a la sigueinte linea
        }

        // ARRET <id> "nom" <x> <y> <coutMaint> <dd/mm/yyyy>
        else if (sscanf(ligne, "ARRET %d \"%[^\"]\" %d %d %d %s", &idStation, nombreStation, &x, &y, &cout, fecha) == 6) {
            //asignamos los valores a las variables
            sscanf(fecha, "%2d/%2d/%4d", &date.jour, &date.mois, &date.annee);
            dep = creeArret(x, y, nombreStation, idStation);
            setCoutMaintenance(dep, cout);
            setDateDerniereMaintenance(dep, date);

            listeStations = ajoutEnFin(listeStations, dep);
        }

        // TRONCON <idLigne> <idDep> <idArr> <coutT> <coutD>
        else if (sscanf(ligne, "TRONCON %d %d %d %d %d", &ligneID, &idStation, &x, &cout, &cout2) == 5) {
            //buscamos la estacion y la asignamos
            Tstation *stationDep = findStationById(listeStations, idStation);
            Tstation *stationArr = findStationById(listeStations, x);

            if (stationDep && stationArr) {
                troncon = creeTroncon(ligneID, stationDep, stationArr, cout, cout2);
                listeStations = ajoutEnFin(listeStations, troncon);
            }
        }

        // BUS <idBus> <idLigne> <x> <y>
        else if (sscanf(ligne, "BUS %d %d %d %d", &busId, &ligneBusActuelle, &posXBus, &posYBus) == 4) {
            bus[*nbBus] = malloc(sizeof(Typebus));
            bus[*nbBus]->idBus = busId;
            bus[*nbBus]->idLigneBusActuelle = ligneBusActuelle;
            bus[*nbBus]->posXBus = posXBus;
            bus[*nbBus]->posYBus = posYBus;
            bus[*nbBus]->sensParcours = depart_vers_arrivee;
            bus[*nbBus]->positionSurLaLigneDeBus = getptrFirstCell(listeStations); // empieza al principio
            (*nbBus)++;
        }
    }

    // Después de terminar de leer estaciones/troncons para una línea, guardamos la lista
    if (currentLine) {
        currentLine->depart = getptrFirstCell(listeStations);
        currentLine->arrivee = getptrLastCell(listeStations);
    }

    fclose(f);
}

//liberar memorio
void libererLigneBus(TligneBus *ligne) {
    TlisteStation courant = ligne->depart;
    while (courant != NULL) {
        TlisteStation suivant = courant->suiv;

        // Liberar la Tstation apuntada por pdata
        if (courant->pdata != NULL) {
            free(courant->pdata);
        }

        // Liberar la cellule
        free(courant);

        courant = suivant;
    }

    // Marcar la línea como vacía
    ligne->depart = NULL;
    ligne->arrivee = NULL;

    // Si se usó malloc para nomLigne, liberarlo también
    if (ligne->nomLigne != NULL) {
        free(ligne->nomLigne);
        ligne->nomLigne = NULL;
    }
}
