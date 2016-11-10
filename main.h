//	Brendan Thompson
//  main.h
//  11/10/16
//
//  Basic Header for writing a midi file. 
//  page numbers reference Standard MIDI-File Format Spec. 1.1, updated
//

//		**** PROJECT OUTLINE ****
//  main.cpp = basic functions for writing a standard midi file
    //  including: wb, writeVLQ, writeSMF, writeHeader, writeTrackLength, etc.
    //	calls writeTrackEvent from trackEvents.cpp to write individual tracks
    //  will contain algorithms for making chords, arpeggios, scales, etc.
//
//	trackEvents.cpp = where a track is written. calls the individual functions to write the events for a track
    //	calls functions from channelMessages.cpp and metaEvents.cpp to write individual events
//
// 	channelMessages.cpp = where channel messages are written
//
//	metaEvents.cpp = where metaEvents are written
//
//	MIDIconst.h = creates a bunch of constants that make the code easier for the human to read and write

//**** Current Status ****
//	

#ifndef    main_H
#define    main_H

#define DEBUG

#include <iostream>
#include <fstream>
#include <iomanip>
#include "MIDIconst.h"
using namespace std;

// GLOBAL VARIABLES!!!!
unsigned int division;
unsigned int numTracks;


// *** Main Function Declarations ****

	// write byte = takes in a Hex value and prints it to the output file
	void wb (unsigned value);
		
	// read byte = read one byte from the global input file
	unsigned char rb (void);
	
	// writeVLQ = takes in a hex value and writes the converted array of VLQ Bytes to the file
	void writeVLQ (unsigned int hexNum);
	
	// writeSMF = calls the functions to write an entire Standard MIDI File 
	void writeSMF ();
	
	// writeHeadChunk = calls the functions to write an entire header chunk to a file
	void writeHeadChunk ();
	
	// writeTrackChunk = calls the functions to write an entire track chunk to a file
	void writeTrackChunk ();

// *** Track Events ***
	// writeEventDeltaTime (numTicks) = takes in a hex value and writes it as a VLQ to the file
	void writeEventDeltaTime (unsigned int numTicks);
	
	// writeTrackOne = writes track events to the file
	void writeTrackOne ();

	void makeMajorChord (unsigned char channel, unsigned char root, unsigned int volume);

	void makeMajorScale(unsigned char channel, unsigned char root, unsigned int volume);

	void musicThing (unsigned char channel, unsigned char root, unsigned int volume);

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
