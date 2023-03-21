#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#include "individu.h"


/* Sous-programme permettant de creer un Individu */
Individu creerI(){
	Individu I = NULL;
	return I;
}

/* sous-programme utilise pour ajouter en fin de la liste chainee un Bit genere aleatoirement */
Individu insert_tailI(Individu I, unsigned char b) {
	Individu temp, x=I;
	temp = (Individu)malloc(sizeof(Individu));
	temp->Bit = b;
	temp->next = NULL;
	if (I == NULL){
		I = temp;
	} else {
		while (x->next != NULL){
			x = x->next;
		}
		x->next = temp;
	}
	return I;
}

/* Sous-programme de generation d'individu aleatoire de maniere iterative */
Individu generation_iterative(Individu I, int longIndiv){
	unsigned char b;
	int i;
	for (i=0; i<longIndiv; i++){
		b = rand() % 2;
		I = insert_tailI(I, b);
	}
	return I;
}

/* sous-programme utilise pour ajouter en tete de la liste chainee un Bit genere aleatoirement */
Individu insert_headI(Individu I, unsigned char b){
	Individu temp;
	temp = (Individu)malloc(sizeof(Individu));
	temp->Bit = b;
	temp->next = I;
	return temp;
}

/* Sous-programme de generation d'Individu aleatoire de maniere recusive */
Individu generation_recursive(Individu I, int longIndiv){
	if (longIndiv == 0){
		return creerI();
	} else {
		unsigned char b = rand() % 2;
		/* Permet d'ajouter le Bit en fin de la liste*/
		return insert_headI(generation_recursive(insert_headI(I, b), longIndiv-1), b);
	}
}

/* Sous-programme de décodage de la liste de bits; passage de binaire a decimal */
int decode(Individu I, int longIndiv){
	/* Pour passer de la base binaire a decimal : 
		nombre dec = somme(2^i) avec i variant de 0 a la longeur du nombre binaine -1  
	Etant donner l'utilisation d'une liste simplement chainee et que la premiere valeur de la liste
		est le 2 a la puissance de plus haut degre le boucle fonction en decrementation */
	Individu x=I;
	int value = 0, i;
	for (i=longIndiv; i>0; i--){
		if (x->Bit == 1){
			value += pow(2,i-1);
		}
		x = x->next;
	}
	return value;
}

/* Sous-programme de croiser deux individu en fonction de d'une probaliliter donnee */
Individu croiseI(Individu I1, Individu I2, int longIndiv, float pCroise){
	Individu I3 = creerI(), x1=I1, x2=I2;
	float proba;
	int i;
	for (i=0; i<longIndiv; i++){
		/* La variable 'proba' est un nombre aleatoire entre 0 et 100 
			qui est compare a la probabilite pCroise defini aleatoirement
			a l'excution du programme */
		proba = (float)(rand() % 101) / (float)100;
		
		/* Choix arbitraire que le premier Individu soit 
			le celui associer a la probabilite*/
		if (proba <= pCroise) {
			I3 = insert_tailI(I3, x1->Bit);
		} else {
			I3 = insert_tailI(I3, x2->Bit);
		}
		
		x1 = x1->next;
		x2 = x2->next;
	}
	return I3;
}

/* Sous-programme de qualite_indiv permettant de calculer X  = (x/ (2^longIndiv) )* (B−A)+ A */
float X(float x, int longIndiv){
	float A=0.1, B=5;
	return (x/pow(2,longIndiv))*(B-A)+A;
}

/* Sous-programme qui calcul la qualite d'un individu, par la fonction reel F1(x) = -X^2 */
float qualite_indiv(Individu I, int longIndiv){
	float x;
	/* On decode l'individu pour obtenir la valeur decimal 
		dans le calcule de la qualite de l'Individu */
	x = decode(I, longIndiv); 
	return -log(X(x, longIndiv));
}

/* Procedure permettant d'afficher un Individu en binaire ainsi que sa valeur decimal et sa qualite */
void affichageI(Individu I, int longIndiv){
	Individu x = I;
	while (x != NULL){
		printf(" %d", x->Bit);
		x = x->next;
	}
	printf(" - decode %d", decode(I, longIndiv));
	printf(" - qualite %f", qualite_indiv(I, longIndiv));
	printf("\n");
}

/* Procedure pour libere les allocations memoires effectuer pour un Individu */
void freeIndiv(Individu I){
	if (I != NULL){
		freeIndiv(I->next);
		free(I);
	}
}

