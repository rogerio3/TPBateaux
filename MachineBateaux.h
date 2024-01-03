/*------------------------------------------------------------------------
 *           MACHINE BATEAUX ET LOCATIONS
 *------------------------------------------------------------------------
 * Auteurs     : Alain Lucci et Damien Genthial
 * Création   : 12 mai 2015
 */

#ifndef MACHINE_BATEAUX_H
#define MACHINE_BATEAUX_H

#ifndef MACHINE_BATEAUX_C
#define PUBLIC extern
#else
#define PUBLIC
#endif

#include <stdio.h>

/*------- Definitions de constantes -------*/
#define NBATMAX 20  // nombre maximum de bateaux
#define H_OUVR   8  // heure d'ouverture : 8 h 00
#define H_FERM  19  // heure de fermeture : 19 h 00
#define MAXNOMFICHIER 64 // Longueur maximum d'un nom de fichier


/*------- Définitions de types et de sous-types -------*/
typedef struct {
    int heures;  // H_OUVR .. H_FERM
    int minutes;  // 0 .. 59
} Heure;

typedef struct {
    int num;  // 0 .. NBATMAX
    Heure h;  // de départ ou de retour selon le ruban
} Bateau;

typedef struct {
    int nbHeures;  // >= 0
    int nbMinutes;  // 0 .. 59;
} Duree;

typedef struct {
    int num;  // 0..NBATMAX
    Heure depart;
    Heure retour;
} Location;

typedef struct {
    FILE* fichier;
    char nomFichier[MAXNOMFICHIER];
    Bateau courant;
} RubanBateaux;

typedef struct {
    FILE* fichier;
    char nomFichier[MAXNOMFICHIER];
    Location courante;
} RubanLocations;

/* Marques de fin des rubans */
#ifndef MACHINE_BATEAUX_C
extern const Bateau MARQUE;
extern const Location LMARQUE;
#else
const Bateau MARQUE = {0, {H_OUVR, 0}};
const Location LMARQUE = {0, {H_OUVR, 0}, {H_FERM, 0}};
#endif

/*------------------------------------------------------------------------
 * Lecture d'un entier de manière "fiable", retourne -1 en cas d'erreur */
PUBLIC int lireEntier();

/* Pour changer le nom d'un ruban, bateaux ou locations */
PUBLIC void changeNomBateaux(RubanBateaux* rb, const char nom[]);
PUBLIC void changeNomLocations(RubanLocations* rloc, const char nom[]);

/* Bateau courant d'un ruban de bateaux */
PUBLIC Bateau bc(const RubanBateaux* rb);
/* Location courante d'un runban de locations */
PUBLIC Location lc(const RubanLocations* rl);

/* Initialisation d'un ruban en lecture */
PUBLIC void demarrer(RubanBateaux* rb);
PUBLIC void demarrerL(RubanLocations* rl);

/* Avancer sur un ruban */
PUBLIC void avancer(RubanBateaux* rb);
PUBLIC void avancerL(RubanLocations* rl);

/* Fermer un ruban */
PUBLIC void fermer(RubanBateaux* rb);
PUBLIC void fermerL(RubanLocations* rl);

/* Initialisation d'un ruban en écriture */
void amorcer(RubanBateaux* rb);
void amorcerL(RubanLocations* rl);

/* Enregistrer un élément sur un ruban */
PUBLIC void enregistrer(RubanBateaux* rb, Bateau b);
PUBLIC void enregistrerL(RubanLocations* rl, Location l);

/* Marquer un ruban */
PUBLIC void marquer(RubanBateaux* rb);
PUBLIC void marquerL(RubanLocations* rl);

#undef PUBLIC
#endif	/* MACHINE_BATEAUX_H */
