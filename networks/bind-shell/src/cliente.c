/*
 * Redes de Computadoras 2019-2
 * Martinez Sanchez Jose Manuel
 * cliente.c
 */
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#define BUFFSIZE 2048
static const char ALUMNO[] = "Alumno: Martinez Sanchez Jose Manuel";
static const char MATRICULA[] = "408027094";
static const char ID_PRACTICA[] = "2";


void sendError(char *mess){
  perror(mess);
  exit(1);
}

int main(int argc, char *argv[]){
      printf("\n");
      printf("%-25s%-25s", " " ,"Redes de Computadoras 2019-2\n");                                                                                                                                   printf("%-25s%-25s - %-25s% \n", " ",ALUMNO,MATRICULA);                                                                                                                                        printf("%-25s%-25s%-25s \n", " ","Practica:" ,ID_PRACTICA);
      printf("\n");
      printf("Para terminar la conexion escriba EOF.\n");
      printf("\n");
      int actualSocket;
      struct sockaddr_in actualServer;
      char buffer[BUFFSIZE];
      unsigned int echolen;
      int received = 0;
      if (argc != 3){
            fprintf(stderr, "No ingreso parametros validos!\n");
            exit(1);
      }

      if ((actualSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0){
            sendError("Imposible crear socket");
        }
      memset(&actualServer, 0, sizeof(actualServer));
      actualServer.sin_family = AF_INET;
      actualServer.sin_addr.s_addr = inet_addr(argv[1]);
      actualServer.sin_port = htons(atoi(argv[2]));
      if (connect(actualSocket,(struct sockaddr *) &actualServer,sizeof(actualServer)) < 0){
          sendError("Imposible conectar al servidor");
      }
      char s[100];
      while(1) {
        printf(">: " );
        fgets(s,100,stdin);
        s[strlen(s)-1]='\0'; //Eliminar '\n'
        echolen = strlen(s);

        /*  Desde el cliente; */
        if (send(actualSocket, s, echolen, 0) != echolen){
            sendError("Error en la respuesta");
        }
        if(strcmp(s,"EOF") == 0){
          printf("Conexion finalizada\n" );
        exit(0);
        }
        fprintf(stdout, "Respuesta del servidor:\n \n");
        while (received < echolen){
            int bytes = 0;
            if ((bytes = recv(actualSocket, buffer, echolen, 0)) < 1){
                sendError("Error al recibir respuesta.");
            }
            received += bytes;
            buffer[bytes] = '\0';
            fprintf(stdout, buffer);
        }
        int bytes = 0;
        do {
            buffer[bytes] = '\0';
            printf("%s\n", buffer);
        } while((bytes = recv(actualSocket, buffer, BUFFSIZE-1, 0))>=BUFFSIZE-1);
        buffer[bytes] = '\0';
        printf("%s\n", buffer);
        printf("\n");
    }
}
/*
 * cliente.c
 */
