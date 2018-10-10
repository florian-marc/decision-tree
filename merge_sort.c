//MARC Florian
//ESILV Promotion 2020
//TD L
//DATE : 13/01/2018

#include <stdlib.h>
#include "merge_sort.h"

void merge_sort(double* tab, int taille)
{
	if(taille<=1)
	{
		return;
	}
	else
	{
		double* tab1=tab;
		int taille1=taille/2;
		double* tab2=tab+taille1;
		int taille2=tab+taille-tab2;
		merge_sort(tab1,taille1);
		merge_sort(tab2,taille2);
		merge(tab1,tab2,taille);
	}
}

void merge(double* tab1, double* tab2, int taille)
{
	double* new_tab=(double*) malloc(taille*sizeof(double));
	int index1 = 0;
	int index2 = 0;
	int index_tab=0;
	while(index_tab < taille)
	{
		if(*(tab1+index1)<=*(tab2+index2))
		{
			*(new_tab + index_tab) = *(tab1 + index1);
			if(tab1+index1==tab2-1)
			{
				*(tab1+index1)=*(tab2+index2);
				if(tab2+index2<tab1+taille-1)
				{
					index2++;
				}
			}
			else
			{
				index1++;
			}
		}
		else
		{
			*(new_tab + index_tab) = *(tab2 + index2);
			if(tab2+index2==tab1+taille-1)
			{
				*(tab2+index2)=*(tab1+index1);
				if(tab1+index1<tab2-1)
				{
					index1++;
				}
			}
			else
			{
				index2++;
			}
		}
		index_tab++;
	}
	int index;
	for(index=0;tab1+index<tab2;index++)
	{
		*(tab1+index)=*(new_tab+index);
	}
	for(index=0;tab2+index<tab1+taille;index++)
	{
		*(tab2+index)=*(new_tab+index+(tab2-tab1));
	}
}