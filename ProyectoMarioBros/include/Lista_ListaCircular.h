#ifndef __LISTA_LISTACIRCULAR__
#define __LISTA_LISTACIRCULAR__

#include "Columna.h"


extern Columna *basureroC;

void initNodoC(Columna *nodo);
Columna *creaNodoC ();
void insFinalNC (Columna **raiz, Columna *nodo);
int freeNodoC (Columna *nodo);
void eliminaListaC(Columna **r);
void imprimeListaC (Columna *raiz);

/*Listas Dobles*/

extern ElementoL *basureroD;

void initElementoL(ElementoL *nodo);
ElementoL *creaElementoL ();
void insFinalND (ElementoL **raiz, ElementoL *nodo);
int freeElementoL (ElementoL *nodo);
void eliminaListaS(ElementoL **r);
void imprimeListaD (ElementoL *raiz);

/*Funciones extra*/

void initMapa(arreglo *M);
int leeMapaArreglo (char *name, arreglo *m);
int creaMapa(Mapa *m, arreglo *m1);
void leeMapaCircular(Mapa *m, arreglo *m1);

#endif
