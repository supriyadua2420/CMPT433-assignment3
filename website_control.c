#include "website_control.h"
#include "joystick.h"
#include "beats.h"


int sockfd;
char buffer[MAXLINE];
char *hello = "Hello from server";
struct sockaddr_in servaddr, cliaddr;

pthread_t network_thread;

wavedata_t sound;


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
	
	if(strcmp(buffer, "HiHat") == 0){	
		AudioMixer_readWaveFileIntoMemory(HI_HAT, &sound);
		AudioMixer_queueSound(&sound);
		sleep(1);
	}
	if(strcmp(buffer, "Snare") == 0){
		AudioMixer_readWaveFileIntoMemory(SNARE, &sound);
		AudioMixer_queueSound(&sound);
		sleep(1);
	}
	if(strcmp(buffer, "Base") == 0){
		printf("this is the base sound \n");
		AudioMixer_readWaveFileIntoMemory(BASE_DRUM, &sound);
		AudioMixer_queueSound(&sound);
		sleep(1);
	}
	if(strcmp(buffer, "volumeUp")==0){
		printf("volume up\n");
		increase_volume();
	}
	if(strcmp(buffer, "volumeDown")==0){
		printf("volume down\n");
		decrease_volume();
	}
	if(strcmp(buffer, "tempoUp")==0){
		printf("tempo up\n");
		increase_tempo();
	}
	if(strcmp(buffer, "tempoDown")==0){
		printf("tempo down\n");
		decrease_tempo();
	}
	if(strcmp(buffer, "None")){
		printf("thi is none mode\n");
		setBeat(0);
	}
	if(strcmp(buffer, "Rock #1\n")){
		printf("this is Rock 1 mode\n ");
		setBeat(1);
	}
	if(strcmp(buffer, "Rock #2\n")){
		printf("this is Rock #2 mode\n");
		setBeat(2);

	}
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


