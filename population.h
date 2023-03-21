#ifndef __POPULATION_H__
#define __POPULATION_H__
#include "individu.h"

/* Definition de type abstrait Population */
typedef struct pop {
	Individu indiv;
	struct pop *next;
} popu;

typedef popu *Population;

Population creerP();
Population init_pop(Population P, int TaillePop, int longIndiv);
Population meilleur_indiv(Population P, int tSelect);
Population last_Indiv(Population P);
void quickSort(Population first, Population last, int longIndiv);
Population croiseP(Population P1, int longIndiv, float pCroise, int tSelect);
void affichageP(Population P, int longIndiv);
void freePop(Population P);

#endif 
