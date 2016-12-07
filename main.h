//	Brendan Thompson
//  main.h
//  12/05/16
//
//  Header for reading a notMIDI file and outputting is in MIDI
//  page numbers reference Standard MIDI-File Format Spec. 1.1, updated

#ifndef    MAIN_H
#define    MAIN_H

// #define DEBUG

#define MAXARRAYSIZE 250

#include <iostream>
#include <fstream>
#include <iomanip>
#include "MIDIconst.h"
#include <stdio.h>
using namespace std;

// symbolic constants
const   unsigned BUFF_SIZE = 200;
const   char    COMMENT_CHAR = '/';
const   char    TRACK_COUNT_CHAR = 'N';
const   char    MEASURE_CHAR = 'M';

struct EVENT {
	string eventName;
	char data1[10];
	char data2[10];
	char data3[10];
};

struct BEAT {
	int numEvents;
	EVENT eventList[30];
};

// *** Main Function Declarations ****

	// write byte = takes in a Hex value and prints it to the output file
	void wb (unsigned value);
		
	// rb = reads values from a file, converts them to notes between C3 and B5,
		// and puts the notes into an array 
	void rb (void);
	
	// writeVLQ = takes in a hex value and writes the converted array of VLQ Bytes to the file
	void writeVLQ (unsigned int hexNum);
	
	// writeSMF = calls the functions to write an entire Standard MIDI File 
	void writeSMF ();
	
	// writeHeadChunk = calls the functions to write an entire header chunk to a file
	void writeHeadChunk ();
	
	// writeTrackChunk = calls the functions to write an entire track chunk to a file
	void writeTrackChunk ();

	// writeEventDeltaTime (numTicks) = takes in a hex value and writes it as a VLQ to the file
	void writeEventDeltaTime (unsigned int numTicks);

// *** Track Events ***
	

// *** EVENTS ***
	// *** Meta Events ***
		// metaEndOfTrack = FF 2f 00 = writes end of track to the file
		void metaEndOfTrack ();
		
		// metaSetTempo = FF 51 03 = takes in the three bytes to set the tempo to and writes the event to the file (pg 8)
		void metaSetTempo (unsigned int a, unsigned int b, unsigned int c);


	// *** Channel Messages ***
		// note on = 9channel = turn on note on channel at volume
		void noteOn (unsigned char channel, unsigned char note, unsigned int volume);
		
		// note off = 8channel = turn on note on channel at volume
		void noteOff (unsigned char channel, unsigned char note, unsigned int volume);
		
		// programChange = Cchannel = set instrument of channel to program (pg 10)
		void programChange (unsigned char channel, unsigned int program);
		
		// controlChange = Bchannel = change control of controller to value (pg 10)
		void controlChange (unsigned char channel, unsigned int controller, unsigned int value);

// *** File Reader ***
	// function comment here
	void processNote (char buffer[]);
	// function comment here
	void processTrackCount (char buffer[]);
	// function comment here
	void processMeasureNumber (char buffer[]);
	// function comment here
	void processNoteName (char buffer[]);
	// function comment here
	void processNoteDuration (char buffer[]);
	// function comment here
	void processBeatNumber (char buffer[]);


#endif
