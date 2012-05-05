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



/* MAIN */
int main()
{

/* VARIABLES */

char cadena[100], *comando, *atributo, *atributo2, buffer[512]; 
char * usuario;
char * password;
int pase=0;
int caso;


	int fd, numbytes;
	/* descriptores de ficheros */
	
	char buf[MAXDATASIZE];
	/*buffer del texto */
	
	struct hostent *ho;
	/*Estructura que recibe informacion del nodo remoto */
	
	struct sockaddr_in server;
	/* info sobre dirección del servidor */
	

		
	/* INICIO DE SESION */

while(sesioniniciada==0){
	fflush(stdin);
	printf("Bienvenido al Administrador de Archivos Remoto \n");
//PIDE USUARIO
	printf("\n Nombre: ");  
	       fflush(stdin);
	scanf("%s",usuario);
	fflush(stdin);		 
// PIDE PASSWORD
	printf("Contraseña: ");	
	scanf("%s",password);
	fflush(stdin);
		}
/** COMPROBAR EL USUARIO Y PASSWORD **/
int i;
for(i=0; i<=5; i++)	{
//printf("\n user: %s pass: %s %d \n", usuario, pass, i);
		
if((strcmp(users[i],usuario)==0) && (strcmp(passwords[i],pass)==0))
		{
		//SESION INICIADA
		sesioniniciada=1;
		printf("\n");
		}
			}
}

/** PEDIR LAS ORDENES **/
 while(salida == 1){
	printf("%s>>", usuario);
	scanf(" %[^\n]s", comando);
	// SALIDA
	
		//salida=1;
	//tokenizar  
	funcion = strtok(comando," ");
	param = strtok(NULL," ");
	param1= strtok(NULL," ");

	
	//Loop infinito pidiendo comandos
	


//imprimirlo para checarlo
	//cada Enter lo manda al server
	
	
	//enviar mensaje constantemente

	
}

