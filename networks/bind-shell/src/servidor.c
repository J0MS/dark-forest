/*
 * Redes de Computadoras 2019-2
 * Martinez Sanchez Jose Manuel
 * servidor.c
 */
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <signal.h>

#define BACKLOG 5
#define BUFFERSIZE 2048
#define MAXSIZE 2048

void sendError(char *info) {
    perror(info);
    exit(1);
}

void configuration(char inputBuffer[], char *args[], int *background){
    const char s[4] = " \t\n";
    char *token;
    token = strtok(inputBuffer, s); //Rompe la cadena inputBuffer en segmentos o tókens dependiendo de los delimitadores de s.
    int i = 0;
    while( token != NULL){
        args[i] = token;
        i++;
        token = strtok(NULL,s);
    }
    args[i] = NULL;
}

void manageConnection(int sock){
    char buffer[BUFFERSIZE];
    int received = -1;
    char data[MAXSIZE];
    memset(data,0,MAXSIZE);
      while(1) {
        data[0] = '\0';
        if((received = recv(sock, buffer,BUFFERSIZE,0))<0){
            sendError("Error al recibir datos.");
        }
        buffer[received] = '\0';
        strcat (data,  buffer);
        if (strcmp(data, "EOF")==0)
            exit(0);

        printf("Comando recibido:",data);
        puts(data);
        char *args[100];
        configuration(data,args,0);
        int pipefd[2],lenght;

        if(pipe(pipefd)){  //Llamada al sistema para crear comunicacion unidireccional entre dos descriptores de archivo.
          sendError("Error en el pipeline.");//<0 Error en crear el pipe()
        }

        pid_t process_id = fork(); //Bifurcacion, necesaria para execvp(), 1 llamada bifurca en = 2n
        char path[MAXSIZE];

        if(process_id==0){ // Proceso hijo creado.
            close(1);
            dup2(pipefd[1],1);
            close(pipefd[0]);
            close(pipefd[1]);
            execvp(args[0],args); // Ejecuta el comando.
        }
        else{
            if(process_id>0){ // ID del proceso hijo creado, enviado al procesos padre.
                close(pipefd[1]);
                memset(path,0,MAXSIZE);
                while(lenght=read(pipefd[0],path,MAXSIZE-1)){
                  if(send(sock,path,strlen(path),0) != strlen(path) ){
                      sendError("Error en el envio.");
                  }
                  fflush(NULL); // Borrar el buffer de entrada estandar (stdin)
                  memset(path,0,MAXSIZE);
                }
                    close(pipefd[0]);
                }
                else{
                    printf("Error !\n");
                    exit(0);//
                }
              }
      }
}

int main(int argc, char const *argv[]){
    printf("%-25s%-25s%s\n", " " ,"Esperando conexiones en el puerto:",argv[1]);
    if (argv[1]==NULL) {
      printf("%s ERROR, no ingreso el puerto!\n" );
      return 0;
    } else {
      int serverSocket,clientSocket;
      struct sockaddr_in handlingServersocket, handlingClientsocket;
      unsigned int clientlen = sizeof(handlingClientsocket);
      signal(SIGPIPE, SIG_IGN);
      if((serverSocket = socket(PF_INET, SOCK_STREAM,IPPROTO_TCP))<0){
          sendError("Failed");
      }
      memset(&handlingServersocket,0,sizeof(handlingServersocket));
      handlingServersocket.sin_family = AF_INET;
      handlingServersocket.sin_addr.s_addr= htonl(INADDR_ANY);
      handlingServersocket.sin_port = htons(atoi(argv[1])); //Obteniendo el puerto.

      if(bind(serverSocket, (struct sockaddr *) & handlingServersocket,sizeof(handlingServersocket))<0){
          sendError("Error al crear el socket.");
      }
      if(listen(serverSocket,BACKLOG)<0){
          sendError("Error al conectar.");
      }
      while(1){
          if((clientSocket = accept(serverSocket,(struct sockaddr *) &handlingClientsocket,&clientlen))<0){
              sendError("Error en la conexion.");
          }
          fprintf(stdout, "Conexion aceptada desde: %s:%s\n",inet_ntoa(handlingClientsocket.sin_addr),argv[1] );
          manageConnection(clientSocket);
      }

      return 0;
    }

}
/*
 * servidor.c
 */
