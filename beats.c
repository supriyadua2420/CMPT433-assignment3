#include "beats.h"

//make both beats and test them.

wavedata_t sounds[3];

pthread_t beats_thread;

long wait_time()
{
    int bpm = AudioMixer_getBPM();
	long milisec = ((double) 60 / bpm / 2) * 1000000000;

    return milisec;
}

void Rock1(){
    long wait = wait_time();

     AudioMixer_queueSound(&sounds[0]);
     AudioMixer_queueSound(&sounds[2]);
     sleep_function(wait);

     AudioMixer_queueSound(&sounds[0]);
     sleep_function(wait);

     AudioMixer_queueSound(&sounds[0]);
     AudioMixer_queueSound(&sounds[1]);
     sleep_function(wait);

     AudioMixer_queueSound(&sounds[0]);
     sleep_function(wait);

   /* AudioMixer_queueSound(&sounds[0]);
     AudioMixer_queueSound(&sounds[2]);
     sleep_function(wait);

     AudioMixer_queueSound(&sounds[0]);
     sleep_function(wait);

     AudioMixer_queueSound(&sounds[0]);
     AudioMixer_queueSound(&sounds[1]);
     sleep_function(wait);

     AudioMixer_queueSound(&sounds[0]);
     sleep_function(wait);*/

    

}

void Rock2(){

}

void* beats_routine()
{
    while(1){
		Rock1();	
		sleep(1);
	}
}
void beats_init(){
    AudioMixer_readWaveFileIntoMemory(HI_HAT, &sounds[0]);
    AudioMixer_readWaveFileIntoMemory(SNARE, &sounds[1]);
    AudioMixer_readWaveFileIntoMemory(BASE_DRUM, &sounds[2]);

    pthread_create(&beats_thread, NULL, &beats_routine, NULL);

}

void beats_cleanup(){
    pthread_join(beats_thread, NULL);
}