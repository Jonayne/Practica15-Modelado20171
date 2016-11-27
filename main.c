//By Jonayne  \( ͡° ͜ʖ ͡°)/.

#include "main.h"
#define BUFFERSIZE 200

int main(int argc, char const *argv[]){
    // Verifica si hay menos de 3 parametros
    // si no entonces se imprimen las instrucciones
    // y se para la ejecución del programa
    if (argc < 3){
        imprime_instrucciones();
        exit(-1);
    }

    int i; //:O

    //Abrimos los archivos de lectura.
    FILE* entrada[argc-2];
    for(i= 0; i < argc-2 ; i++){
    	entrada[i] = fopen(argv[i+1], "r");
    	if (entrada[i] == NULL){ //Revisamos si pudimos abrirlo correctamente.
    		printf("\n\n*-*-*-**-*-*-**-*-*-**-*-*-**- ¡ERROR! *-*-*-**-*-*-**-*-*-**-*-*-**-\n\n- No se pudo abrir el archivo: %s\nVerifique que escribió bien el nombre de este.-\n\n", argv[i+1]);
    		exit(-1);
		}
    }

    //Abrimos el archivo de escritura.
    FILE* salida= fopen(argv[argc-1], "w"); //No revisamos si regreso null pues con "w", si no existe el archivo crea uno.

    //Creamos un arreglo de Listas, cada lista representará un archivo.
    Lista archivos[argc-2];

    /*	Rellenamos cada Lista con su archivo correspondiente, cada 
		elemento de la lista tendrá por valor una estructura Palabra
		la cual tiene como atributos un apuntador a un char y un contador de repetidos.
		Con este proceso tendremos las palabras de cada archivo bien organizadas con sus correspondientes
		número de repetidos. 
    */
    for(i= 0; i < argc-2; i++){
    	archivos[i] = crea_lista();
    	char buffer[BUFFERSIZE];
		while(fgets(buffer, BUFFERSIZE, entrada[i])){ //Obtenemos un renglón.
			char* token= NULL;
			token= strtok(buffer, " ,.-\n"); //Obtenemos la primer palabra.
			while(token != NULL){
				if(es_repetida(archivos[i], token)){ //Revisamos si la palabra ya se encontraba en esta lista.
					aumenta_reps(archivos[i], token); //Si sí, aumentamos la var. correspondiente.
				}else{	//Si no, la agregamos.
					Palabra* nueva= malloc(sizeof(Palabra));
					nueva -> repetidos = 1;
					nueva -> word = strndup(token, BUFFERSIZE); //Copiamos el contenido de token y lo pasamos a otro apuntador.
					inserta_elemento(archivos[i], nueva); //Metemos la -Palabra- a nuestra lista.
				}
				token= strtok(NULL, " ,.-\n"); //Iteramos sobre el renglón, obteniendo todas las palabras.
			}
		}
    }

    //Obtenemos las palabras más repetidas de cada archivo.
    Palabra* palabras_mas_repetidas[argc-2];
    for(i= 0; i < argc-2; i++){
    	palabras_mas_repetidas[i]= palabra_mas_repetida(archivos[i]);
    }

    //Imprimimos en la consola nuestros resultados, avisando que los guardamos en un archivo de salida.
    printf("\nNombre del archivo    ---    Palabra más repetida    ---    Núm. de repeticiones\n\n");
    for(i= 0; i < argc-2; i++){
    	printf(" %s       		  %s       	    	      %d\n\n", argv[i+1], (palabras_mas_repetidas[i] -> word), (palabras_mas_repetidas[i] -> repetidos));
    }
    printf("Se han guardado los resultados en el archivo: %s\n\n", argv[argc-1]);
    
    //Aquí escribimos los resultados en el archivo de salida.
    fprintf(salida, "**************************************************************************************\n");
    fprintf(salida, "*    Nombre del archivo    -    Palabra más repetida    -    Núm. de repeticiones    *\n*                                                                                    *\n");
    for(i= 0; i < argc-2; i++){
    	fprintf(salida, "      %s       		          %s      	    	         %d\n*                                                                                    *\n", argv[i+1], (palabras_mas_repetidas[i] -> word), (palabras_mas_repetidas[i] -> repetidos));
	}
	fprintf(salida, "**************************************************************************************");

    //Cerramos los archivos de lectura y salida, además de liberar la memoria.
    libera_memoria(archivos, argc-2);
    for(i= 0; i < argc-2; i++){
    	fclose(entrada[i]);
    }
    fclose(salida);
}

/* ------ Implementación de funciones ------ */

/*Imprime las instrucciones de uso del programa*/
void imprime_instrucciones(){
	printf("\n\n*-*-*-**-*-*-**-*-*-**-*-*-**- ¡ERROR! *-*-*-**-*-*-**-*-*-**-*-*-**-\n\nEl formato de entrada es incorrecto, el uso correcto es el siguiente:\n\n./<nombre_ejecutable> <archivo_de_lectura1> ... <archivo_de_lecturaN> <archivo_de_salida>\n\n¡Prueba de nuevo!.\n\n*-*-*-**-*-*-**-*-*-**-*-*-**-*-*-**-*-*-**-*-*-**-*-*-**-*-*-**-*-*-\n\n");
}

/*Aumenta el atributo "repetidos" de una palabra*/
void aumenta_reps(Lista lista, char* pal){
	Elemento* tmp= *lista;
	while(tmp != NULL){
		char* word= ((Palabra*)(tmp -> valor))-> word;
		if(strcmp(word, pal) == 0){ //Encontramos una palabra repetida para aumentar el atributo "repetidos" de esta.
			((Palabra*)(tmp -> valor)) -> repetidos = (((Palabra*)(tmp -> valor)) -> repetidos) + 1;
			return;
		}
		tmp= tmp -> siguiente;
	}
}

/*Revisa si una palabra ya se encuentra en la lista*/
int es_repetida(Lista lista, char* palabra){
	Elemento* next= *lista;
	while(next != NULL){
		char* letras= ((Palabra*)(next -> valor)) -> word;
		if(strcmp(letras, palabra) == 0){ //Revisamos si esta palabra ya estaba antes en la lista.
			return TRUE;
		}
		next= next -> siguiente;
	}
	return FALSE;
}

/*Devuelve la palabra más repetida en un archivo*/
Palabra* palabra_mas_repetida(Lista lista){
	Palabra* palabra;
	int max= 0;
	Elemento* tmp= *lista;
	while(tmp != NULL){
		int repetidos= ((Palabra*)(tmp -> valor)) -> repetidos; //Obtenemos el atributo repetidos de esta palabra.
		if(repetidos >= max){ //Si encontramos una palabra que esté más repetida que nuestro max.
			palabra= (Palabra*)tmp -> valor;
			max= repetidos;
		}
		tmp= tmp -> siguiente;
	}
	return palabra;
}

/*Libera la memoria que ocupa un arreglo de listas*/
void libera_memoria(Lista* listas, int tam){
	for(int i= 0; i < tam; i++){
    	borra_lista(*(listas+i));
    }
}
