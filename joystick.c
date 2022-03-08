#include "joystick.h"
#include "audioMixer_template.h"

static pthread_t id;

static char* joy_directions[] = {joy_up, joy_down, joy_lft, joy_right};


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
}

int isPressed(const char* direction){
	int answer = 0;
	answer = strcmp(direction, "0\n");
	return answer;
	
}


void sleep_function(void){
	
	for (int i = 0; i < 1; i++) {
		long seconds = 1;
		//long nanoseconds = 500000000;
		long nanoseconds = 100;
		struct timespec reqDelay = {seconds, nanoseconds};
		nanosleep(&reqDelay, (struct timespec *) NULL);
	}

}

int readJoyInput(void){

	const char* direction_vals[4];
	while(1){
		for(int j = 0; j < 4; j++){
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

void* joystick_routine(){

//modify this routine to have the add queue, set volume and tempo functionality
//add the "in" direction
//export all the gpio pins.
	export_all();
	int i = 0;
	while(1){
	
		int ans = readJoyInput();
		sleep_function();
		
		//press left		
		if(ans == 2){
			printf("you pressed left \n");
		 	
		}
		//press right
		else if(ans== 3){
			printf("you pressed right \n");
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


