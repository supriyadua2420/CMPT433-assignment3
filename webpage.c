//Socket code source : https://www.geeksforgeeks.org/udp-server-client-implementation-c/

#include "webpage.h"
#include "joystick.h"
#include "beats.h"

unsigned int len;

int sockfd;
char buffer[MAXLINE];

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

void send_to_web(char* hello){
	sendto(sockfd, (const char *)hello, strlen(hello),
		MSG_CONFIRM, (const struct sockaddr *) &cliaddr,
			len);
}

void* routine(){

	create_socket();
	int n;
	
	
	while(1){

	len = sizeof(cliaddr); //len is value/resuslt

	n = recvfrom(sockfd, (char *)buffer, MAXLINE,
				MSG_WAITALL, ( struct sockaddr *) &cliaddr,
				&len);
				
	buffer[n] = '\0';
	printf("Instruction received : %s\n", buffer);

	if(strcmp(buffer, "HiHat") == 0){	
		AudioMixer_readWaveFileIntoMemory(HI_HAT, &sound);
		AudioMixer_queueSound(&sound);
		sleep(1);
		AudioMixer_freeWaveFileData(&sound);
	}
	else if(strcmp(buffer, "Snare") == 0){
		AudioMixer_readWaveFileIntoMemory(SNARE, &sound);
		AudioMixer_queueSound(&sound);
		sleep(1);
		AudioMixer_freeWaveFileData(&sound);
	}
	else if(strcmp(buffer, "Base") == 0){
		AudioMixer_readWaveFileIntoMemory(BASE_DRUM, &sound);
		AudioMixer_queueSound(&sound);
		sleep(1);
		AudioMixer_freeWaveFileData(&sound);
	}
	else if(strcmp(buffer, "volumeUp")==0){
		increase_volume();
		int vol = AudioMixer_getVolume();
		char hello []= "Volume up, Current volume: ";
		char volum[5];
		snprintf(volum, 4,"%d", vol); 
		strcat(hello, volum);
		send_to_web(hello);

	}
	else if(strcmp(buffer, "volumeDown")==0){
		decrease_volume();
		int vol = AudioMixer_getVolume();
		char hello []= "Volume down, Current volume: ";
		char volum[5];
		snprintf(volum, 4,"%d", vol); 
		strcat(hello, volum);
		send_to_web(hello);
	}
	else if(strcmp(buffer, "tempoUp")==0){
		increase_tempo();
		int tempo = AudioMixer_getBPM();
		char hello []= "Tempo up, Current tempo: ";
		char volum[5];
		snprintf(volum, 4,"%d", tempo); 
		strcat(hello, volum);
		send_to_web(hello);
	}
	else if(strcmp(buffer, "tempoDown")==0){
		decrease_tempo();
		int tempo = AudioMixer_getBPM();
		char hello []= "Tempo down, Current tempo: ";
		char volum[5];
		snprintf(volum, 4,"%d", tempo); 
		strcat(hello, volum);
		send_to_web(hello);
	}
	else if(strcmp(buffer, "None")==0){
		setBeat(0);
	}
	else if(strcmp(buffer, "Rock1")==0){
		setBeat(1);
	}
	else if(strcmp(buffer, "Rock2")==0){
		setBeat(2);

	}
	}

	return NULL;
}

void web_init(){
	pthread_create(&network_thread, NULL, &routine, NULL);
}

void web_cleanup(){
	pthread_join(network_thread, NULL);
}


