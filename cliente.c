#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/netinet.h>

#define PORT 34665
/* PUERTO */

#define MAXDATASIZE 128


/* 128 bytes a pasar máximo */


char* ip = "127.0.0.1"
/* MAIN */
int main()
{
	int fd, numbytes;
	/* descriptores de ficheros */
	
	char buf[MAXDATASIZE];
	/*buffer del texto */
	
	struct hostent *ho;
	/*Estructura que recibe informacion del nodo remoto */
	
	struct sockaddr_in server;
	/* info sobre dirección del servidor */
	
	
		
	
	
	//Loop infinito pidiendo comandos
	
	
	//imprimirlo para checarlo
	
	
	//enviarlo
	
}

