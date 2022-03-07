#include <alsa/asoundlib.h>

// File used for play-back:
// If cross-compiling, must have this file available, via this relative path,
// on the target when the application is run. This example's Makefile copies the wave-files/
// folder along with the executable to ensure both are present.
#define SOURCE_FILE "wave-files/100060__menegass__gui-drum-splash-hard.wav"
//#define SOURCE_FILE "./wave-files/100053__menegass__gui-drum-cc.wav"

#define SAMPLE_RATE   44100
#define NUM_CHANNELS  1
#define SAMPLE_SIZE   (sizeof(short)) 	// bytes per sample

typedef struct {
	int numSamples;
	short *pData;
} wavedata_t;

snd_pcm_t *Audio_openDevice();
void Audio_readWaveFileIntoMemory(char *fileName, wavedata_t *pWaveStruct);
void Audio_playFile(snd_pcm_t *handle, wavedata_t *pWaveData);
void config_wave();
void play_once();
void clean();
