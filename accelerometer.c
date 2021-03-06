#include "accelerometer.h"
#include "audioMixer_template.h"

wavedata_t sound;

static pthread_t id;

static char config[2] = {0};
static char data[7] = {0};

static int initI2cBus(void)
{
	// Create I2C bus
	int file;
	char *bus = "/dev/i2c-1";
	if((file = open(bus, O_RDWR)) < 0) 
	{
		printf("Failed to open the bus. \n");
		exit(1);
	}
	// Get I2C device, MMA8452Q I2C address is 0x1C(28)
	ioctl(file, I2C_SLAVE, 0x1C);
	
	return file;
}

//Set to standby mode
void standbyMode(int file){
	config[0] = 0x2A;
	config[1] = 0x00;
	write(file, config, 2);
}

//Set to Active mode
void activeMode(int file){
	config[0] = 0x2A;
	config[1] = 0x01;
	write(file, config, 2);
}

// Set range to +/- 2g(0x00)
void setRange(int file){
	config[0] = 0x0E;
	config[1] = 0x00;
	write(file, config, 2);
}

int digit12(int index1, int index2){
	
	int Accl = ((data[index1] * 256) + data[index2]) / 16;
	if(Accl > 2047)
	{
		Accl -= 4096;
	}
	
	return Accl;
}


void readData(int file){
	
	wavedata_t sound;
	// Read 7 bytes of data(0x00)
	char reg[1] = {0x00};
	write(file, reg, 1);
	if(read(file, data, 7) != 7)
	{
		printf("Error : Input/Output error \n");
	}
	else{
		int x = digit12(1,2);
		int y = digit12(3,4);
		int z = digit12(5,6);
		
		
		if(x > 200 || x < -200){
			printf("x threshold reached : now playing Snare \n");
			AudioMixer_readWaveFileIntoMemory(SNARE, &sound);
			AudioMixer_queueSound(&sound);
			sleep(1);
			AudioMixer_freeWaveFileData(&sound);
			
		}
		if(y > 200 || y < -200){
			printf("y threshold reached : now playing Hi-Hat \n");
			AudioMixer_readWaveFileIntoMemory(HI_HAT, &sound);
			AudioMixer_queueSound(&sound);
			sleep(1);
			AudioMixer_freeWaveFileData(&sound);
			
		}
		if(z > 1200 || z < -200){
			printf("z threshold reached : now playing BASE_DRUM \n");
			AudioMixer_readWaveFileIntoMemory(BASE_DRUM, &sound);
			AudioMixer_queueSound(&sound);
			sleep(1);
			AudioMixer_freeWaveFileData(&sound);
			
		}
	}
}



void* acc_routine(){

	int file = initI2cBus();
	setRange(file);
	
	while(1){
	 standbyMode(file);
	 activeMode(file);
	 sleep(0.5);
	 
	 readData(file);
	 sleep(2);
	 
	}
	
	return NULL;
	
}

void acc_init(void){
	pthread_create(&id, NULL, &acc_routine, NULL);
	
}

void acc_cleanup(void){
	pthread_join(id, NULL);
	
}
 

