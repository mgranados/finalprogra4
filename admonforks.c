/**
@author: Abraham Gonzalez et all
@Manejador de archivos en unix

i want to kill everybody

**/




#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
int num;

int main()
{
	/*Se declaran las variables y métodos*/
	char *users[3], *passwords[3]; 					//Guardan usuarios y contraseñas por defecto
	char usuario[20], contra[20]; 					//Reciben el usuario y contraseña
	char cadena[100], *comando, *atributo, *atributo2, buffer[512]; //Reciben los comandos y atributos
	int pase=0;
	int caso;
	int pid;
	void mostrardir();
	void editar(char *argumnto);
	void mostrar(char *argumento);
	void copiar(char *argumento1, char *argumento2);
	void mover(char *argumento1, char *argumento2);
	
	
	/*Se asignan los usuarios y contraseñas*/
	users[0]="edoardo";
	users[1]="abraham";
	users[2]="carmen";

	passwords[0]="psw1";
	passwords[1]="psw2";
	passwords[2]="psw3";
	
	/*Anuncio de bienvenida*/
	printf("\nBienvenido al Administrador de Archivos 'Server'\n");

	/*Ciclo encargado de verificar los usuarios y contraseñas introducidos con los guardos por defecto*/
	do
	{
		printf("Nombre: ");
		scanf(" %[^\n]s", usuario);
		printf("Contraseña: ");
		scanf(" %[^\n]s", contra);

		if((strcmp(users[0],usuario)==0 && strcmp(passwords[0],contra)==0)
		|| (strcmp(users[1],usuario)==0 && strcmp(passwords[1],contra)==0)
		|| (strcmp(users[2],usuario)==0 && strcmp(passwords[2],contra)==0))
			pase=1;	
		else	
			printf("Contraseña incorrecta, intentelo nuevamente\n");
	}while(pase!=1);
	
	/*Ciclo del administrador, espera por la entrada de comandos y los asigna su ejecución correspondiente*/
    printf("%s@server:~$",usuario);
	do
	{
        if(num==0){
		scanf(" %[^\n]s", cadena);

		/*Separación de la cadena en el comando y sus argumentos, en caso de tenerlos*/
		comando=strtok(cadena, " ");
		atributo=strtok(NULL, " ");
		atributo2=strtok(NULL, " ");	

		/*Asignación del caso que se debe seguir según el comando introducido*/
		if(strcmp(comando,"pwd")==0)
			caso=1;
		else if(strcmp(comando,"ls")==0)
			caso=2;
		else if(strcmp(comando,"cd")==0)
			caso=3;
		else if(strcmp(comando,"mkdir")==0)
			caso=4;
		else if(strcmp(comando,"rmdir")==0)
			caso=5;
		else if(strcmp(comando,"vi")==0)
			caso=6;
		else if(strcmp(comando,"cat")==0)
			caso=7;
		else if(strcmp(comando,"cp")==0)
			caso=8;
		else if(strcmp(comando,"mv")==0)
			caso=9;
		else if(strcmp(comando,"rm")==0)
			caso=10;
		else if(strcmp(comando,"exit")!=0){
			printf("Comando incorrecto, intente de nuevo\n");
            printf("%s@server:~$",usuario);
        }
        }
		/*Ejecución de los métodos o comandos correspondientes según el caso*/
        /* Cada caso crea su propio proceso para ejecutar el metodo y despues se regresa el control al usuario mediante exit(1);*/
       		switch(caso)
		{
               
			case 1:
                
                pid=fork();
                if(pid==0 ){                
				printf("%s \n",getcwd(buffer,-1));
                    printf("%s@server:~$",usuario);
                    exit(1);
                }
                
               break;

			case 2:
                pid=fork();
                if(pid==0 ){
				mostrardir();
                    printf("%s@server:~$",usuario);
                    exit(1);
                }
				break;

			case 3:
                pid=fork();
                if(pid==0 ){
				chdir(atributo);
                    printf("%s@server:~$",usuario);
                    exit(1);
                }
                chdir(atributo);
				break;

			case 4:
                    pid=fork();
                    if(pid==0 ){
				mkdir(atributo,0755);
				printf("Se creo el directorio %s \n", atributo);
                        printf("%s@server:~$",usuario);
                        exit(1);
                    }
                
				break;

			case 5:	
                        pid=fork();
                        if(pid==0 ){
				rmdir(atributo);
				printf("Se elimino el directorio %s \n", atributo);
                            printf("%s@server:~$",usuario);
                            exit(1);
                        }

				break;

			case 6:
                editar(atributo);                             
                            
                printf("%s@server:~$",usuario);
				break;
			
			case 7: 
                                pid=fork();
                                if(pid==0 ){
				mostrar(atributo);
                                    printf("%s@server:~$",usuario);
                                    exit(1);
                                }
				break;
			
			case 8:
                                    pid=fork();
                                    if(pid==0 ){
				copiar(atributo, atributo2);
                                        printf("%s@server:~$",usuario);
                                        exit(1);
                                    }
				break;

			case 9:
                                        pid=fork();
                                        if(pid==0 ){
				mover(atributo, atributo2);
                                            printf("%s@server:~$",usuario);
                                            exit(1);
                                        }
				break;
			
			case 10: 
                                            pid=fork();
                                            if(pid==0 ){
				remove(atributo);
				printf("Se elimino el archivo %s \n", atributo);
                                                printf("%s@server:~$",usuario);
                                                exit(1);
                                            }
                printf("%s@server:~$",usuario);
				break;
                    
		}
				caso=0;
	}while(strcmp(comando,"exit")!=0);		//Sale del ciclo y termina la ejecución con el comando "exit"

	return 0;
}

/*Asignación de los métodos*/
void mostrardir()
{
	DIR *dir;
	struct dirent *mi_dir;
	char buff[512];
	
	dir=opendir(getcwd(buff,-1));
	while((mi_dir=readdir(dir))!=NULL)
		printf("%s \n", mi_dir->d_name);
	closedir(dir);
    
}

void editar(char *argumento)
{
	FILE *archivo;
	char cadena[500];
	
	archivo=fopen(argumento, "w");		//Abre o crea el archivo solicitado
	printf("Contenido $\n");
	scanf(" %[^\n]s", cadena);
	fprintf(archivo, "%s", cadena);
	fclose(archivo);
}

void mostrar(char *argumento)
{
	FILE *archivo;
	char caracter;

	archivo=fopen(argumento, "r");
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

void copiar(char *argumento1, char *argumento2)
{
	FILE *archivo1, *archivo2;
	char caracter;
	
	archivo1=fopen(argumento1, "r");
	archivo2=fopen(argumento2, "w");	//Crea el archivo en caso de que no exista
	
	if(archivo1==NULL)
		printf("El archivo %s no exite", argumento1);
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

void mover(char *argumento1, char *argumento2)
{
	FILE *archivo1, *archivo2;
	char caracter;

	archivo1=fopen(argumento1, "r");
	
	chdir(argumento2);
	archivo2=fopen(argumento1, "w");
	
	if(archivo1==NULL)
		printf("El archivo %s no exite", argumento1);
	else
	{
		while(feof(archivo1)==0)
		{
			caracter=fgetc(archivo1);
			fputc(caracter,archivo2);
		}
		fclose(archivo2);
		chdir("../");
		remove(argumento1);
		printf("Se ha movido el archivo\n");	
	}
	fclose(archivo1);
}

/*---Comandos a utilizarce en la consola---*/
/*
 *	pwd
 *      ls
 *	cd [Directorio]
 *	mkdir [Nombre de Directorio]
 *	rmdir [Nombre de Directorio]
 *	vi [Nombre de Archivo]
 *  	cat [Nombre de Archivo]
 *	cp [Nombre de Archivo 1] [Nombre de Archivo 2]
 *	mv [Nombre de Archivo] [Nombre de Directorio]
 *	rm [Nombre de Archivo]
 */