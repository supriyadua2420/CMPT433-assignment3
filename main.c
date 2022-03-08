#include "audioMixer_template.h"
//#include "wave_player.h"
#include "acc_sample.h"
#include "joystick.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(){


	
	/*AudioMixer_init();
	acc_init();
	
	acc_cleanup();
	AudioMixer_cleanup();
	*/
	
	
	AudioMixer_init();
	//acc_init();
	joystick_init();

	joystick_cleanup();
	//acc_cleanup();
	AudioMixer_cleanup();
	
	
	
	
	
	
return 0;
}
