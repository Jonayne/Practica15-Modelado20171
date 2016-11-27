//By Jonayne  \( ͡° ͜ʖ ͡°)/ 

#ifndef LISTA_LIGADA_H_ // Guarda para evitar include circulares
#define LISTA_LIGADA_H_
//Includes necesarios.
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*Estructura *elemento* que simula a un nodo de la lista.*/
struct elemento{
	struct elemento* siguiente;
	void* valor;
};

// defino alias para los datos (struct elemento) y (Elemento**)
typedef struct elemento Elemento; 
typedef Elemento** Lista;

#include "main.h"

/*Libera(free) la memoria ocupada por la lista, sus elementos y valores*/
//No se te olvide liberar la memoria de cada elemento y su valor.
void borra_lista(Lista);

/*Remueve un elemento de una lista en una posición dada*/
//Si la posición no coincide con ningún elemento se regresa NULL
Elemento* quita_elemento(Lista, size_t posicion);

/*Imprime los elementos de la lista como enteros*/
void imprime_lista_char(Lista lista);

/*Crea una lista vacía*/
Lista crea_lista();

/*Inserta un elemento en la lista y se regresa el nuevo tamaño de la lista*/
void inserta_elemento(Lista lista, void *valor);

/*Regresa el número de elementos en la lista*/
size_t longitud(Lista lista);

#endif //LISTA_LIGADA_H_
