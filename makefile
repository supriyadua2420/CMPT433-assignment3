# Makefile for building embedded application.
# by Brian Fraser

# Edit this file to compile extra C files into their own programs.

TARGET= audioMixer
#TARGET = wave_player
#TARGET = acc
#TARGET = joy
#TARGET = music

SOURCES= audioMixer_template.h audioMixer_template.c acc_sample.h acc_sample.c main.c
#SOURCES = wave_player.h wave_player.c main.c
#SOURCES = acc_sample.h acc_sample.c wave_player.h wave_player.c main.c
#SOURCES = joystick.h joystick.c main.c
#SOURCES = wave_player.h wave_player.c website_control.c 

PUBDIR = $(HOME)/cmpt433/public
OUTDIR = $(PUBDIR)
CROSS_TOOL = arm-linux-gnueabihf-
CC_CPP = $(CROSS_TOOL)g++
CC_C = $(CROSS_TOOL)gcc

CFLAGS = -Wall -g -std=c99 -D _POSIX_C_SOURCE=200809L -Werror


# Asound process:
# get alibsound2 lib on target:
# 	# apt-get install libasound2
# Copy target's /usr/lib/arm-linux-gnueabihf/libasound.so.2.0.0 
#      to host  ~/public/asound_lib_BBB/libasound.so
# Copy to just base library:

LFLAGS = -L$(HOME)/cmpt433/public/asound_lib_BBB


# -pg for supporting gprof profiling.
#CFLAGS += -pg



all: wav
	$(CC_C) $(CFLAGS) $(SOURCES) -o $(OUTDIR)/$(TARGET)  $(LFLAGS) -lpthread -lasound

# Copy wave files to the shared folder
wav:
	mkdir -p $(PUBDIR)/wave-files/
	cp wave-files/* $(PUBDIR)/wave-files/ 

clean:
	rm -f $(OUTDIR)/$(TARGET)

