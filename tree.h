#ifndef TREE_H
#define TREE_H

//MARC Florian
//ESILV Promotion 2020
//TD L
//DATE : 13/01/2018

#include <stdbool.h>
#include "donnees.h"

typedef struct _noeud
{
	critere_division* critere;
	double Y;
	double precision;
	matrice_donnees* matrice;
	
	struct _noeud* fils_droite;
	struct _noeud* fils_gauche;
	struct _noeud* pere;
} noeud;

//typedef struct _noeud noeud;


//Initialise l'arbre et crée les branches à l'aide de creer noeud
noeud* creer_racine(matrice_donnees* data, double variable_a_predire, unsigned int hauteur_maximale, unsigned int nb_min_individus, double precision_min, double precision_max);

//Crée le noeud si le parent est divisible, crée ensuite les noeux enfant
noeud* creer_noeud(critere_division* new_critere, noeud* noeud_parent, unsigned int hauteur_maximale, unsigned int nb_min_individus, double precision_min, double precision_max);

/* Renvoie  : true si le noeud n'a aucun fils
 * 			  false sinon
 * */
bool est_feuille(noeud const* element);

//Calcule la hauteur de l'arbre depuis un noeud qui n'est pas la racine
unsigned int hauteur_depuis_feuille(noeud const* feuille);

//Calcule la hauteur de l'arbre depuis la racine
unsigned int hauteur_depuis_racine(noeud const* racine);

//Algorithme récursif qui renvoie le nombre de feuille d'un noeud
unsigned int nb_feuille(noeud const* racine);

//Algorithme renvoyant la probabilité qu'un individu donné ait un Y donné
double predire(noeud const* racine, double* individu);

//Renvoie le critère de l'enfant s'il existe, NULL sinon
critere_division* get_critere_enfant(noeud const* noeud_courant);

//Affiche un noeud de l'arbre
void afficher_noeud(noeud const* noeud_courant);

//Affiche l'arbre en arborescence 
void affichage_arborescence(noeud const* arbre, unsigned int profondeur);

#endif