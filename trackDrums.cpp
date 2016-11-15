//	Brendan Thompson
//  trackDrums.cpp
//  11/10/16
//
//  Calls the functions that write the events for a track
//  page numbers reference Standard MIDI-File Format Spec. 1.1, updated

//  This will contain algorithms for making chords, arpeggios, scales, etc.

// To do:
// 	- take in tempo from main and put it to event 1

#include "main.h"


// writeTrackOne = writes a track event to the file
void writeTrackDrums () {
	#ifdef DEBUG
	cout<<"\t\tWriting Track Events "<<endl;
	#endif
	
	int counter = 1, i;
	char noteInput;
	
	//event 1: 	00 ff 51 03 0f 42 40 == at delta 0 - set tempo - to hex 0f4240
		writeEventDeltaTime (0x00); // time = 0
		metaSetTempo (0x0f, 0x42, 0x40); // new tempo = decimal 1000000 microseconds per quarter note = 1 second per quarter note
		
	//event 2: 00 c0 0b = at delta 0 - set program of channel 1 - to program decimal 1, the Basic Piano
		writeEventDeltaTime (0x00); // time = 0
		programChange (0x01, 0x6D); // new program = 0x0b = decimal 1 = (pg 17)

	// Pattern 1: Bass on the beat, snare on the AND
		for (i; i < (lengthArray/2); i++) {
			writeEventDeltaTime (0x00); // time = 0
			noteOn(CHANNEL_10, B1, 0x60);
			writeEventDeltaTime (0x30); // time = 0
			noteOne(CHANNEL_10, D2, 0x60);

			writeEventDeltaTime (0x00); // time = 0
			noteOn(CHANNEL_10, B1, 0x30);
			writeEventDeltaTime (0x30); // time = 0
			noteOne(CHANNEL_10, D2, 0x60);

			writeEventDeltaTime (0x00); // time = 0
			noteOn(CHANNEL_10, B1, 0x30);
			writeEventDeltaTime (0x30); // time = 0
			noteOne(CHANNEL_10, D2, 0x60);

			writeEventDeltaTime (0x00); // time = 0
			noteOn(CHANNEL_10, B1, 0x30);
			writeEventDeltaTime (0x30); // time = 0
			noteOne(CHANNEL_10, D2, 0x60);
		}

	// Pattern 2: Bass on the beat, snare on the AND, clap on 2 4
		for (i; i < lengthArray; i++) {
			writeEventDeltaTime (0x00); // time = 0
			noteOn(CHANNEL_10, B1, 0x60);
			writeEventDeltaTime (0x30); // time = 0
			noteOne(CHANNEL_10, D2, 0x60);

			writeEventDeltaTime (0x30); // time = 0
			noteOn(CHANNEL_10, B1, 0x60);
			writeEventDeltaTime (0x00); // time = 0
			noteOn(CHANNEL_10, Ds2, 0x60);
			writeEventDeltaTime (0x30); // time = 0
			noteOne(CHANNEL_10, D2, 0x60);

			writeEventDeltaTime (0x30); // time = 0
			noteOn(CHANNEL_10, B1, 0x60);
			writeEventDeltaTime (0x30); // time = 0
			noteOne(CHANNEL_10, D2, 0x60);

			writeEventDeltaTime (0x30); // time = 0
			noteOn(CHANNEL_10, B1, 0x60);
			writeEventDeltaTime (0x00); // time = 0
			noteOn(CHANNEL_10, Ds2, 0x60);
			writeEventDeltaTime (0x30); // time = 0
			noteOne(CHANNEL_10, D2, 0x60);
		}

	//event8: 81 50 b0 7b 00 = at delta decimal 208 - control change - all notes off 
		writeEventDeltaTime (0xd0); //time = VLQ 81 50 = 0xd0 = decimal 208 
		controlChange (CHANNEL_10, 0x7b, 0x00);
			// turn off all notes on channel 10 (pg 10, 15)
			
	//event9: 00 ff 2f 00 = end of track
		writeEventDeltaTime (0x00); // time = 0
		metaEndOfTrack ();
}