#include "beats.h"

//make both beats and test them.

wavedata_t sounds[4];
int current_beat = 0;

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

    

}

void Rock2(){

     long wait = wait_time();
     AudioMixer_queueSound(&sounds[0]);
     AudioMixer_queueSound(&sounds[2]);
     sleep_function(wait);

     AudioMixer_queueSound(&sounds[3]);
     sleep_function(wait);

     AudioMixer_queueSound(&sounds[0]);
     AudioMixer_queueSound(&sounds[1]);
     sleep_function(wait);

     AudioMixer_queueSound(&sounds[3]);
     sleep_function(wait);
}

int getBeat(){
    return current_beat;
}

void setBeat(int beat){
    current_beat = beat;
}


void beat_change(){

    current_beat = getBeat();
    if(current_beat == 0){
        //no sound
    }
    else if(current_beat == 1){
        Rock1();
        sleep(1);
        
    }
    else if(current_beat == 2){
        Rock2();
        sleep(1);
    }

}

void* beats_routine()
{
    while(1){

        beat_change();			
		sleep(1);
	}
}
void beats_init(){
    AudioMixer_readWaveFileIntoMemory(HI_HAT, &sounds[0]);
    AudioMixer_readWaveFileIntoMemory(SNARE, &sounds[1]);
    AudioMixer_readWaveFileIntoMemory(BASE_DRUM, &sounds[2]);
    AudioMixer_readWaveFileIntoMemory(DRUM_CYN, &sounds[3]);

    pthread_create(&beats_thread, NULL, &beats_routine, NULL);

}

void beats_cleanup(){
    pthread_join(beats_thread, NULL);
}