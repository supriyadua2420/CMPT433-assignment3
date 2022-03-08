#include "audioMixer_template.h"
//#include "wave_player.h"
#include "acc_sample.h"
//#include "joystick.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(){


	
	AudioMixer_init();
	acc_init();
	/*wavedata_t sound;
	AudioMixer_readWaveFileIntoMemory(SNARE, &sound);
	
	int i =0;
	while(i<4){
	AudioMixer_queueSound(&sound);
	sleep(3);
	i++;
	}
	AudioMixer_freeWaveFileData(&sound);*/
	acc_cleanup();
	AudioMixer_cleanup();
	
	
	
	//AudioMixer_init();
	//acc_init();
	
	//acc_cleanup();
	//AudioMixer_cleanup();
	
	
	//joystick_init();
	//joystick_cleanup();
	
	
return 0;
}
