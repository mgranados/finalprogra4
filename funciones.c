

/* Librerias */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


/* ---------------------------
	Funciones Prototipo 
------------------------------*/

//Funcion que muestra el contenido de los directorios
	void mostrarCdir();
//Funcion para crear, editar archivos
	void editar ();
//Funcion que muestra el contenido de un archivo
	void mostrar();
//Funcion que copia un archivo
	void copiar();
//Funcion que mueve un archivo de lugar
	void mover ();
//Funcion que imprime el directorio actual
	void mostrardir ();	
	
/* ---------------------
		Funciones
------------------------*/

void mostrarCdir()
{
	DIR *dir;
	struct dirent *mi_dir;
	char buff[512];

	if((dir=opendir(getcwd(buff,-1)))==-1){
		perror("Error en mostrardir, al abrir un directorio");
		exit(1);
		}
		
	while((mi_dir=readdir(dir))!=NULL)
		printf("%s \n", mi_dir->d_name);
	
	closedir(dir);
}



void editar(char *arg)
{
	FILE *archivo;
	char cadena[500];
	
	archivo=fopen(arg, "w");	printf("Contenido $\n");
	scanf(" %[^\n]s", cadena);
	fprintf(archivo, "%s", cadena);
	
	fclose(archivo);
}

void mostrar(char *arg)
{
	FILE *archivo;
	char caracter;

	archivo=fopen(arg, "r");
	if(archivo==NULL)
		printf("El archivo no existe \n");
	else
	{
		printf("\n");
		while(feof(archivo)==0)
		{
			caracter=fgetc(archivo);
			printf("%c",caracter);
		}
		printf("\n\n");
	}
	fclose(archivo);	
}


void copiar(char *arg1, char *arg2)
{
	FILE *archivo1, *archivo2;
	char caracter;

	archivo1=fopen(arg1, "r");
	archivo2=fopen(arg2, "w");	//Crea el archivo en caso de que no exista

	if(archivo1==NULL)
		printf("El archivo %s no exite", arg1);
	else
	{
		while(feof(archivo1)==0)
		{
			caracter=getc(archivo1);
			putc(caracter,archivo2);
		}
		printf("Se ha copiado el archivo\n");
	}	
	fclose(archivo1);
	fclose(archivo2);	
}


void mover(char *arg1, char *arg2)
{
	FILE *archivo1, *archivo2;
	char caracter;

	archivo1=fopen(arg1, "r");

	chdir(arg2);
	archivo2=fopen(arg1, "w");

	if(archivo1==NULL)
		printf("El archivo %s no exite", arg1);
	else
	{
		while(feof(archivo1)==0)
		{
			caracter=fgetc(archivo1);
			fputc(caracter,archivo2);
		}
		fclose(archivo2);
		chdir("../");
		remove(arg1);
		printf("Se ha movido el archivo\n");	
	}
	fclose(archivo1);
}

void mostrardir()
{
	printf("%s \n",getcwd(buffer,-1));
}