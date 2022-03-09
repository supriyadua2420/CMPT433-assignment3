#include "website_control.h"


int sockfd;
char buffer[MAXLINE];
char *hello = "Hello from server";
struct sockaddr_in servaddr, cliaddr;

pthread_t network_thread;

wavedata_t sound;

void play_sound(char* sound_name){
	AudioMixer_readWaveFileIntoMemory(sound_name, &sound);
	AudioMixer_queueSound(&sound);
	sleep(1);
}

void checkResponse(char* response){
	
	if(strcmp(response, "None\n")){
		//do nothing.
	}
	if(strcmp(response, "Rock #1\n")){
		//play beat 1;
	}
	if(strcmp(response, "Rock #2\n")){
		//play beat 2;
	}
	if(strcmp(response, "HiHat\n")){
		play_sound(HI_HAT);	
	}
	if(strcmp(response, "Snare\n")){
		play_sound(SNARE);
	}
	if(strcmp(response, "Base\n")){
		play_sound(BASE_DRUM);
	}
	/*if(strcmp(response, "volumeup\n")){
		//raise volume
		printf("volume up\n");
	}*/
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


