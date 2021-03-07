/* Usage : streamserveur /usr/local/mysock */ 
#include <sys/types.h> 
#include <sys/socket.h> 
#include<string.h>
#include <sys/un.h> //struct sockaddr_un

//• Côté Serveur (en attente de connexion)
//le socket est dit passif

int main(int argc, char *argv[]){
	
	int sd, ns, nb; 
	char buf[25]; 
	int len;
	struct sockaddr_un serveraddr, clientaddr; 
	int clientaddrlen;
	
	//• crée un socket socket()
	sd = socket(AF_UNIX, SOCK_STREAM,0);
	
	serveraddr.sun_family=AF_UNIX;
	strcpy(argv[1], serveraddr.sun_path);
	
	//• associe une adresse au socket bind
	bind(sd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
	
	//Do• se met à l ’écoute des connexions entranteslisten
	listen(sd,1);
	
	//• accepte une connexion entrante accept()
	ns=accept(sd,(struct sockaddr *)&clientaddr, &clientaddrlen);
	
	//• lit et écrit sur le socket read(),recv();write(),send
	nb=read(ns, &len, sizeof(len)); /* les erreurs ne sont pas traitées */
	nb=read(ns, buf, len); 
	write(1,buf,nb);
	
	//• ferme le socket close()
	close(ns); 
	close(sd);

	return 0;
}

