#include "joystick.h"
#include "audioMixer_template.h"
#include "beats.h"

static pthread_t id;

static char* joy_directions[] = {joy_up, joy_down, joy_lft, joy_right, joy_in};


const char* readValFile(char *fileName)
{
	FILE *pFile = fopen(fileName, "r");
	if (pFile == NULL) {
		printf("ERROR: Unable to open file (%s) for read\n", fileName);
		exit(-1);
	}
	// Read string (line)
	const int MAX_LENGTH = 1024;
	char *buff = malloc(MAX_LENGTH);
	
	fgets(buff, MAX_LENGTH, pFile);
	fclose(pFile);

	
	return buff;
}

void readWriteFile(char *fileName, int value){
	FILE *file = fopen(fileName, "w");
	
	if (file == NULL) {
		printf("ERROR OPENING %s.", fileName);
		exit(1);
	}	
	
	int charWritten = fprintf(file,"%d" ,value);
	if (charWritten <= 0) {
		printf("ERROR WRITING DATA");
		exit(1);
	}
	
	fclose(file);
	
}

void export_all(){
	readWriteFile(export_path, 65);
	readWriteFile(export_path, 47);
	readWriteFile(export_path, 26);
	readWriteFile(export_path, 46);
	readWriteFile(export_path, 27);
}

int isPressed(const char* direction){
	int answer = 0;
	answer = strcmp(direction, "0\n");
	return answer;
	
}


void sleep_function(long milisec){
	
	for (int i = 0; i < 1; i++) {
		long sec = 0;
		milisec = 100;
		struct timespec reqDelay = {sec, milisec};
		nanosleep(&reqDelay, (struct timespec *) NULL);
	}

}

int readJoyInput(void){

	const char* direction_vals[5];
	while(1){
		for(int j = 0; j < 5; j++){
			direction_vals[j] = readValFile(joy_directions[j]);
			if(isPressed(direction_vals[j]) == 0){
				return j;
			}
				
		} 
	
	}
	
	return 0;
}

void increase_volume(){
	int prev_volume = AudioMixer_getVolume();
	int current_volume = prev_volume + 5;
	AudioMixer_setVolume(current_volume);
	printf("volume set to : %d \n", current_volume);
}

void decrease_volume(){
	int prev_volume = AudioMixer_getVolume();
	int current_volume = prev_volume - 5;
	AudioMixer_setVolume(current_volume);
	printf("volume set to : %d \n", current_volume);
}

void increase_tempo(){
	int prev_BPM = AudioMixer_getBPM();
	int current_BPM = prev_BPM + 5;
	AudioMixer_setBPM(current_BPM);
	printf("BPM set to : %d \n", current_BPM);
}

void decrease_tempo(){
	int prev_BPM = AudioMixer_getBPM();
	int current_BPM = prev_BPM - 5;
	AudioMixer_setBPM(current_BPM);
	printf("BPM set to : %d \n", current_BPM);
}

void* joystick_routine(){


	export_all();
	int i = 0;
	while(1){
	
		int ans = readJoyInput();
		sleep(1);
		
		//press left		
		if(ans == 2){
			//printf("you pressed left \n");
			decrease_tempo();
		}
		//press right
		else if(ans== 3){
			//printf("you pressed right \n");
			increase_tempo();
		}
		
		//press up
		else if(ans == 0){
			//printf("you pressed up \n");
			increase_volume();
		}
		
		//press down
		else if(ans == 1){
			//printf("you pressed down \n");
			decrease_volume();
		}	
		else if(ans == 4){
			printf("you pressed in \n");
			int beat = getBeat();
			if(beat == 2){
				beat = 0;
			}
			else{
				beat +=1;
			}
			setBeat(beat);

		}

		i++;
	}
	return NULL;
}

void joystick_init(){
	pthread_create(&id, NULL, &joystick_routine, NULL);
}
void joystick_cleanup(){
	pthread_join(id, NULL);
}


