#include "audioMixer_template.h"
#include "accelerometer.h"
#include "joystick.h"
#include "beats.h"
#include "webpage.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>


int main(){
	
	AudioMixer_init();
	acc_init();
	joystick_init();
	beats_init();
	web_init();

	web_cleanup();
	beats_cleanup();
	joystick_cleanup();
	acc_cleanup();
	AudioMixer_cleanup();
	

	
	
return 0;
}
