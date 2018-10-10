#ifndef DONNEES_H
#define DONNEES_H

//MARC Florian
//ESILV Promotion 2020
//TD L
//DATE : 13/01/2018

#include <stdbool.h>

//----------------------------------------------------------
// Données
//----------------------------------------------------------

typedef struct 
{
	unsigned int nb_colonnes; // la 1ere <=> classe à prédire (Y). Autres colonnes <=> variables d'observatio (Xi)
	unsigned int nb_lignes;   // <=> les individus
	double** matrice;         // tableau de tableaux de réels (i.e. tableaux 2D de réels)
} matrice_donnees;

typedef struct
{
	unsigned int variable_observee;	
	double mediane_corrigee;	
	int test_inegalite;			 //-1 : <|1 : >=
} critere_division;

matrice_donnees* charger_donnees(const char* nom_fichier);

// Usage var =  liberer_donnees(var);
matrice_donnees* liberer_donnees(matrice_donnees * data);

//permet de créer une matrice de données à partir de données engendrées par les algorithmes
matrice_donnees* creer_matrice_donnees(unsigned int lignes, unsigned int colonnes, double** new_matrice);

//permet de libérer l'espace mémoire engendré par les tableaux temporaires servant au calcul du meilleure critere
matrice_donnees** liberer_tableau_matrice_donnees(matrice_donnees** array, int taille);

//permet de copier ou de 
critere_division* creer_critere(unsigned int Xi, double mediane, int test);

//permet de libérer l'espace mémoire d'un critère
critere_division* liberer_critere(critere_division* critere);

/* Renvoie : - true si le tableau est vide ou si il pointe vers NULL
 *           - false sinon
 */
bool is_null_or_empty(matrice_donnees* data);

// Affichage de la matrice
void affichage_matrice(matrice_donnees* data);

/* Copie le contenu d'une colonne dans un tableau temporaire dont l'adresse est renvoyée
 * Renvoie NULL sinon
 */ 
double* extraire_colonne(unsigned int num_colonne, matrice_donnees* data);

void affichage_colonne(double* colonne, int taille);

// Permet d'extraire les individus de la matrice source en fonction d'un critere de division
matrice_donnees* extraire_individus(matrice_donnees* source, critere_division* critere);

//Renvoie un nouveau tableau qui contient les adresses des individus correspondant au critere
double** copie_individus(matrice_donnees* source, critere_division* critere, unsigned int taille);

//Renvoie la taille du tableau d'individu qui sera extrait de la matrice source
unsigned int nb_ligne_matrice_extraite(matrice_donnees* source, critere_division* critere);

#endif