//By Jonayne  \( ͡° ͜ʖ ͡°)/ 

#ifndef MAIN_H // Guarda para evitar include circulares
#define MAIN_H

#define TRUE 1
#define FALSE 0

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista_ligada.h"

/* Estructura palabra, que tiene una como atributos una cadena, y la veces que se ha repetido en un texto. */
struct palabra{
	char* word;
	int repetidos;
};

typedef struct palabra Palabra; //Defino un alias para palabra.

/* ------ FUNCIONES ------ */

/*Imprime las instrucciones de uso del programa*/
void imprime_instrucciones();

/*Revisa si una palabra ya se encuentra en una lista*/
int es_repetida(Lista lista, char* palabra);

/*Devuelve la palabra más repetida en una lista*/
Palabra* palabra_mas_repetida(Lista lista);

/*Aumenta el atributo "repetidos" de una palabra*/
void aumenta_reps(Lista lista, char* pal);

/*Libera la memoria que ocupa un arreglo de listas*/
void libera_memoria(Lista* listas, int tam);


#endif //MAIN_H
