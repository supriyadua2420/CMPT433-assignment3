#include "audioMixer_template.h"
#include "acc_sample.h"
//#include "joystick.h"
//#include "website_control.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>


int main(){
	
	AudioMixer_init();
	acc_init();
	//joystick_init();
	//web_init();
	wavedata_t sound;
	AudioMixer_readWaveFileIntoMemory(HI_HAT, &sound);
	int i = 0 ;
	while(i<50){
		AudioMixer_queueSound(&sound);
		sleep(1);
		i++;
	}

	//web_cleanup();
	//joystick_cleanup();
	acc_cleanup();
	AudioMixer_cleanup();
	

	
	
return 0;
}
