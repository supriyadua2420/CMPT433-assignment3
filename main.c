#include "audioMixer_template.h"
#include <stdlib.h>

int main(){


	//wavedata_t sound;
	//AudioMixer_readWaveFileIntoMemory(HI_HAT, &sound);
	//AudioMixer_queueSound(&sound);	
	
	AudioMixer_init();
	AudioMixer_cleanup();
	
	//wavedata_t sound;
	//AudioMixer_queueSound(&sound);
	
	//free(sound.pData);
return 0;
}
