#include <stdlib.h>
#include <stdio.h>

#include "individu.h"
#include "population.h"

/* Sous-programme permettant de creer une Population */
Population creerP(){
	Population P = NULL;
	return P;
}

/* sous-programme utilise pour ajouter en fin de la liste chainee un Individu donne */
Population insert_tailP(Population P, Individu I) {
	Population temp, x=P;
	temp = (Population)malloc(sizeof(Population));
	temp->indiv = I;
	temp->next = NULL;
	if (P == NULL){
		P = temp;
	} else {
		while (x->next != NULL){
			x = x->next;
		}
		x->next = temp;
	}
	return P;
}


/* Sous-programme qui initialise la population pour une taille de population donne */
Population init_pop(Population P, int TaillePop, int longIndiv){
	int i;
	for (i=0; i < TaillePop; i++){
		Individu I = creerI();
		I = generation_iterative(I, longIndiv);
		P = insert_tailP(P, I);
	}
	return P;
}

/* Sous-programme permettant d'obtenir le dernier Individu de la Population */
Population last_Indiv(Population P){
	Population x = P;
	while (x != NULL && x->next != NULL){
		x = x->next;
	}
	return x;
}

/* Sous-programme permettant de partitionner la population selon un pivot */
Population parition(Population first, Population last, int longIndiv){
    /* premier individu de la population */
    Population pivot = first;
    Population front = first;
    Individu temp = NULL;
    while (front != NULL && front != last) {
        if (qualite_indiv(front->indiv, longIndiv) > qualite_indiv(last->indiv, longIndiv)) {
            pivot = first;
            /* échange de la value */
            temp = first->indiv;
            first->indiv = front->indiv;
            front->indiv = temp;
            
            /* visite du suivant */
            first = first->next;
        }
        
        /* visite du suivant */
        front = front->next;
    }
    /* change la dernière valeur à l'indiv actuel */
    temp = first->indiv;
    first->indiv = last->indiv;
    last->indiv = temp;
    return pivot;
}

/* Procedure permettant de trier la population par ordre decroissant;
    principe de diviser pour regner */
void quickSort(Population first, Population last, int longIndiv) {
    /* si la liste n'est composé que d'un seul indiv*/
    if (first == last) {
        return;
    }
    
    /*division de la population selon un pivot*/
    Population pivot = creerP();
    pivot = parition(first, last, longIndiv);
    
    if (pivot != NULL && pivot->next != NULL) {
        quickSort(pivot->next, last, longIndiv);
    }
    
    if (pivot != NULL && first != pivot) {
        quickSort(first, pivot, longIndiv);
    }
}

/* Sous-programme permettant de selectionner une partie de la Population selon un taux donne */
Population meilleur_indiv(Population P, int tSelect){
    Population x=P, e=P;
    if (P != NULL){
        int i;
        /* Decalage d'un des pointeurs en fonction du taux donner */
        for (i=0; i < tSelect; i++){
            x = x->next;
        }
        /* Parcours de la liste chainee en changeant les Individus inferieur au taux */
        while (x != NULL){
            x->indiv = e->indiv;
            x = x->next;
            e = e->next;
        }
    }
    return P;
}


/* Sous-programme permettant de croiser la Population en prennant aleatoirement deux individu consecutif */
Population croiseP(Population P1, int longIndiv, float pCroise, int TaillePop){
	Population P2 = creerP(), x1=P1;
	if (x1 != NULL ){
		/* Parcours de la Population et selection un nombre aleatoire dans la taille 
			de la Population correpondant aux Individu a croiser*/
		int i;
		for (i=0; i<TaillePop; i++){
			int s = rand() % TaillePop;
			int j = 0;
			
			/* Parcours la Population tant que le pointeur est defini et qu'il n'a pas atteint l'Individu souhaite */
			while (x1 != NULL && j != s){
				x1 = x1->next;
				j++;
			}
			
			/* Si les pointeurs sont defini cela signifi que les Individus existent 
				donc ils peuvent etre croises*/
			if (x1 != NULL && x1->next != NULL){
				Individu I = creerI();
				I = croiseI(x1->indiv, x1->next->indiv, longIndiv, pCroise); 
				P2 = insert_tailP(P2, I);
			} else {
				/* Ce cas permet de s'assurer que la Population ne reduit pas 
					car les Individus selectionner n'existe pas*/
				--i;
			}
			
			/* Afin que la Population soit parcourus a chaque iteration de la boucle */
			x1 = P1;
		}
	}
	return P2; 
}

/* Procedure permettant d'afficher la Population en parametre 
	soit tout les Individus en binaire ainsi que sa valeur decimal et sa qualite */
void affichageP(Population P, int longIndiv){
	Population i = P;
	while (i != NULL){
		affichageI(i->indiv, longIndiv);
		i = i->next;
	}
	printf("\n");
}

/* Procedure pour libere les allocations memoires effectuer pour la population */
void freePop(Population P){
	if (P->next != NULL) {
		freeIndiv(P->indiv);
		freePop(P->next);
		free(P);
	}
	
}

