/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>

     
     char buffer[512];


void error(const char *msg)
{
    perror(msg);
    exit(1);
}

void *mostrardir()
{
   printf("%s",getcwd(buffer,-1));
}

int main(int argc, char *argv[])
{
     int sockfd,newsockfd, portno;
     socklen_t clilen;
     int n;
     char *cmd;
     char *atb1;
     char *atb2;
     int caso,i;
     
     //Creacion de Threads
     int cic=0; //Variable de cantidad de threads
     pthread_t tid[5000];//Cantidad de threads -- Request al servidor
     struct sockaddr_in serv_addr, cli_addr;
    
     if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     }
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0) 
        error("ERROR opening socket");
     bzero((char *) &serv_addr, sizeof(serv_addr));
     portno = atoi(argv[1]);
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0) 
              error("ERROR on binding");
     listen(sockfd,5);
     while (1){
     clilen = sizeof(cli_addr);
     newsockfd = accept(sockfd, 
                 (struct sockaddr *) &cli_addr, 
                 &clilen);
     if (newsockfd < 0) 
          error("ERROR on accept");
     bzero(buffer,256);
     n = recv(newsockfd,buffer,255,0);
     if (n < 0) error("ERROR reading from socket");
     
     printf("%s",buffer);
     //Variables para recibir el string del cliente
     cmd=strtok(buffer, " ");
     atb1= strtok(NULL, " ");
     atb2= strtok(NULL, " ");
     
     if(strcmp(cmd,"pwd")==0)
         caso=1;
     else if(strcmp(cmd,"ls")==0)
         caso=2;
     else if(strcmp(cmd,"cd")==0)
         caso=3;
     else if(strcmp(cmd,"mkdir")==0)
         caso=4;
     else if(strcmp(cmd,"rmdir")==0)
         caso=5;
     else if(strcmp(cmd,"vi")==0)
         caso=6;
     else if(strcmp(cmd,"cat")==0)
         caso=7;
     else if(strcmp(cmd,"cp")==0)
         caso=8;
     else if(strcmp(cmd,"mv")==0)
         caso=9;
     else if(strcmp(cmd,"rm")==0)
         caso=10;
     else if(strcmp(cmd,"exit")==0){
         n = write(newsockfd,"exit",18);
         //enviar mensaje de que se acabo
         
     }
     
     switch(caso){
         
    case 1:
    cic++; 
         n = write(newsockfd,"Entro al caso 1",18);
    pthread_create(&tid[cic],NULL, &mostrardir,NULL);
    
         
     }
    
    for(i=0;i<cic;i++)
    pthread_join(tid[i],NULL);
     
     
     
     

     close(newsockfd);
     //close(sockfd);
 }
     return 0; 
}


