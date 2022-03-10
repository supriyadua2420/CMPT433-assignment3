#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#define joy_lft "/sys/class/gpio/gpio65/value" 
#define joy_right "/sys/class/gpio/gpio47/value" 
#define joy_up "/sys/class/gpio/gpio26/value"
#define joy_down "/sys/class/gpio/gpio46/value"
#define joy_in "/sys/class/gpio/gpio27/value"

#define export_path "/sys/class/gpio/export"

void joystick_init();
void joystick_cleanup();

void increase_volume();
void decrease_volume();
void increase_tempo();
void decrease_tempo();

void sleep_function(long milisec);

void* joystick_routine();
