//MARC Florian
//ESILV Promotion 2020
//TD L
//DATE : 13/01/2018

#include "donnees.h"
#include <stdlib.h>
#include <stdio.h>

//----------------------------------------------------------
// Données
//----------------------------------------------------------

matrice_donnees* charger_donnees(const char* nom_fichier)
{
	FILE* fichier = fopen(nom_fichier,"r");
	if( fichier != NULL )
	{
		unsigned int nb_lignes;
		unsigned int nb_colonnes;
	
		// Etape 1 - traitement première ligne
		fscanf(fichier, "%u %u", &nb_lignes, &nb_colonnes); // %u <=> unsigned int
		fgetc(fichier); // lecture du retour chariot ('\n'). Valeur ignorée => passage à la ligne suivante
				
		// Etape 2 - allocation des lignes de la matrice
		double** matrice = (double**) malloc( nb_lignes * sizeof(double*) );
		
		// Etape 3 - remplissage de la matrice
		int ligne;
		for(ligne = 0 ; ligne < nb_lignes ; ligne++)
		{
			// allocation des colonnes de la matrice (pour chaque ligne)
			matrice[ligne] = (double*) malloc( nb_colonnes * sizeof(double) );
			
			int colonne;
			for(colonne = 0 ; colonne < nb_colonnes ; colonne++)
			{
				if(colonne != nb_colonnes-1)
				{
					fscanf(fichier, "%lg ", &matrice[ligne][colonne]);
				}
				else // dernière colonne (où le réel n'est pas suivi d'un espace)
				{
					fscanf(fichier, "%lg" , &matrice[ligne][colonne]);
				}
			}
			
			fgetc(fichier); // lecture du retour chariot ('\n'). Valeur ignorée => passage à la ligne suivante
		}
		
		matrice_donnees * data = (matrice_donnees*) malloc(sizeof(matrice_donnees));
		data->nb_colonnes = nb_colonnes;
		data->nb_lignes = nb_lignes;
		data->matrice = matrice;
		
		fclose(fichier);
		return data;
	}
	
	printf("Fichier %s inconnu.\n", nom_fichier);
	return NULL;
}

// Usage : var = liberer_donnees(var);  => var devient NULL
matrice_donnees* liberer_donnees(matrice_donnees * data)
{
	if(data != NULL)
	{
		int ligne;
		for(ligne = 0 ; ligne < data->nb_lignes ; ligne++)
		{
			if(data->matrice[ligne] != NULL) // normalement toujours vrai
				free(data->matrice[ligne]);
		}
		free(data->matrice);
		free(data);
	}
	return NULL;
}

matrice_donnees* creer_matrice_donnees(unsigned int lignes, unsigned int colonnes, double** adresse_matrice)
{
	matrice_donnees* new_matrice = (matrice_donnees*) malloc(sizeof(matrice_donnees));
	new_matrice->nb_colonnes = colonnes;
	new_matrice->nb_lignes = lignes;
	new_matrice->matrice = adresse_matrice;
	return new_matrice;
}

matrice_donnees** liberer_tableau_matrice_donnees(matrice_donnees** array, int taille)
{
	int i;
	for(i = 0; i < taille; i++)
	{
		free(array[i]);
	}
	free(array);
	return NULL;
}

critere_division* creer_critere(unsigned int Xi, double mediane, int test)
{
	critere_division* new_critere = (critere_division*) malloc(sizeof(critere_division));
	new_critere->variable_observee = Xi;
	new_critere->mediane_corrigee = mediane;
	new_critere->test_inegalite = test;
	return new_critere;
}

critere_division* liberer_critere(critere_division* critere)
{
	if(critere != NULL)
	{
		free(critere);
	}
	return NULL;
}

bool is_null_or_empty(matrice_donnees * data)
{
	bool sortie = false;
	if(data == NULL)
	{
		sortie = true;
	}
	if(data->matrice == NULL)
	{
		sortie = true;
	}
	if(data->nb_lignes == 0)
	{
		sortie = true;
	}
	return sortie;
}

void affichage_matrice(matrice_donnees* data)
{
	if(!is_null_or_empty(data))
	{
		int l;
		for(l = 0; l < data->nb_lignes; l++)
		{
			int c;
			for(c = 0; c < data->nb_colonnes; c++)
			{
				printf("[%.2lf]", data->matrice[l][c]/**(*((data->matrice) + l) + c)*/);
			}
			printf("\n");
		}
	}
	else
	{
		printf("Cette matrice est vide\n");
	}
}

double* extraire_colonne(unsigned int num_colonne, matrice_donnees* data)
{
	double* tableau_temporaire = NULL;
	if(num_colonne < data->nb_colonnes && num_colonne >=0)
	{
		tableau_temporaire = (double*) malloc(data->nb_lignes * sizeof(double));
		int l;
		for(l = 0; l < data->nb_lignes; l++)
		{
			tableau_temporaire[l] = data->matrice[l][num_colonne];
		}
	}
	return tableau_temporaire;
}

void affichage_colonne(double* colonne, int taille)
{
	int l;
	printf("\n");
	for(l = 0; l < taille; l++)
	{
		printf("[%.2lf]", colonne[l]);
	}
	printf("\n");
}

matrice_donnees* extraire_individus(matrice_donnees* source, critere_division* critere)
{
	unsigned int taille_new_matrice = nb_ligne_matrice_extraite(source, critere);
	double** new_array = copie_individus(source, critere, taille_new_matrice);
	matrice_donnees* new_matrice = creer_matrice_donnees(taille_new_matrice, source->nb_colonnes, new_array);
	return new_matrice;
}

double** copie_individus(matrice_donnees* source, critere_division* critere, unsigned int taille)
{
	double** new_array = (double**) malloc(taille * sizeof(double*));
	unsigned int num_colonne = critere->variable_observee;
	double** tableau_source = source->matrice;
	unsigned int new_index = 0;
	int l;
	for(l = 0; l < source->nb_lignes; l++)
	{
		if(critere->test_inegalite == -1)
		{
			if(tableau_source[l][num_colonne] <= critere->mediane_corrigee)
			{
				new_array[new_index] = tableau_source[l];
				new_index++;
			}
		}
		else
		{
			if(tableau_source[l][num_colonne] > critere->mediane_corrigee)
			{
				new_array[new_index] = tableau_source[l];
				new_index++;
			}
		}
	}
	return new_array;
}

unsigned int nb_ligne_matrice_extraite(matrice_donnees* source, critere_division* critere)
{
	unsigned int taille_nouvelle_matrice = 0;
	unsigned int num_colonne = critere->variable_observee;
	double** tableau_source = source->matrice;
	unsigned int l;
	for(l = 0; l < source->nb_lignes; l++)
	{
		if(critere->test_inegalite == -1)
		{
			if(tableau_source[l][num_colonne] <= critere->mediane_corrigee)
			{
				taille_nouvelle_matrice++;
			}
		}
		else
		{
			if(tableau_source[l][num_colonne] > critere->mediane_corrigee)
			{
				taille_nouvelle_matrice++;
			}
		}
	}
	return taille_nouvelle_matrice;
}
