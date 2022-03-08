// Server side implementation of UDP client-server model
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>
#include "audioMixer_template.h" 

#define PORT	 12345
#define MAXLINE 1024

int sockfd;
char buffer[MAXLINE];
char *hello = "Hello from server";
struct sockaddr_in servaddr, cliaddr;

pthread_t network_thread;

void checkResponse(char* response){
	//int answer = 0;
	if(strcmp(response, "None\n")){
		printf("Yay this matched ! \n");
	}
	
}

void create_socket(){

	// Creating socket file descriptor
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}
	
	memset(&servaddr, 0, sizeof(servaddr));
	memset(&cliaddr, 0, sizeof(cliaddr));
	
	// Filling server information
	servaddr.sin_family = AF_INET; // IPv4
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servaddr.sin_port = htons(PORT);
	
	// Bind the socket with the server address
	if ( bind(sockfd, (const struct sockaddr *)&servaddr,
			sizeof(servaddr)) < 0 )
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
	

}

void* routine(){

	create_socket();
	int n;
	unsigned int len;
	
	while(1){

	len = sizeof(cliaddr); //len is value/resuslt

	n = recvfrom(sockfd, (char *)buffer, MAXLINE,
				MSG_WAITALL, ( struct sockaddr *) &cliaddr,
				&len);
				
	buffer[n] = '\0';
	printf("Client : %s\n", buffer);
	sendto(sockfd, (const char *)hello, strlen(hello),
		MSG_CONFIRM, (const struct sockaddr *) &cliaddr,
			len);
			
	checkResponse(buffer);
	printf("Hello message sent.\n");
	}

	return NULL;
}

void web_init(){
	pthread_create(&network_thread, NULL, &routine, NULL);
}

void web_cleanup(){
	pthread_join(network_thread, NULL);
}

// Driver code
int main() {

	web_init();
	web_cleanup();
	
	return 0;
}

