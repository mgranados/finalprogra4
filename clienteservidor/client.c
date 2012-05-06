#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 



int main(int argc, char *argv[])
{
    /*------------------------------------- VARIABLES  ------------------------------------------------------ */
    char * users[3], *passwords[3]; 
    users[0]="martin";
    users[1]="abraham";
    users[2]="jazmin";
    
    passwords[0]="1";
    passwords[1]="2";
    passwords[2]="3";
    char cadena[100], *comando, *atributo, *atributo2; 
    
    char usuario[100];
    char password[100];
    
    int sesioniniciada=0;
    int salida =0 ;
    int fd, numbytes;
    
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    
    struct hostent *server;

   while(1){
    char buffer[256];
    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
  
            server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no se encuentra el host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0);
        
        
 
        
        
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
        printf("Login exitoso.\n");
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

   
    n = write(sockfd,comando,strlen(comando));
  bzero(comando,strlen(comando));
    
    bzero(buffer,256);
    
    n = read(sockfd,buffer,255);
    
    printf("%s\n",buffer);

    close(n);
}}
close(sockfd);
return 0;
}
