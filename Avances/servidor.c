/*--------------
	Cabeceras
----------------*/
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
#include "funciones.h"

/*---------------------
	Variables Globales
----------------------*/

char buffer[512]; //Buffer para almacenar mensajes del cliente
char *dir;


/*--------------
	  Main
----------------*/

int main (int argc, char *argv[])
{
	// Variables para la conexion
	int sockfd, newsockfd, portno, n;
	socklen_t clilen;
	
	struct sockaddr_in serv_addr, cli_addr;
	
	// Variables para tokenizar
	char *cmd, *atb1, *atb2, *cadena;
	
	int caso;
	int cic=0;
	
	//Variables para los Threads
	pthread_t tid[5000]; // Cantidad de threads y request permitidos
	
	//Conexion
	 sockfd = socket(AF_INET, SOCK_STREAM, 0);
 	 bzero((char *) &serv_addr, sizeof(serv_addr));
 	 portno = atoi(argv[1]);
 	 serv_addr.sin_family = AF_INET;
 	 serv_addr.sin_addr.s_addr = INADDR_ANY;
 	 serv_addr.sin_port = htons(portno);
 	 bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
  	 listen(sockfd,5);
  	 
  	 while(1) //LOOP para que el servidor siempre este recibiendo mensajes
  	 {
	  	 caso=0;
  	 //Se recibe el mensaje
	clilen = sizeof(cli_addr);
	newsockfd = accept(sockfd,(struct sockaddr *) &cli_addr, &clilen);
	bzero(buffer,256);// Se limpia el buffer
	 n = recv(newsockfd,buffer,255,0); //Recibe el mensaje del cliente
	  
	 //Se tokeniza los comandos
	 cadena=strtok(buffer, "\n");
	 cmd=strtok(cadena," ");
	 atb1=strtok(NULL, " ");
	 atb2=strtok(NULL, " ");
	 
	 printf("\n cmd=|%s|",cmd);
	 printf("\n atb1=|%s|",atb1);
	 printf("\n atb2=|%s|",atb2);


		
	if(strcmp(cmd,"pwd")==0)
	{
	cic++;
	cadena = mostrardir(buffer);
	n = write(newsockfd,cadena,100);
	}
	else if(strcmp(cmd,"ls")==0)
	{
	
	}
	else if(strcmp(cmd,"cd")==0)
	{
	}
	else if(strcmp(cmd,"mkdir")==0)
	{
	}
	else if(strcmp(cmd,"rmdir")==0)
	{
	}
	else if(strcmp(cmd,"vi")==0)
	{
	}
	else if(strcmp(cmd,"cat")==0)
	{
	}
	else if(strcmp(cmd,"cp")==0)
	{
	}
	else if(strcmp(cmd,"mv")==0)
	{
	}
	else if(strcmp(cmd,"rm")==0)
	{
	}
	else if(strcmp(cmd,"exit")==0)
	{
	}
	else
	printf("\n No es un comando valido\n");



	printf("\n \n");
	close(newsockfd);
	 }

}




