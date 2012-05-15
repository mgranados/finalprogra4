#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

void termina(int x); 

char n[10]; 
int s; 
void acabar(int x){

printf("\n Está seguro que desea terminarlo? "); 
scanf("%[^\n]s",n); 
// printf("Presiona enter para continuar");

if(strcmp(n,"yes")==0 || strcmp(n , "YES")==0 || strcmp(n,"y")==0){
exit(0); 
}else {
signal (SIGINT, SIG_DFL);
}

// signal (SIGINT, SIG_DFL);


}

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
 
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    int conec= argc;
    char *arg1= argv[1];
    char *arg2= argv[2];
    char *us, *pas;
    
    
    char buffer[256];
    char usuario[100];
    char password[100];
  
    int contador=0;
   
   if (conec < 3) {
      fprintf(stderr,"usage %s hostname port\n", argv[0]);
      exit(0);
   }
   system("clear");
   printf("\n Bienvenido al servidor \n");
   
   while(contador==0)
   {
       printf("\n Usuario: ");
  fgets(usuario,255,stdin);
  us=strtok(usuario, "\n");
      printf("\n Contraseña: ");
    fgets(password,255,stdin);
    pas=strtok(password, "\n");

     if(strcmp(us,"abraham")==0 && strcmp(pas,"1")==0)
     contador++;
     else if(strcmp(us,"martin")==0 && strcmp(pas,"2")==0)
     contador++;
     else if(strcmp(us,"sandy")==0 && strcmp(pas,"3")==0)
     contador++;
     else
     printf("\n Usuario o contraseña Incorrecta Por favor intente de nuevo");

   }
   

    while(1){
        
        if (signal (SIGINT, acabar) == SIG_ERR)
        {
        perror ("No se puede cambiar signal");
        }

        portno = atoi(arg2);
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd < 0) 
            error("ERROR opening socket");
        server = gethostbyname(arg1);
        if (server == NULL) {
            fprintf(stderr,"ERROR, no such host\n");
            exit(0);
        }
        bzero((char *) &serv_addr, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        bcopy((char *)server->h_addr, 
             (char *)&serv_addr.sin_addr.s_addr,
             server->h_length);
        serv_addr.sin_port = htons(portno);
        if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");
    printf("%s@server: ", usuario);
  bzero(buffer,256);

  fgets(buffer,255,stdin);
    n = write(sockfd,buffer,strlen(buffer));
    if (n < 0) 
         error("ERROR writing to socket");
        bzero(buffer,256);

    n = read(sockfd,buffer,255);
    if (n < 0) 
         error("ERROR reading from socket");
    printf("%s\n",buffer);
    
    if((strcmp(buffer,"Escriba su contenido: \n"))==0)
    {
        bzero(buffer,256);
        fgets(buffer,255,stdin);
        n = write(sockfd,buffer,strlen(buffer));
    }
    
    close(sockfd);
}
return 0;
   
}
