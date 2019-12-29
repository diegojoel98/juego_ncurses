#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <Lista_ListaCircular.h>

Columna *basureroC = NULL;

void initNodoC(Columna *nodo)
{
	nodo->LD = NULL;
	nodo->ant = nodo->sig = nodo;

}

Columna *creaNodoC ()
{
	Columna *apu;

	if (basureroC == NULL)
	{
		apu = (Columna *)malloc(sizeof(Columna));
		if (apu != NULL)
			initNodoC(apu);
	}
	else
	{
		apu = basureroC;
		basureroC = basureroC->sig;
		initNodoC(apu);
	}
	return apu;
}

/*!
\function void insFinalNC (Columna **raiz, Columna *nodo)
\brief Inserta una nodo al final de una lista circular.
*/
void insFinalNC (Columna **raiz, Columna *nodo)
{
	
	if (!*raiz)
		*raiz = nodo;
	else
	{
		nodo->sig = *raiz;
		nodo->ant = (*raiz)->ant;
		(*raiz)->ant = nodo;
		nodo->ant->sig = nodo;
	}

}

int freeNodoC (Columna *nodo)
{
	if (nodo == NULL)
		return -1;
	
	initNodoC(nodo);
	nodo->sig = basureroC;
	basureroC = nodo;
	return 0;
}

void eliminaListaC(Columna **r)
{
	Columna *apu;
	
	while (*r != NULL)
	{
		apu = *r;
		*r = (*r)->sig;
		freeNodoC(apu);
	}
}


/*Listas Dobles*/


ElementoL *basureroD = NULL;

void initElementoL(ElementoL *nodo)
{
	nodo->el.simbolo = ' ';
	nodo->el.color = ' ';
	nodo->el.moneda = 0;
	nodo->el.enemigo = 0;
	nodo->el.portal = 0;
	nodo->ant = nodo->sig = NULL;
}

ElementoL *creaElementoL ()
{
	ElementoL *apu;

	if (basureroD == NULL)
	{
		apu = (ElementoL *)malloc(sizeof(ElementoL));
		if (apu != NULL)
			initElementoL(apu);
	}
	else
	{
		apu = basureroD;
		basureroD = basureroD->sig;
		initElementoL(apu);
	}
	return apu;
}

/*!
\function void insFinalND (ElementoL **raiz, ElementoL *nodo)
\brief Inserta una nodo al final de una lista doble.
*/
void insFinalND (ElementoL **raiz, ElementoL *nodo)
{
	
	if (!*raiz)
		*raiz = nodo;
	else
	{
	    ElementoL *apu;

	    apu = *raiz;

	    while (apu->sig != NULL)
	        apu = apu->sig;
	    apu->sig = nodo;
	    nodo->ant = apu;
	}
	
}

int freeElementoL (ElementoL *nodo)
{
	if (nodo == NULL)
		return -1;
	
	initElementoL(nodo);
	nodo->sig = basureroD;
	basureroD = nodo;
	return 0;
}

void eliminaListaS(ElementoL **r)
{
	ElementoL *apu;
	
	while (*r != NULL)
	{
		apu = *r;
		*r = (*r)->sig;
		freeElementoL(apu);
	}
}
 

/*-------------Funciones adicionales para el main------------------*/


void initMapa(arreglo *M)
{
    M->ren = M->col = 0;
    M->datos = 0;
}

/* volvi a usar la funcion del maestro para meter todos los datos en un arreglo normal, y meti mapa solo para obtener el renglon y columna del mapa para la lista circular de listas dobles*/

int leeMapaArreglo (char *name, arreglo *m)
{
    FILE *arch;
    char *buff, *ptr;
    int i, j, k;

    initMapa(m);

    arch = fopen(name, "r");
	 if (arch)
    {
				ssize_t num;
				size_t n = 8192;

				buff = (char *)malloc(n * sizeof(char));//Buffer para leer renglones del archivo
				if (!buff)
				{
					fprintf (stderr, "Error en leeMapa: No se pudo obtener memoria para el buffer\n");
					return -1;
				}
				//Leemos y analizamos la primera linea del archivo que contiene el número
				//de renglones y columnas del mapa.
				num = getline(&buff, &n, arch); //Leemos la primer linea del archivo.

				//Encontramos el número de renglones y columnas del archivo.
				ptr = strtok(buff, " ,\n"); 
				m->ren = atoi(ptr);
				
				ptr = strtok(NULL, " ,\n");
				m->col= atoi(ptr);
				

				//Obtenemos memoria para almacenar el mapa.
				m->datos = (Elemento *)malloc(m->col * m-> ren * sizeof(Elemento));
				if (!buff)
				{
					fprintf (stderr, "Error en leeMapa: No se pudo obtener memoria para almacenar el mapa.\n");
					free(buff);
					return -1;
				}

				k = 0;
				for (i = 0; i < m->ren; ++i)
				{
					 num = getline(&buff, &n, arch); //Leemos una linea del archivo.
					 if (num < 2 * m->col)
					 {
						  fprintf (stderr, "Error en leeMapa: no hay suficientes datos en el renglon %d\n", i+1);
						  exit(1);
					 }
					 else
						  for (j = 0; j < 2 * m->col; j += 2, ++k)
						  {
								m->datos[k].simbolo = buff[j];
								m->datos[k].color = buff[j+1];
						  }
				}
				fclose(arch);
    			free (buff);
	 }
	 else
	 {
		fprintf (stderr, "Error en leeMapa: No se pudo abrir el archivo- \"%s\"\n", name);
		return -1;
    }	
	 return 0;
}

int creaMapa(Mapa *m, arreglo *m1)
{
    int i, j;
    Columna *auxC;
    ElementoL *auxE;
	 m->ren = m1->ren;
	 m->col = m1->col;
	 m->next = 0;
	 m->LC = NULL;
	for (i = 0; i < m->col; ++i)
	{
		auxC = creaNodoC ();
				
			for (j = 0; j < m->ren; ++j)
			{
					auxE = creaElementoL ();
					insFinalND( &(auxC->LD), auxE);						
			}
				
		insFinalNC ( &(m->LC), auxC); 
				
	}
	 return 0;
}

void leeMapaCircular(Mapa *m, arreglo *m1)
{
	int i, j, k;
	Columna *apu = m->LC;
	
	
	for (i = 0; i < m->col; ++i, apu = apu->sig)
	{	
			ElementoL *apuL;

			apuL = apu->LD;
         k = i;			
			for (j = 0; j < m->ren; ++j, k += m->col, apuL = apuL->sig)
			{
				 
				apuL->el.simbolo = m1->datos[k].simbolo;
				apuL->el.color = 	m1->datos[k].color;
				
			}
	}
}


