#include "website_control.h"


int sockfd;
char buffer[MAXLINE];
char *hello = "Hello from server";
struct sockaddr_in servaddr, cliaddr;

pthread_t network_thread;

wavedata_t sound;

void checkResponse(char* response){
	
	if(strcmp(response, "None\n")){
		//do nothing.
	}
	if(strcmp(response, "Rock #1\n")){
	
		//printf("reached here \n");
	}
	if(strcmp(response, "Rock #2\n")){
		//queue the beat when ready.
		//printf("Yay this matched ! \n");
	}
	if(strcmp(response, "HiHat\n")){
		AudioMixer_readWaveFileIntoMemory(HI_HAT, &sound);
		AudioMixer_queueSound(&sound);
		sleep(2);
	}
	if(strcmp(response, "Snare\n")){
		
		AudioMixer_readWaveFileIntoMemory(SNARE, &sound);
		AudioMixer_queueSound(&sound);
		sleep(2);
	}
	if(strcmp(response, "Base\n")){
		
		AudioMixer_readWaveFileIntoMemory(BASE_DRUM, &sound);
		AudioMixer_queueSound(&sound);
		sleep(2);
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
	//printf("Hello message sent.\n");
	}

	return NULL;
}

void web_init(){
	pthread_create(&network_thread, NULL, &routine, NULL);
}

void web_cleanup(){
	AudioMixer_freeWaveFileData(&sound);
	pthread_join(network_thread, NULL);
}


