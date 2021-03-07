#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<stdlib.h>
#define MYPORT 9899
#define BACKLOG 10
#define buffersize 1024


int main(){

		struct sockaddr_in my_addr;
		struct sockaddr_in their_addr;
		FILE *requestFile;		
		
		my_addr.sin_family = AF_INET;
		my_addr.sin_port = htons(MYPORT);
		my_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
		memset(my_addr.sin_zero, '\0', sizeof my_addr.sin_zero);

		int s = socket(AF_INET, SOCK_STREAM, 0);
		int d = bind(s, (struct sockaddr *)&my_addr, sizeof my_addr);
		if(s==-1){
		 printf("Error in socket creation\n");
		}
		else{
		 printf("Socket Created \n");}
		if(d==-1){ printf("ERROR IN BINDING \n");}
		else{
		 printf("Binding ...\n");}

		int l = listen(s,BACKLOG);

		if(l==-1){ printf("Error in listening \n"); }
		else{
		 printf("Listening ...\n");}
		//accepting client's request
		
		socklen_t taille = sizeof their_addr;
	
		
		int new_sock = accept(s,(struct sockaddr *)&their_addr, &taille);
		
		if(new_sock==-1){
		  printf("UnSuccess\n"); }
		printf("hello after creating the new sock \n ");

		//sending
		
		//int send=send(s, const void *msg, int len, int flags);
		
		char *buffer = (char*)malloc(sizeof(char)*buffersize);
       		recv(new_sock, buffer, buffersize, 0);

		printf("Server received the file :%s\n ", buffer);
		
		requestFile =fopen(buffer,"r");

		char line [ 128 ];		
		if(requestFile == NULL){
			printf("FIle NOT fOUND \n");	
			
			char *msg=(char*)malloc(sizeof(char)*buffersize);
			strcpy(msg, "File not found");
			int sendLen = send(new_sock,msg,buffersize,0);
			if(sendLen!=-1){
				printf("Sending Correct ... \n"); } 
		} 
		else{     
			 while (fgets(line, sizeof line,requestFile ) != NULL )  
      				{	
					printf("Line read : %s \n ",line);
        				int sendLen = send(new_sock,line,sizeof line,0); 
					if(sendLen!=-1){
						printf("The line Correctly sent ... \n");					
					}
												
      				}
			 printf("Im Here \n");			
			char *particularmsg=(char*)malloc(sizeof(char)*buffersize);
			strcpy(particularmsg,"Done");		
			send(new_sock,particularmsg,buffersize,0);    			
			


		} 
		
		
	       return 0;
}
