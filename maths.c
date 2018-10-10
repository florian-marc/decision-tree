//MARC Florian
//ESILV Promotion 2020
//TD L
//DATE : 13/01/2018

#include <stdlib.h>
#include <stdbool.h>
#include "maths.h"
#include "merge_sort.h"

bool est_divisible(noeud* noeud_courant, unsigned int hauteur_maximale, unsigned int nb_min_individus, double precision_min, double precision_max)
{
	bool divisible = true;
	noeud* noeud_parent = noeud_courant->pere;
	unsigned int height = hauteur_depuis_feuille(noeud_courant);
	if(height > hauteur_maximale)
	{
		divisible = false;
	}
	if(noeud_parent!=NULL)
	{
		if(noeud_parent->matrice->nb_lignes <= nb_min_individus)
		{
			divisible = false;
		}
		double precision = noeud_parent->precision;
		if(precision > precision_max || precision < precision_min)
		{
			divisible = false;
		}
	}
	return divisible;
}

critere_division* meilleur_critere(noeud* noeud_courant)
{
	matrice_donnees* matrice_etudiee = noeud_courant->matrice;
	unsigned int nb_matrices = 2 * ((matrice_etudiee->nb_colonnes) - 1);
	
	//Création des tableaux ou seront stockés les tableaux de prétraitement
	matrice_donnees** tableau_matrice_temp = (matrice_donnees**) malloc(nb_matrices* sizeof(matrice_donnees*)); 	//Tableau où seront stockées les matrices extraites
	critere_division** tableau_critere_temp = (critere_division**) malloc(nb_matrices * sizeof(matrice_donnees*)); 	//Tableau où seront stockés les criteres associés à chaque matrice extraite
	double* precision_branches = (double*) malloc(nb_matrices * sizeof(double));									//Tableau où seront stockées les précisions associées à chaque matrice extraite
	
	int index_matrice;
	critere_division* new_critere = NULL;
	for(index_matrice = 0; index_matrice < nb_matrices; index_matrice++)
	{
		if(index_matrice % 2 == 0)
		{
			double* colonne_etudiee = extraire_colonne((index_matrice / 2) + 1, matrice_etudiee);
			double mediane = mediane_corrigee_colonne_double(colonne_etudiee, matrice_etudiee->nb_lignes);
			new_critere = creer_critere((index_matrice / 2) + 1, mediane, -1);
		}
		else
		{
			new_critere->test_inegalite = 1;
		}
		tableau_critere_temp[index_matrice] = new_critere;
		tableau_matrice_temp[index_matrice] = extraire_individus(matrice_etudiee, new_critere);
		/*===============================================================================================================================
		printf("\n Matrice numero %d : \n", index_matrice);
		affichage_matrice(tableau_matrice_temp[index_matrice]);
		*///=============================================================================================================================
		precision_branches[index_matrice] = nu(precision_data_set(tableau_matrice_temp[index_matrice], noeud_courant->Y));
	}
	/*
	printf("Voici le tableau des precisions pour le noeud courant : \n");
	affichage_colonne(precision_branches, nb_matrices);
	*/
	//Selection du meilleur critere à l'aide de la fonction de décision
	unsigned int index_meilleur_critere = max_colonne_double(precision_branches, nb_matrices);
	critere_division* critere_temp = tableau_critere_temp[index_meilleur_critere];
	critere_division* critere_sortie = creer_critere(critere_temp->variable_observee, critere_temp->mediane_corrigee, 0);
	
	free(precision_branches);
	//free(tableau_matrice_temp);
	tableau_matrice_temp = liberer_tableau_matrice_donnees(tableau_matrice_temp, nb_matrices);
	free(tableau_critere_temp);

	return critere_sortie;
}

double precision_data_set(matrice_donnees* matrice, double Y)
{
	double resultat = 0.0;
	if(!is_null_or_empty(matrice))
	{
		double* colonne = extraire_colonne(0, matrice);
		int c;
		double nb_occurence = 0.0;
		for(c = 0; c < matrice->nb_lignes; c++)
		{
			if(colonne[c] == Y)
			{
				nb_occurence += 1;
			}
		}
		resultat = nb_occurence / matrice->nb_lignes;
	}
	return resultat;
}

int max_colonne_double(double* colonne, unsigned int taille)
{
	int max = -1.0;
	if(colonne != NULL)
	{
		max = 0;
		if(taille > 1)
		{
			int l;
			for(l = 1; l < taille; l++)
			{
				if(colonne[l] > colonne[max])
				{
					max = l;
				}
			}
		}
	}
	printf("max : %lf, indice : %d\n", colonne[max], max);
	return max;
}

double mediane_corrigee_colonne_double(double* colonne, unsigned int taille)
{
	double mediane_corrigee = -1.0;
	int index_max = max_colonne_double(colonne, taille);
	if(taille >= 2 && index_max > -1)
	{
		double max_colonne = colonne[index_max];
		merge_sort(colonne, taille);
		affichage_colonne(colonne, taille);
		double resultat = -1.0;
		if(taille % 2 == 0)
		{
			resultat = (colonne[taille / 2] + colonne[(taille / 2) - 1]) / 2;
		}
		else
		{
			resultat = colonne[taille / 2];
		}
		if(resultat == max_colonne)
		{
			int i = 0;
			do
			{
				i++;
				if(colonne[(taille / 2) - i] < max_colonne)
				{
					mediane_corrigee = colonne[(taille / 2) - i];
				}
			} while((taille / 2) - i > 0 && colonne[(taille / 2) - i] >= max_colonne);
		}
		else
		{
			mediane_corrigee = resultat;
		}
	}
	return mediane_corrigee;
}

int max_int(int a, int b)
{
	int max;
	if(a >= b)
	{
		max = a;
	}
	else
	{
		max = b;
	}
	return max;
}

double max_double(double a, double b)
{
	double max;
	if(a >= b)
	{
		max = a;
	}
	else
	{
		max = b;
	}
	return max;
}

double valeur_absolue(double a)
{
	if(a < 0)
	{
		a = -a;
	}
	return a;
}

double nu(double a)
{
	if(a <= 0.5)
	{
		a = 1 - (2 * a);
	}
	else
	{
		a = (2 * a) - 1; 
	}
	return a;
}