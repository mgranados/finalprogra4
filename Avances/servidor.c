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

char buffer[512];
char buffer1[512]; //Buffer para almacenar mensajes del cliente
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
	
	int pid;
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
  	 //Se recibe el mensaje
	clilen = sizeof(cli_addr);
	newsockfd = accept(sockfd,(struct sockaddr *) &cli_addr, &clilen);
	pid=fork();
	if(pid==0){
		
		printf(" \n nuevo ID %d", pid);
	
	printf("%d accept", newsockfd);
	bzero(buffer,512);// Se limpia el buffer
	 n = recv(newsockfd,buffer,5º1,0); //Recibe el mensaje del cliente
	  
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
	cadena = mostrardir(buffer);
	n = write(newsockfd,cadena,100);
	}
	else if(strcmp(cmd,"ls")==0)
	{
	cadena = mostrarCdir();
	n = write(newsockfd,cadena,300);
	bzero(cadena,500);
	}
	else if(strcmp(cmd,"cd")==0)
	{
	chdir(atb1);
	cadena = mostrardir(buffer);
	n = write(newsockfd,cadena,100);
	}
	else if(strcmp(cmd,"mkdir")==0)
	{
		mkdir(atb1,0755);
		cadena = "Se creo tu directorio ";
		memcpy(buffer1,cadena, strlen(cadena));
		strcat(buffer1,atb1);
		n = write(newsockfd,buffer1,100);
	}
	else if(strcmp(cmd,"rmdir")==0)
	{
		rmdir(atb1);
		cadena = "Se borro el directorio: ";
	memcpy(buffer1,cadena, strlen(cadena));
			strcat(buffer1,atb1);
		n = write(newsockfd,buffer1,100);
	}
	else if(strcmp(cmd,"vi")==0)
	{
		crear(atb1);
		cadena = "Escriba su contenido: \n";
		n = write(newsockfd,cadena,100);
		
		n = recv(newsockfd,buffer1,255,0);
		editar(atb1,buffer1);

	}
	else if(strcmp(cmd,"cat")==0)
	{
		if((cadena=mostrar(atb1))==NULL)
		cadena = "No existe el archivo";
		
		memcpy(buffer1,cadena, strlen(cadena));
		strcat(buffer1,"");
		n = write(newsockfd,buffer1,512);

	}
	else if(strcmp(cmd,"cp")==0)
	{
		copiar(atb1, atb2);
		
		cadena="Se ha copiado el archivo.";
		n = write(newsockfd,cadena,502);
	}
	else if(strcmp(cmd,"mv")==0)
	{
		mover(atb1, atb2);
		cadena="Se ha movido el archivo.";
		n = write(newsockfd,cadena,502);
	}
	else if(strcmp(cmd,"rm")==0)
	{
		remove(atb1);
		cadena="Se ha borrado el archivo.";
		n = write(newsockfd,cadena,502);

	}
	else if(strcmp(cmd,"exit")==0)
	{
		cadena="Bye bye.";
		n = write(newsockfd,cadena,502);

		close(newsockfd);
	}
	else{
		cadena = "No es un comando valido";
		n = write(newsockfd,cadena,100);
	}



	printf("\n \n");
	close(newsockfd);
exit(0);
	}
		
		}
	 }






