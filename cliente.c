/*
@author: Martin Granados et al.

@Cliente.c Servidor de archivos distribuidos

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>


#define PORT 34665
/* PUERTO */

#define MAXDATASIZE 128
/* 128 bytes a pasar máximo */



/* ----------------------------------------- MAIN --------------------------------------------------------*/
int main()
{

/*------------------------------------- VARIABLES  ------------------------------------------------------ */
char * users[3], *passwords[3]; 
users[0]="martin";
users[1]="abraham";
users[2]="jazmin";

passwords[0]="1";
passwords[1]="2";
passwords[2]="3";
char cadena[100], *comando, *atributo, *atributo2, buffer[512]; 
char usuario[100];
char password[100];
int sesioniniciada=0;
int salida =0 ;
int fd, numbytes;
	/* descriptores de ficheros */
	
	/*--------------------------------- PEDIR  LOGIN ------------------------------------------------ */

while(sesioniniciada==0){
	fflush(stdin);
	system("clear");
	printf("Bienvenido al Administrador de Archivos Remoto \n");
	
//PIDE USUARIO
	printf("\n Nombre: ");         
	scanf("%s",usuario);
	printf("Contraseña: ");	
	
	scanf("%s",password);
	
		
/** COMPROBAR EL USUARIO Y PASSWORD **/
int i;
for(i=0; i<=2; i++)	{
		fflush(stdin);
if((strcmp(users[i],usuario)==0) && (strcmp(passwords[i],password)==0))
		{
		//SESION INICIADA
		sesioniniciada=1;
		printf("	EHHHHHHHHHHHHHHHHHH\n");
		break;
		}
		else 
		printf("Login incorrecto, intentelo nuevamente\n");
	}
}

/** -------------------------- while  PEDIR LAS ORDENES ---------------------**/
 
 while(salida == 0){
printf("%s@server:~$",usuario);
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


/*--------------------------------------- CERRAR  MAIN ------------------------------------------------ */
}

