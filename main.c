#include "audioMixer_template.h"
//#include "wave_player.h"
#include "acc_sample.h"
//#include "joystick.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(){


	/*AudioMixer_init();

	wavedata_t sound;
	AudioMixer_readWaveFileIntoMemory(HI_HAT, &sound);
	printf("almost done \n");
	AudioMixer_queueSound(&sound);
	//
	AudioMixer_cleanup();
	exit(1);*/
	
	//AudioMixer_init();
	acc_init();
	
	acc_cleanup();
	//AudioMixer_cleanup();
	
	
	//joystick_init();
	//joystick_cleanup();
	
	/*printf("Beginning play-back of %s\n", SOURCE_FILE);
	config();
	play_once();
	clean();*/
	
return 0;
}
