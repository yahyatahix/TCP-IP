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
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#define MYPORT 9899
#define BACKLOG 10
#define buffersize 1024

int main(){
	
	struct sockaddr_in serv_addr;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(MYPORT);
	serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	memset(serv_addr.sin_zero, '\0', sizeof serv_addr.sin_zero);
	int s = socket(AF_INET, SOCK_STREAM, 0);
	if(s==-1){
		 printf("Error in socket creation\n");
		}
	else{
		 printf("Socket Created \n");}
	
	int conn =connect(s, (struct sockaddr *)&serv_addr, sizeof serv_addr);
	
	if(conn==-1){
			printf("connection failed");	
		}
		else{printf("connection succeded to the server \n");}
	char *filename = (char*)malloc(sizeof(char)*buffersize);
	printf("Enter the name of file :\n");
	gets(filename);	
	int byte_len=send(s,filename,buffersize,0);
	if(byte_len==-1){
		printf("SENDING FAILED ... \n");	
	}
	else{
	 	printf("File name sent ... \n");
	}
		
	//char *error = (char*)mall;oc(buffersize*sizeof(char));
	//recv(s, error, buffersize, 0);
	
	//printf("hello i failed here%s \n",error);
	
	FILE *answerFile=fopen(filename,"w"); 
	
	while(1){
		
		//printf("the content of the file : \n");
		char *line = (char*)malloc(sizeof(char)*buffersize);
       		recv(s, line, buffersize,0);	
		if(strcmp(line , "Done")==0){
			break; 		
		}			
		
		fputs(line,answerFile);
		//printf("%s \n",line);
	}
	printf("I m here \n"); 
	fclose(answerFile);

	return 0 ; 
}
