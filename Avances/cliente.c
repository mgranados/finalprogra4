#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 



void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
 //datos de sesión
    char *users[5];
    char *passwords[5];
    int logout=0;
    users[0]="sandy";
    users[1]="abraham";
    users[2]="martin";
    users[3]="admin";
    users[4]="asdaf";
    
    passwords[0]="1";
    passwords[1]="2";
    passwords[2]="3";
    passwords[3]="admin";
    passwords[4]="asdf";
    
    char usuario[10];
    char pass[10];		
    		//Reciben el usuario y contraseña
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    int conec= argc;
    char *arg1= argv[1];
    char *arg2= argv[2];
    
    
    char buffer[256]="hola";
  
   
   
   if (conec < 3) {
      fprintf(stderr,"usage %s hostname port\n", argv[0]);
      exit(0);
   }
   






    while(1){
        int sesioniniciada=0;
        /*Ciclo encargado de verificar los usuarios y contraseñas introducidos con los guardos por defecto*/
       
        
        
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
