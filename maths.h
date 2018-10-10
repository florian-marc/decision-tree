#ifndef MATHS_H
#define MATHS_H

//MARC Florian
//ESILV Promotion 2020
//TD L
//DATE : 13/01/2018

#include "tree.h"
#include "donnees.h"

/* L'échantillon peut être divisé si :
 *  	-La hauteur maximale n'a pas été atteinte (strictement inférieur à hauteur_max)
 *  	-Le nombre d'individus n'est pas inférieur stricte à nb_min_individus
 *  	-la précision n'est pas strictement inférieure à seuil_precision_min ou strictement supérieure à seuil_percision_max
 */
bool est_divisible(noeud* noeud_courant, unsigned int taille_maximale, unsigned int nb_min_individus, double precision_min, double precision_max);

critere_division* meilleur_critere(noeud* noeud_courant);

/* Renvoie la proportion de Y dans la première colonne du tableau de données
 */
double precision_data_set(matrice_donnees* matrice, double Y);

/* Renvoie : - l'indice du maximum d'une colonne d'une matrice de données si le tableau existe,
 *           - -1 sinon
 */
int max_colonne_double(double* colonne, unsigned int taille);

/* Renvoie : - la médiane corrigée d'une colonne d'une matrice de données si le tableau existe
 *           - -1.0 sinon
 * 
 */
double mediane_corrigee_colonne_double(double* colonne, unsigned int taille);

/* Renvoie le maximum de deux entiers
 */
int max_int(int a, int b);

/* Renvoie le maximum de deux réels
 */
double max_double(double a, double b);

// Renvoie la valeur absolue d'un réel
double valeur_absolue(double a);

// Fonction de décision
double nu(double a);

#endif