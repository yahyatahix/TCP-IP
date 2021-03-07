/* Usage : streamclient /usr/local/mysock "Hello World !" */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h> //struct sockaddr_un
//#include <netinet/in.h>
//• Côté Client (demandeur de la connexion): 
//le socket est dit actif

int main(int argc, char *argv[]) {
	int sd; 
	int len;
	struct sockaddr_un serveraddr;
	
	//• crée un socket socket()
	sd=socket(AF_INET, SOCK_STREAM,0);

	serveraddr.sun_family=AF_UNIX;
	strcpy(argv[1], serveraddr.sun_path);
	
	// se connecte à une <adresse,port> connect()
	
	if(connect(sd, (struct sockaddr *)&serveraddr, sizeof( serveraddr)) <0) 
		exit(1);
	
	len=strlen(argv[2]); 

	//• lit et écrit dans le socket read(),recv();write(),send()
	write(sd, &len, sizeof(len));
	write(sd, argv[2], len);
	
	//• ferme le socket close()
	close(sd);

	return 0;
}





