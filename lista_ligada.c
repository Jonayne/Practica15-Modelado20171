//By Jonayne  \( ͡° ͜ʖ ͡°)/

#include "lista_ligada.h"

/*Inserta un elemento en la lista y se regresa el nuevo tamaño de la lista*/
void inserta_elemento(Lista lista, void *value){ 
		Elemento* new= malloc(sizeof(Elemento)); //Apartamos memoria.
		new -> siguiente= *lista;
		new -> valor= value; //Asignamos el valor, y ponemos el siguiente.
		*lista= new;
}

/*Imprime los elementos de la lista como enteros*/
void imprime_lista_char(Lista lista){
	printf("\n");
	Elemento* next= *lista;
	while(next != NULL){
		Palabra* pal= (Palabra*)next -> valor;
		printf("Los repetidos de la palabra -%s- son: %d\n", (pal -> word) , (pal -> repetidos)); //Vamos iterando sobre la lista imprimiendo cada elemento.
		next= next -> siguiente;
	}
	printf("\n");
}

/*Libera(free) la memoria ocupada por la lista, sus elementos y valores*/
//No se te olvide liberar la memoria de cada elemento y su valor.
void borra_lista(Lista lista){
	size_t tam= longitud(lista);
	Elemento* element;
	for(int i= 0; i < tam; i++){
		element= quita_elemento(lista, 0);
		if (element != NULL){
			free(element -> valor); //Borramos cada elemento de la lista, y nos aseguramos de liberar la memoria.
			free(element);
		}
	}
	free(lista);
}

/*Remueve un elemento de una lista en una posición dada*/
//Si la posición no coincide con ningún elemento se regresa NULL
Elemento* quita_elemento(Lista lista, size_t posicion){
	size_t tam= longitud(lista);
	if(posicion >= tam || posicion < 0) return NULL; //Si la posición es ilegal, no hacemos nada.

	if(posicion == 0){ //Si es la cabeza.

		Elemento* next_to_head= (*lista) -> siguiente; //Borramos la cabeza y la nueva cabeza es el siguiente a esta.
		Elemento* head= *lista;
		(*lista) -> siguiente= NULL;
		(*lista) -> valor= NULL;
		*lista= next_to_head;
		return head;

	}else if(posicion == tam-1){ //Si es el último.

		Elemento* prev_to_last= *lista;

		for(int i= 1; i < tam-1; i++){
			prev_to_last= prev_to_last -> siguiente;
		}
		Elemento* last= prev_to_last -> siguiente;
		prev_to_last -> siguiente = NULL;
		last -> valor= NULL;
		last -> siguiente= NULL;

		return last;

	}else{	//Si no es ninguno de los anteriores.
	   	Elemento* next= *lista;
	   	for(int i= 0; i < tam; i++){
			if(i == posicion-1){
				Elemento* aux= next -> siguiente;
				Elemento* a_borrar= aux;
				Elemento* el_sig= a_borrar -> siguiente; //AHHHHHHH, odio acomodar referencias T_T.
				next -> siguiente= el_sig;
				a_borrar -> siguiente = NULL;
				a_borrar -> valor = NULL;
				
				return aux;
			}
			next= next -> siguiente;
		}
	}
}

/*Crea una lista vacía*/
Lista crea_lista(){
	Lista nueva_lista= calloc(1, sizeof(Lista)); //Apartamos la memoria para crear la nueva lista vacía.
	return nueva_lista;
}

/*Regresa el número de elementos en la lista*/
size_t longitud(Lista lista){
	size_t tam= 0;
	Elemento* next= *lista;

	while(next != NULL){ //Iteramos sobre la lista hasta que el "siguiente sea null", i.e, estemos en el último.
		next= next -> siguiente;							//Para ese momento ya habremos contado los elementos.
		tam+= 1;
	}
		
	return tam;
}
