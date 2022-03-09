#include "beats.h"

//make both beats and test them.
//add the in pin in joysitck module

wavedata_t sounds[3];

void beats_init(){
    AudioMixer_readWaveFileIntoMemory(HI_HAT, &sounds[0]);
    AudioMixer_readWaveFileIntoMemory(SNARE, &sounds[1]);
    AudioMixer_readWaveFileIntoMemory(BASE_DRUM, &sounds[2]);
}

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