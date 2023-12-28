/*------------------------------------------------------------------------
 *           MACHINE BATEAUX ET LOCATIONS
 *------------------------------------------------------------------------
 * Auteurs     : Alain Lucci et Damien Genthial
 * Création   : 12 mai 2015
 */

#define MACHINE_BATEAUX_C
#include "MachineBateaux.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

/* ------- Procédures et fonctions privées ------- */

/* Lecture d'un bateau dans un fichier, ne pas l'utiliser directement
 * Syntaxe :
 *    num heures:minutes */
static Bateau lireBateau(FILE* ruban) {
    Bateau res;
    if (feof(ruban))
        return MARQUE;
    else {
        // L'espace à la fin du format force la détection de feof après le dernier
        fscanf(ruban, "%d%d:%d ", &res.num, &res.h.heures, &res.h.minutes);
        return res;
    }
}

/* Lecture d'une location dans un fichier, ne pas l'utiliser directement
 * Syntaxe :
 *    num heures:minutes heures:minutes */
static Location lireLocation(FILE* ruban) {
    Location res;
    if (feof(ruban))
        return LMARQUE;
    else {
        // L'espace à la fin du format force la détection de feof après le dernier
        fscanf(ruban, "%d%d:%d%d:%d ", &res.num,
                &res.depart.heures, &res.depart.minutes,
                &res.retour.heures, &res.retour.minutes);
        return res;
    }
}

/* Ouverture d'un fichier en lecture avec arrêt brutal et affichage d'un message en cas d'erreur */
static FILE* ouvreLecture(char nom[]) {
    FILE* f = fopen(nom, "r");
    if (f == NULL) {
        fprintf(stderr, "\n*******\nLe fichier %s n'existe pas ou n'est pas lisible.\n\n", nom);
        exit(EXIT_FAILURE);
    }
    return f;
}

/* Ouverture d'un fichier en écriture avec arrêt brutal et affichage d'un message en cas d'erreur */
static FILE* ouvreEcriture(char nom[]) {
    FILE* f = fopen(nom, "w");
    if (f == NULL) {
        fprintf(stderr, "\n*******\nImpossible d'écrire dans le fichier %s.\n\n", nom);
        exit(EXIT_FAILURE);
    }
    return f;
}

/* ------- Procédures et fonctions publiques ------- */

/* Lecture d'un entier de manière "fiable", retourne -1 en cas d'erreur */
int lireEntier() {
    char ligne[32];
    int res = -1;
    fgets(ligne, 32, stdin);
    sscanf(ligne, "%d", &res);
    return res;
}

/* Pour changer le nom d'un ruban, bateaux ou locations */
void changeNomBateaux(RubanBateaux* rb, const char nom[]) {
    strcpy(rb->nomFichier, nom);
}
void changeNomLocations(RubanLocations* rloc, const char nom[]) {
    strcpy(rloc->nomFichier, nom);
}

/* Bateau courant d'un ruban de bateaux */
Bateau bc(const RubanBateaux* rb) {
    return rb->courant;
}

/* Location courante d'un runban de locations */
Location lc(const RubanLocations* rl) {
    return rl->courante;
}

/* Initialisation d'un ruban en lecture */
void demarrer(RubanBateaux* rb) {
    rb->fichier = ouvreLecture(rb->nomFichier);
    rb->courant = lireBateau(rb->fichier);
}
void demarrerL(RubanLocations* rl) {
    rl->fichier = ouvreLecture(rl->nomFichier);
    rl->courante = lireLocation(rl->fichier);
}

/* Avancer sur un ruban */
void avancer(RubanBateaux* rb) {
    rb->courant = lireBateau(rb->fichier);
}
void avancerL(RubanLocations* rl) {
    rl->courante = lireLocation(rl->fichier);
}

/* Fermer un ruban */
void fermer(RubanBateaux* rb) {
    fclose(rb->fichier);
}
void fermerL(RubanLocations* rl) {
    fclose(rl->fichier);
}

/* Initialisation d'un ruban en écriture */
void amorcer(RubanBateaux* rb) {
    rb->fichier = ouvreEcriture(rb->nomFichier);
}
void amorcerL(RubanLocations* rl) {
    rl->fichier = ouvreEcriture(rl->nomFichier);
}

/* Enregistrer un élément sur un ruban */
void enregistrer(RubanBateaux* rb, Bateau b) {
    rb->courant = b;
    fprintf(rb->fichier, "%d %d:%02d\n", b.num, b.h.heures, b.h.minutes);
}
void enregistrerL(RubanLocations* rl, Location l) {
    rl->courante = l;
    fprintf(rl->fichier, "%d %d:%02d %d:%02d\n", l.num,
            l.depart.heures, l.depart.minutes,
            l.retour.heures, l.retour.minutes);
}

/* Marquer un ruban */
void marquer(RubanBateaux* rb) {
    rb->courant = MARQUE;
    fprintf(rb->fichier, "%d %d:%02d\n", MARQUE.num, MARQUE.h.heures, MARQUE.h.minutes);
    fclose(rb->fichier);
}
void marquerL(RubanLocations* rl) {
    rl->courante = LMARQUE;
    fprintf(rl->fichier, "%d %d:%02d %d:%02d\n", LMARQUE.num,
            LMARQUE.depart.heures, LMARQUE.depart.minutes,
            LMARQUE.retour.heures, LMARQUE.retour.minutes);
    fclose(rl->fichier);
}
