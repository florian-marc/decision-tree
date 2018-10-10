//MARC Florian
//ESILV Promotion 2020
//TD L
//DATE : 13/01/2018

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "donnees.h"
#include "maths.h"
#include "tree.h"

#define FICHIER_SOURCE "iris.txt"

//renvoie la racine de l'arbre s'il a pu être construit, NULL sinon
noeud* construction_arbre();

//menu principal du programme
void menu();


double* creer_individu_guide(unsigned int nb_colonnes);

double* creer_individu_guide(unsigned int nb_colonnes)
{
	double* sortie = (double*) malloc(nb_colonnes * sizeof(double));
	int c;
	for(c = 0; c < nb_colonnes; c++)
	{
		printf("Valeur de X%d : ", c+1);
		scanf("%lf", &sortie[c]);
	}
	return sortie;
}

void menu()
{
	noeud* arbre = construction_arbre();
	if(arbre != NULL)
	{
		int choix;
		bool sortie = false;
		do
		{
			printf("\nMenu principal\n\n");
			printf("\t1. Afficher la hauteur de l'arbre\n");
			printf("\t2. Afficher le nombre de feuilles de l'arbre\n");
			printf("\t3. Afficher l'arbre sous forme arborescente\n");
			printf("\t4. Afficher les feuilles //Non implemente\\\n");
			printf("\t5. Predire\n");
			printf("\t6. Sortir de l'algorithme\n");
			unsigned int hauteur;
			unsigned int largeur;
			double* new_individu;
			double precision;
			scanf("%d", &choix);
			switch(choix)
			{
				case 1:
					hauteur = hauteur_depuis_racine(arbre);
					printf("La hauteur de l'arbre est %u\n", hauteur);
					break;
				case 2:
					largeur = nb_feuille(arbre);
					printf("La largeur de l'arbre est %u feuilles", largeur);
					break;
				case 3:
					affichage_arborescence(arbre, 0);
					break;
				case 4:
					//A implémenter
					break;
				case 5:
					new_individu = creer_individu_guide((arbre->matrice->nb_colonnes) - 1);
					precision = predire(arbre, new_individu);
					printf("Precision pour prédire que ce sont des individus de type %lf = %lf\n", arbre->Y, precision);
					break;
				case 6:
					sortie = true;
					break;
				default:
				printf("Saisie incorrecte, veuillez reessayer : ");
				break;
			}
		}while(!sortie);
	}
}

noeud* construction_arbre()
{
	unsigned int hauteur_max;
	unsigned int nb_min_individus;
	double Y;
	double precision_min;
	double precision_max;
	int choix;
	printf("L'arbre sera contruit a partir du fichier source %s\n\n", FICHIER_SOURCE);
	printf("\t1. Construire l'arbre a partir de parametres automatiques\n");
	printf("\t2. Construire l'arbre a partir de parametres personnalises\n");
	scanf("%d", &choix);
	printf("Chargement des données depuis le fichier %s\n", FICHIER_SOURCE);
	matrice_donnees* data = charger_donnees(FICHIER_SOURCE);
	noeud* arbre = NULL;
	if(data != NULL)
	{
		switch(choix)
		{
			case 1:
				hauteur_max = (data->nb_colonnes - 1) * 2;
				nb_min_individus = (data->nb_lignes)/10;
				precision_min = 0.1;
				precision_max = 0.9;
				break;
			case 2:
				printf("Hauteur max de l'arbre (>0) : ");
				scanf("%u", &hauteur_max);
				printf("Nombre minimum d'individus par noeud : ");
				scanf("%u", &nb_min_individus);
				printf("Precision minimale de l'arbre : ");
				scanf("%lf", &precision_min);
				printf("Precision maximale de l'arbre : ");
				scanf("%lf", &precision_max);
				break;
		}
		printf("Quelle valeur de Y voulez-vous employer ?");
		scanf("%lf", &Y);
		printf("Construction de l'arbre de decision\n");
		arbre = creer_racine(data, Y, hauteur_max, nb_min_individus, precision_min, precision_max);
		if(arbre != NULL)
		{
			printf("Construction de l'arbre réussie!\n");
		}
		else
		{
			printf("Construction de l'arbre impossible, veuillez vérifier vos données\n");
		}
	}
	return arbre;
}

int main(int argc, char **argv)
{
	menu();
	return 0;
}
