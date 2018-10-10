//MARC Florian
//ESILV Promotion 2020
//TD L
//DATE : 13/01/2018

#include <stdlib.h>
#include <stdio.h>
#include "tree.h"
#include "maths.h"

noeud* creer_racine(matrice_donnees* data, double variable_a_predire, unsigned int hauteur_maximale, unsigned int nb_min_individus, double precision_min, double precision_max)
{
	//allocation dynamique de la racine
	noeud* nouveau_noeud = (noeud*) malloc(sizeof(noeud));
	nouveau_noeud->pere = NULL;
	if(est_divisible(nouveau_noeud, hauteur_maximale, nb_min_individus, precision_min, precision_max))
	{
		nouveau_noeud->Y = variable_a_predire;
		nouveau_noeud->matrice = data;
		nouveau_noeud->critere = NULL;
		nouveau_noeud->precision=precision_data_set(data, variable_a_predire);
		
		critere_division* critere_enfant_gauche = meilleur_critere(nouveau_noeud);
		critere_enfant_gauche->test_inegalite = -1;
		critere_division*critere_enfant_droite = creer_critere(critere_enfant_gauche->variable_observee, critere_enfant_gauche->mediane_corrigee, 1);
		
		nouveau_noeud->fils_gauche = creer_noeud(critere_enfant_gauche, nouveau_noeud, hauteur_maximale, nb_min_individus, precision_min, precision_max);
		nouveau_noeud->fils_droite = creer_noeud(critere_enfant_droite, nouveau_noeud, hauteur_maximale, nb_min_individus, precision_min, precision_max);
		
		return nouveau_noeud;
	}
	else
	{
		free(nouveau_noeud);
		return NULL;
	}
}

noeud* creer_noeud(critere_division* new_critere, noeud* noeud_parent, unsigned int hauteur_maximale, unsigned int nb_min_individus, double precision_min, double precision_max)
{
	noeud* nouveau_noeud = (noeud*) malloc(sizeof(noeud));
	nouveau_noeud->pere = noeud_parent;
	if(est_divisible(nouveau_noeud, hauteur_maximale, nb_min_individus, precision_min, precision_max))
	{
		//allocation dynamique du nouveau noeud
		nouveau_noeud->Y = noeud_parent->Y;
		nouveau_noeud->matrice = extraire_individus(noeud_parent->matrice, new_critere);
		nouveau_noeud->critere = new_critere;
		nouveau_noeud->precision = precision_data_set(nouveau_noeud->matrice, nouveau_noeud->Y);
		
		critere_division* critere_enfant_gauche = meilleur_critere(nouveau_noeud);
		critere_enfant_gauche->test_inegalite = -1;
		critere_division*critere_enfant_droite = creer_critere(critere_enfant_gauche->variable_observee, critere_enfant_gauche->mediane_corrigee, 1);
		
		nouveau_noeud->fils_gauche = creer_noeud(critere_enfant_gauche, nouveau_noeud, hauteur_maximale, nb_min_individus, precision_min, precision_max);
		nouveau_noeud->fils_droite = creer_noeud(critere_enfant_droite, nouveau_noeud, hauteur_maximale, nb_min_individus, precision_min, precision_max);
		
		return nouveau_noeud;
	}
	else
	{
		free(nouveau_noeud);
		return NULL;
	}
}

bool est_feuille(noeud const* element)
{
	bool feuille = false;
	if(element != NULL)
	{
		if(element->fils_gauche == NULL && element->fils_droite == NULL)
		{
			feuille = true;
		}
	}
	return feuille;
}

unsigned int hauteur_depuis_feuille(noeud const* feuille)
{
	if(feuille->pere == NULL)
	{
		return 0;
	}
	else
	{
		return hauteur_depuis_feuille(feuille->pere) + 1;
	}
}

unsigned int hauteur_depuis_racine(noeud const* racine)
{
	if(racine == NULL)
	{
		return  0;
	}
	else
	{
		if(racine->fils_droite == NULL && racine->fils_gauche == NULL)
		{
			return 1;
		}
		else
		{
			return max_int(hauteur_depuis_racine(racine->fils_gauche), hauteur_depuis_racine(racine->fils_droite)) + 1;
		}
	}
}

unsigned int nb_feuille(noeud const* racine)
{
	if(racine == NULL)
	{
		return 0;
	}
	else
	{
		if(racine->fils_droite == NULL && racine->fils_gauche == NULL)
		{
			return 1;
		}
		else
		{
			return nb_feuille(racine->fils_gauche) + nb_feuille(racine->fils_droite);
		}
	}
}

double predire(noeud const* racine, double* individu)
{
	critere_division* critere_courant = get_critere_enfant(racine);
	if(critere_courant != NULL)
	{
		if(individu[critere_courant->variable_observee - 1] <= critere_courant->mediane_corrigee)
		{
			if(racine->fils_gauche != NULL)
			{
				return predire(racine->fils_gauche, individu);
			}
			else
			{
				return racine->precision;
			}
		}
		else
		{
			if(racine->fils_droite != NULL)
			{
				return predire(racine->fils_droite, individu);
			}
			else
			{
				return racine->precision;
			}
		}
	}
	else
	{
		return racine->precision;
	}
}

critere_division* get_critere_enfant(noeud const* noeud_courant)
{
	if(noeud_courant != NULL)
	{
		if(noeud_courant->fils_gauche != NULL)
		{
			return noeud_courant->fils_gauche->critere;
		}
		else
		{
			if(noeud_courant->fils_droite != NULL)
			{
				return noeud_courant->fils_droite->critere;
			}
			else
			{
				return NULL;
			}
		}
	}
	else
	{
		return NULL;
	}
}

void afficher_noeud(noeud const* noeud_courant)
{
	critere_division* critere_courant = noeud_courant->critere;
	if(critere_courant != NULL)
	{
		printf("X%d ", critere_courant->variable_observee);
		if(critere_courant->test_inegalite == -1)
		{
			printf("<= ");
		}
		else
		{
			printf("> ");
		}
		printf("%lf ", critere_courant->mediane_corrigee);
	}
	printf("taille echantillon = %u ", noeud_courant->matrice->nb_lignes);
	printf("precision = %lf\n", noeud_courant->precision);
}

void affichage_arborescence(noeud const* arbre, unsigned int profondeur)
{
	int i;
		for(i = 0; i < profondeur; i++)
		{
			printf("  ");
		}
	if(arbre != NULL)
	{
		if(profondeur == 0)
		{
			afficher_noeud(arbre);
		}
		else
		{
			printf("|-");
			afficher_noeud(arbre);
		}
		if(arbre->fils_gauche != NULL || arbre->fils_droite != NULL)
		{
			affichage_arborescence(arbre->fils_gauche, profondeur + 1);
			affichage_arborescence(arbre->fils_droite, profondeur + 1);
		}
	}
	else
	{
		printf("|-x\n");
	}
}