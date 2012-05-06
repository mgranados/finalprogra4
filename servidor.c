#include "funciones.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>


	/* ---------------------
			Main
	------------------------*/
	
	int main (){
		
		printf("MostrarCDir");
		mostrarCdir();
		
		printf("editar");
		editar ("hola.txt");
		
		printf("mostrar");
		mostrar("hola.txt");
		
		printf("copiar");
		copiar("hola.txt","holacopia.txt");
		
		printf("mover");
		mover("hola.txt", "paleta");
		
		printf("mostrardir");
		mostrardir();
		
		
		
		
		
		
	}