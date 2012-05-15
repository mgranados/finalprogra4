

/* Librerias */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "funciones.h"


/* ---------------------------
	Funciones Prototipo 
------------------------------*/

//Funcion que muestra el contenido de los directorios
	char *mostrarCdir();
//Funcion para editar archivos
	void *editar (char *arg, char *arg2);
//Funcion para crear archivos
	void *crear (char *arg);
//Funcion que muestra el contenido de un archivo
	char *mostrar(char *arg);
//Funcion que copia un archivo
	void *copiar();
//Funcion que mueve un archivo de lugar
	void *mover ();
//Funcion que imprime el directorio actual
	char *mostrardir (char *dir);	
	
/* ---------------------
		Funciones
------------------------*/

char *mostrarCdir()
{
	DIR *dir;
	struct dirent *mi_dir;
	char buff[512];
	char *buffer;
	char *cadenaD;
	char *espacio="\n";

	dir=opendir(getcwd(buff,-1));
			
	while((mi_dir=readdir(dir))!=NULL)
		{
	buffer= mi_dir->d_name;
	strcat(buffer,espacio);
	strcat(cadenaD,buffer);
		}
	closedir(dir);
	
	return cadenaD;
}

void *crear(char *arg)
{
	FILE *archivo;
	 char c;	
	archivo=fopen(arg, "w");

	fclose(archivo);	
}

void *editar(char *arg, char *arg2)
{
	FILE *archivo;
	 char c;	
	archivo=fopen(arg, "w");
	
	fputs(arg2,archivo);

	fclose(archivo);
}

char *mostrar(char *arg)
{
	FILE *archivo;
	char caracter[100];
	char *buffer;

	archivo=fopen(arg, "r");
	if(archivo==NULL){
	return NULL;}
	
		else
	{
		fgets(caracter,100,archivo);
		strncpy(buffer,caracter,strlen(caracter));
		
	}

	fclose(archivo);
	return buffer;
	
}


void *copiar(char *arg1, char *arg2)
{
	FILE *archivo1, *archivo2;
	char caracter;

	archivo1=fopen(arg1, "r");
	archivo2=fopen(arg2, "w");	//Crea el archivo en caso de que no exista


	

		while(feof(archivo1)==0)
		{
			caracter=getc(archivo1);
			putc(caracter,archivo2);
		}
		
	
	fclose(archivo1);
	fclose(archivo2);	
}


void *mover(char *arg1, char *arg2)
{
	FILE *archivo1, *archivo2;
	char caracter;

	archivo1=fopen(arg1, "r");

	chdir(arg2);
	archivo2=fopen(arg1, "w");

	
		while(feof(archivo1)==0)
		{
			caracter=fgetc(archivo1);
			fputc(caracter,archivo2);
		}
		fclose(archivo2);
		chdir("../");
		remove(arg1);
			
	fclose(archivo1);
}

char *mostrardir(char *dir)
{
	char *buffer;
	buffer = getcwd(dir,-1);
	return buffer;
}