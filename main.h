//	Brendan Thompson
//  main.h
//  11/10/16
//
//  Basic Header for writing a midi file. 
//  page numbers reference Standard MIDI-File Format Spec. 1.1, updated

#ifndef    MAIN_H
#define    MAIN_H

#define DEBUG

#define MAXARRAYSIZE 250

#include <iostream>
#include <fstream>
#include <iomanip>
#include "MIDIconst.h"
using namespace std;

// GLOBAL VARIABLES!!!!
unsigned char division;
unsigned char numTracks;
unsigned char noteArray[MAXARRAYSIZE];
unsigned int lengthArray;

// *** Main Function Declarations ****

	// write byte = takes in a Hex value and prints it to the output file
	void wb (unsigned value);
		
	// read byte = read one byte from the global input file
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
	
	// writeTrackMelody = writes track events for the melody to the file
	void writeTrackMelody ();
	void makeMajorScale(unsigned char channel, unsigned char root, unsigned int volume);

	void writeTrackChords ();
	void makeMajorChord (unsigned char channel, unsigned char root, unsigned int volume);

	void writeTrackDrums ();


	//writeTrackDrums = write track events for the drums to the file

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

#endif
