#ifndef __COLUMNA__
#define __COLUMNA__

typedef 
struct 
{
    char simbolo;
    char color;
	 int moneda;
	 int enemigo;
	 int portal;
} Elemento;


typedef 
struct _ElementoL
{
	 Elemento el;
	 struct _ElementoL *sig, *ant;
} ElementoL;

typedef struct _Columna
{
	ElementoL *LD;
	struct _Columna *sig, *ant;
} Columna;

typedef
struct 
{
   int ren, col, next; //Número de renglones, columnas en el mapa y a que mapa se transporta
	Columna *LC;
 
} Mapa;



typedef
struct
{
    int ren, col; //Número de renglones y columnas en el mapa
    Elemento *datos;
} arreglo;
#endif
