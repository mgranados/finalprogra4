#include <stdio.h>           
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <stdlib.h> 
#include <string.h> 
 
#define PORT 36557 /* El puerto que ser· abierto */ 
#define BACKLOG 2 /* El n˙mero de conexiones permitidas */ 
 
main() 
{ 
 
   int fd, fd2, numbytes; /* los ficheros descriptores */ 
 
char buf[100]; 
   struct sockaddr_in server;  
   /* para la informaciÛn de la direcciÛn del servidor */ 
 
   struct sockaddr_in client;  
   /* para la informaciÛn de la direcciÛn del cliente */ 
 
   int sin_size; 
 
   /* A continuaciÛn la llamada a socket() */ 
   if ((fd=socket(AF_INET, SOCK_STREAM, 0)) == -1 ) {   
      printf("error en socket()\n"); 
      exit(-1); 
   } 
 
   server.sin_family = AF_INET;          
 
   server.sin_port = htons(PORT);  
   /* Nodo a variable corta de Red */ 
 
   server.sin_addr.s_addr = INADDR_ANY;  
   /* INADDR_ANY coloca nuestra direcciÛn IP autom·ticamente */ 
 
   bzero(&(server.sin_zero),8);  
   /* escribimos ceros en el reto de la estructura */ 
 
 
   /* A continuaciÛn la llamada a bind() */ 
   if(bind(fd,(struct sockaddr*)&server, 
           sizeof(struct sockaddr))==-1) { 
      printf("error en bind() \n"); 
     perror("El error es: "); 
         exit(-1); 
   }      
 
   if(listen(fd,BACKLOG) == -1) {  /* llamada a listen() */ 
      printf("error en listen()\n"); 
      exit(-1); 
   } 
 
   while(1) { 
      sin_size=sizeof(struct sockaddr_in); 
      /* A continuaciÛn la llamada a accept() */ 
      if ((fd2 = accept(fd,(struct sockaddr *)&client, 
                        &sin_size))==-1) { 
         printf("error en accept()\n"); 
         exit(-1); 
      } 
 
      printf("Se obtuvo una conexiÛn desde %s\n", 
             inet_ntoa(client.sin_addr) );  
      /* que mostrar· la IP del cliente */ 
 
      send(fd2,"Bienvenido a mi servidor.\n",26,0);  
      /* que enviar· el mensaje de bienvenida al cliente */ 
 
 if ((numbytes=recv(fd2,buf,100,0)) == -1){    
      /* llamada a recv() */  
      printf("Error en recv() \n");  
      exit(-1);  
   }  
 
   printf("Mensaje del cliente: %s\n",buf);  
 
      close(fd2); /* cierra fd2 */ 
   } 
} 
 
