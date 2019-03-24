#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/stat.h>
#define _GNU_SOURCE


typedef struct Registro{
    void * valor;
  //  char valor;
    struct Registro *sig; //El puntero siguiente
}Nodo;

typedef Nodo *tpuntero;

extern int longitud;

typedef struct lista {
    struct Nodo * cabeza;
    int longitud;
  }Lista;

typedef Lista *lst;
//struct lista lst;


void agrega_elemento (tpuntero *cabeza, char * e);
void imprimirLista (tpuntero cabeza);
void borrarLista (tpuntero *cabeza);


void agrega_elemento (tpuntero *cabeza, char * e){
    tpuntero nuevo; //Creamos un nuevo nodo
    nuevo = malloc(sizeof(Nodo)); //Utilizamos malloc para reservar memoria para ese nodo
    nuevo->valor = e; //Le asignamos el valor ingresado en la terminal a ese nodo
    nuevo->sig = *cabeza; //Le asignamos al siguiente el valor de cabeza
  //  nuevo->id =
  //  printf("%c IDENTIFICador", nuevo->sig);
    *cabeza = nuevo; //Cabeza pasa a ser el ultimo nodo agregado
    longitud++;
}

void elimina_elemento (tpuntero cabeza,int indexArchivo,tpuntero *c2){
  int tmp = 0;
  while(cabeza != NULL){ //Mientras cabeza no sea NULL
      if (tmp == indexArchivo-1) {
          tpuntero nuevo; //Creamos un nuevo nodo
          nuevo = malloc(sizeof(Nodo)); //Utilizamos malloc para reservar memoria para ese nodo
          nuevo = *c2;
        //  nuevo->sig = cabeza->sig;
          //nuevo->sig = nuevo->sig;
          nuevo->sig =   cabeza->sig;
          *c2 = nuevo;
      //    nuevo->valor = "N"; //Le asignamos el valor ingresado en la terminal a ese nodo
      //    nuevo->sig = *c2; //Le asignamos al siguiente el valor de cabeza
        //  printf("%c IDENTIFICador", nuevo->sig);
        //  *c2 = nuevo; //Cabeza pasa a ser el ultimo nodo agregado
          longitud--;
          break;
      }
      cabeza = cabeza->sig; //Pasamos al siguiente nodo
      tmp++;
  }


}

void imprimirLista(tpuntero cabeza){
    while(cabeza != NULL){ //Mientras cabeza no sea NULL
        printf("%s\n",cabeza->valor); //Imprimimos el valor del nodo
        cabeza = cabeza->sig; //Pasamos al siguiente nodo
    }
}


const char * obtenerArchivo(tpuntero cabeza,int indexArchivo){
    char * cadena;
    int tmp = 0;
    while(cabeza != NULL){ //Mientras cabeza no sea NULL
        if (tmp == indexArchivo) {
            cadena = cabeza->valor;
            break;
        }
        cabeza = cabeza->sig; //Pasamos al siguiente nodo
        tmp++;
    }
    return cadena;
}


void imprimirMayusculas(tpuntero cabeza){
    while(cabeza != NULL){ //Mientras cabeza no sea NULL
      //  printf("%4c",toupper(cabeza->valor)); //Imprimimos el valor del nodo
        cabeza = cabeza->sig; //Pasamos al siguiente nodo
    }
}

bool isNumber(char *input) {
    for (int i = 0; input[i] != '\0'; i++)
        if (isalpha(input[i]))
            return false;
    return true;
}


bool is_file(const char* path) {
    struct stat buf;
    stat(path, &buf);
    return S_ISREG(buf.st_mode);
}

bool is_dir(const char* path) {
    struct stat buf;
    stat(path, &buf);
    return S_ISDIR(buf.st_mode);
}


void borrarLista(tpuntero *cabeza){
    tpuntero actual; //Puntero auxiliar para eliminar la cabeza
    while(*cabeza != NULL){
        actual = *cabeza;
        printf("Elemento a ser eliminado: %c, elemento eliminado: %c,Longitud: %d",actual->valor,actual->valor,longitud); //Elemento a ser eliminado: A, elemento eliminado: A, longitud de lista: 10
        longitud--;
        printf ("\n");
        *cabeza = (*cabeza)->sig;
        free(actual);
    }
}
