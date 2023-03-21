#include <stdlib.h>
#include <time.h>

#include "individu.h"
#include "population.h"

void progamme(int TaillePop, int longIndiv, int nGen, float pCroise, int tSelect){
	
	/* Initialisation de la Population*/
	Population P = creerP();
	P = init_pop(P, TaillePop, longIndiv);
	
	/* Repetion un nombre de generation donnee par nGen*/
	int i;
	for (i=0; i<nGen; i++){
		/* Croissement de la Population */
		P = croiseP(P, longIndiv, pCroise, TaillePop);
		
		/* Triage de la Population */
		quickSort(P, last_Indiv(P), longIndiv);
		
		/* Selection des meilleur Individus de la Population */
		P = meilleur_indiv(P, tSelect);		
	}
	/* Affichage du meilleur Individu */
	printf("Le meilleur Individu de la Population est : ");
	affichageI(P->indiv, longIndiv);
	
}


int main(void){
	/* Initialistation des variables globales necessaires a l'execution */
	const int longIndiv = 16;
	const float pCroise = 0.5;
	srand(time(NULL));
	const int TaillePop = rand() % (200 - 20 + 1)+ 20;
	const float tSelect_p100 = (float)(rand() % (90 - 10 + 1) + 10)/(float)100;
	const int tSelect = TaillePop - TaillePop*(1-tSelect_p100);
	const int nGen = rand() % (200 - 20 + 1)+ 20;
	
	/* Affichage des variables globales pour informer l'utilisateur des donnees */
	printf("TaillePop : %d \n",TaillePop);
	printf("tSelect en % : %.2f \n",tSelect_p100);
	printf("tSelect : %d \n",tSelect);
	printf("nGen : %d \n",nGen);
	printf("\n");
	
	progamme(TaillePop, longIndiv, nGen, pCroise, tSelect);
		
    return 0;
}
