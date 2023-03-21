#ifndef __INDIVIDU_H__
#define __INDIVIDU_H__
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

/* Definition de type abstrait Individu */
typedef struct ind {
	unsigned char Bit;
	struct ind *next;
} indiv;

typedef indiv *Individu;

Individu creerI();
Individu generation_iterative(Individu I, int longIndiv);
Individu generation_recursive(Individu I, int longIndiv);
int decode(Individu I, int longIndiv);
float qualite_indiv(Individu I, int longIndiv);
Individu croiseI(Individu I1, Individu I2, int longIndiv, float pCroise);
void affichageI(Individu I, int longIndiv);
void freeIndiv(Individu I);


#endif 
