/*Redes de Computadoras 2019-2 | Practica 1 Martinez Sanchez Jose Manuel*/
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include "list.h"
#include <string.h>
#include <stdlib.h>
#include <dirent.h>


int longitud = 0;

void display(void){
  tpuntero cabeza;
  cabeza = NULL;
  int input_convert;
  char user_input_c [3] ;
  int * pointer_input_convert = ( int *) malloc (sizeof ( input_convert ));



    do{
      printf("\n");
      printf("%-25s Elija una funcion:\n", " ");
      printf("1.Insertar archivo\n");
      printf("2.Leer archivo\n");
      printf("3.Eliminar archivo\n");
      printf("4.Imprimir archivos\n");
      printf("\n");
      memset(user_input_c, 0, sizeof user_input_c);
      user_input_c[0] = '\0';
      fflush(stdin);
      printf("Seleccion?: ");
      fgets( user_input_c,sizeof(user_input_c),stdin);
      input_convert = user_input_c[0] - '0';
      pointer_input_convert = &input_convert;

       if ( *pointer_input_convert >= 1 && *pointer_input_convert <= 4  ){
          switch( *pointer_input_convert){
             case 1 :
             printf("Ingrese el nombre del archivo:");
            // char fileName[50];
             char * fileName = malloc ( sizeof ( char ));
             scanf("%s",fileName);
             agrega_elemento (&cabeza, fileName);
             fflush(stdin);
            // printf("%c Ingresado correctamente",*fileName);
             printf("\n");
             break;

             case 2 :
                printf("Ingrese el indice del archivo a desplegar: (el indice maximo es %d) ",longitud);
                int index_fileName;
                scanf("%d", &index_fileName);
                if (isalpha(index_fileName) != 0) {
                  printf("Entrada invalida!: ");
                  break;
                } else {
                  if (index_fileName<longitud) {
                    if (is_file(obtenerArchivo(cabeza,index_fileName)) ) {
                      printf("%s Es un archivo valido\n", obtenerArchivo(cabeza,index_fileName));
                      printf("Desplegando archivo con el indice: %d \n",index_fileName);
                      char c[1000];
                      FILE *fptr;

                      if ((fptr = fopen((obtenerArchivo(cabeza,index_fileName)), "r")) == NULL){
                          printf("Error! opening file");
                          // Program exits if file pointer returns NULL.
                          exit(1);
                      }

                      // reads text until newline
                      fscanf(fptr,"%[^\n]", c);

                      printf("Data from the file:\n%s", c);
                      fclose(fptr);

                    }else if (is_dir(obtenerArchivo(cabeza,index_fileName))) {
                      struct dirent *de;  // Pointer for directory entry

                      // opendir() returns a pointer of DIR type.
                      DIR *dr = opendir((obtenerArchivo(cabeza,index_fileName)));

                      if (dr == NULL){
                          printf("Imposible abrir el directorio." );
                      }

                      while ((de = readdir(dr)) != NULL)
                              printf("%s\n", de->d_name);

                      closedir(dr);

                    }else{
                      printf("No es ARCHIVO ni Directorio! ");
                    }

                  }else{
                    printf("Indice fuera de rango!: ");
                    break;
                  }
                  break;
                }
                fflush(stdin);
                printf("\n");
             case 3 :
                printf("Ingrese el indice del archivo a eliminar\n");
                int deletedFile;
                scanf("%d", &deletedFile);
                printf("Eliminando elemento del indice: %d", deletedFile);
                elimina_elemento(cabeza,deletedFile,&cabeza);
                printf("\n");
                fflush(stdin);
                break;
             case 4 :
                printf( "Imprimiendo los elementos de la lista:\n" );
                imprimirLista (cabeza);
                fflush(stdin);
                printf("\n");
               break;
             default :
             break;
           }

      }else if (*pointer_input_convert >= 5 ) {
        printf( "***** Seleccion (int) %d invalida, seleccione [1-4] ******",*pointer_input_convert,"\n" );
        printf( "\n" );

      }else if (isalpha(user_input_c[0]) != 0 ) {
        printf( "***** Seleccion (char)  invalida ******","\n" );
        printf( "\n" );

      }else{
        printf( "*****Seleccion (caracter) invalida******","\n" );
        printf( "\n" );

      }
      pointer_input_convert=NULL;

      //free(pointer_input_convert);
    }while(true);
}



int main(void){
  display();
}
