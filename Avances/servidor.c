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

#define max 256

/*---------------------
	Variables Globales
----------------------*/

char buffer[512];
char buffer1[512]; //Buffer para almacenar mensajes del cliente
char *dir;
char * cwd;



/*--------------
	  Main
----------------*/

int main (int argc, char *argv[])
{
	// Variables para la conexion
	int sockfd, newsockfd, portno, n;
	socklen_t clilen, nbytes;
	
	struct sockaddr_in serv_addr, cli_addr;
	
	// Variables para tokenizar
	char *cmd, *atb1, *atb2, *cadena;
	
	int pid;
	cwd=getcwd(buffer,-1);
		
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
		
		int fd[2];
		
		
		//Threads para sincronizar los procesos
		pthread_mutex_t mutexC;
		pthread_cond_t lugarC;
		
		/*Inicializacion de mutex*/
		pthread_mutex_init (&mutexC, NULL);
		
		/*Inicializacion de la variable condicional*/
		pthread_cond_init (&lugarC,NULL);
	
		pipe(fd);
		
		pid=fork();
	//-------------FORK -------------------
	if(pid==0){
	//printf("\n%d accept", newsockfd);
		printf(" \n ID %d", pid);
		printf("\n Conexion de %d", inet_ntoa(cli_addr.sin_addr));

	bzero(buffer,512);// Se limpia el buffer
	 n = recv(newsockfd,buffer,512,0); //Recibe el mensaje del cliente
	  
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
	pthread_mutex_lock(&mutexC);
	cadena = mostrardir(buffer);
	n = write(newsockfd,cadena,100);
	pthread_mutex_unlock(&mutexC);
	}
	else if(strcmp(cmd,"ls")==0)
	{
	pthread_mutex_lock(&mutexC);
	cadena = mostrarCdir();
	n = write(newsockfd,cadena,300);
	bzero(cadena,500);
	pthread_mutex_unlock(&mutexC);
	}
	else if(strcmp(cmd,"cd")==0)
	{
	pthread_mutex_lock(&mutexC);
	chdir(atb1);
	cadena = mostrardir(buffer);
	n = write(newsockfd,cadena,100);
	strncpy(cwd,getcwd(buffer, -1),strlen(atb1));
	pthread_mutex_unlock(&mutexC);
	}
	else if(strcmp(cmd,"mkdir")==0)
	{
		pthread_mutex_lock(&mutexC);
		mkdir(atb1,0755);
		cadena = "Se creo tu directorio ";
		memcpy(buffer1,cadena, strlen(cadena));
		strcat(buffer1,atb1);
		n = write(newsockfd,buffer1,100);
		pthread_mutex_unlock(&mutexC);
	}
	else if(strcmp(cmd,"rmdir")==0)
	{
		pthread_mutex_lock(&mutexC);
		rmdir(atb1);
		cadena = "Se borro el directorio: ";
	memcpy(buffer1,cadena, strlen(cadena));
			strcat(buffer1,atb1);
		n = write(newsockfd,buffer1,100);
		pthread_mutex_unlock(&mutexC);
	}
	else if(strcmp(cmd,"vi")==0)
	{
		pthread_mutex_lock(&mutexC);
		crear(atb1);
		cadena = "Escriba su contenido: \n";
		n = write(newsockfd,cadena,100);
		
		n = recv(newsockfd,buffer1,255,0);
		editar(atb1,buffer1);
		pthread_mutex_unlock(&mutexC);

	}
	else if(strcmp(cmd,"cat")==0)
	{
		pthread_mutex_lock(&mutexC);
		if((cadena=mostrar(atb1))==NULL)
		cadena = "No existe el archivo";
		
		memcpy(buffer1,cadena, strlen(cadena));
		strcat(buffer1,"");
		n = write(newsockfd,buffer1,512);
		pthread_mutex_unlock(&mutexC);

	}
	else if(strcmp(cmd,"cp")==0)
	{
		pthread_mutex_lock(&mutexC);
		copiar(atb1, atb2);
		
		cadena="Se ha copiado el archivo.";
		n = write(newsockfd,cadena,502);
		pthread_mutex_unlock(&mutexC);
	}
	else if(strcmp(cmd,"mv")==0)
	{
		pthread_mutex_lock(&mutexC);
		mover(atb1, atb2);
		cadena="Se ha movido el archivo.";
		n = write(newsockfd,cadena,502);
		pthread_mutex_unlock(&mutexC);
	}
	else if(strcmp(cmd,"rm")==0)
	{
		pthread_mutex_lock(&mutexC);
		remove(atb1);
		cadena="Se ha borrado el archivo.";
		n = write(newsockfd,cadena,502);
		pthread_mutex_unlock(&mutexC);
	}
	else if(strcmp(cmd,"exit")==0)
	{
		pthread_mutex_lock(&mutexC);
		cadena="Bye bye.";
		n = write(newsockfd,cadena,502);
		pthread_mutex_unlock(&mutexC);
		close(newsockfd);
		exit(1);
	}
	else if(!cmd || strlen(cmd)==0 || cmd==NULL || cmd=="" || cmd=='\0')
	{
		cadena = "No es un comando valido";
		n = write(newsockfd,cadena,100);
	}
	else{
		cadena = "No es un comando valido";
		n = write(newsockfd,cadena,100);
	}


	/*Pipe que envia el current working directory para que se cambie el directorio despues de que muere el proceso hijo */
	
	write(fd[1], cwd, max);
	close(fd[0]);
	close(fd[1]);

	printf("\n \n");

	}
	else{ 
	
			nbytes = read(fd[0], cwd, max);
			close(fd[0]);
			close(fd[1]);
	
	chdir(cwd);
	}
		}
	 }






