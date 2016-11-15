//	Brendan Thompson
//  trackDrums.cpp
//  11/15/16
//
//  Calls the functions that write the events for a drum track
//  page numbers reference Standard MIDI-File Format Spec. 1.1, updated

#include "main.h"

// writeTrackOne = writes a track event to the file
void writeTrackDrums (int lengthArray) {
	#ifdef DEBUG
	cout<<"\t\tWriting DRUM Track Events "<<endl;
	#endif
	
	int i;
	char noteInput;
	
	//event 1: 	00 ff 51 03 0f 42 40 == at delta 0 - set tempo - to hex 0f4240
		writeEventDeltaTime (0x00); // time = 0
		metaSetTempo (0x0f, 0x42, 0x40); // new tempo = decimal 1000000 microseconds per quarter note = 1 second per quarter note

	i = 0;
	// Pattern 1: Intro. Bass on 2 4
		for (i; i < 4; i++) {
			// cout<<"Pattern 1\n";

			writeEventDeltaTime (0x60);
			noteOn(CHANNEL_10, B1, 0x60);

			writeEventDeltaTime (0x60);
			noteOn(CHANNEL_10, B1, 0x60);
		}

	// Pattern 2: Bass on the beat, snare on the AND
		for (i; i < (lengthArray/2); i++) {
			writeEventDeltaTime (0x00);
			noteOn(CHANNEL_10, B1, 0x60);
			writeEventDeltaTime (0x30);
			noteOff(CHANNEL_10, D2, 0x60);

			writeEventDeltaTime (0x00);
			noteOn(CHANNEL_10, B1, 0x30);
			writeEventDeltaTime (0x30);
			noteOff(CHANNEL_10, D2, 0x60);

			writeEventDeltaTime (0x00);
			noteOn(CHANNEL_10, B1, 0x30);
			writeEventDeltaTime (0x30);
			noteOff(CHANNEL_10, D2, 0x60);

			writeEventDeltaTime (0x00);
			noteOn(CHANNEL_10, B1, 0x30);
			writeEventDeltaTime (0x30);
			noteOff(CHANNEL_10, D2, 0x60);
		}

	// Pattern 3: Bass on the beat, snare on the AND, clap on 2 4
		for (i; i < lengthArray; i++) {
			writeEventDeltaTime (0x00);
			noteOn(CHANNEL_10, B1, 0x60);
			writeEventDeltaTime (0x30);
			noteOff(CHANNEL_10, D2, 0x60);

			writeEventDeltaTime (0x30);
			noteOn(CHANNEL_10, B1, 0x60);
			writeEventDeltaTime (0x00);
			noteOn(CHANNEL_10, Ds2, 0x60);
			writeEventDeltaTime (0x30);
			noteOff(CHANNEL_10, D2, 0x60);

			writeEventDeltaTime (0x30);
			noteOn(CHANNEL_10, B1, 0x60);
			writeEventDeltaTime (0x30);
			noteOff(CHANNEL_10, D2, 0x60);

			writeEventDeltaTime (0x30);
			noteOn(CHANNEL_10, B1, 0x60);
			writeEventDeltaTime (0x00);
			noteOn(CHANNEL_10, Ds2, 0x60);
			writeEventDeltaTime (0x30);
			noteOff(CHANNEL_10, D2, 0x60);
		}

	//event8: 81 50 b0 7b 00 = at delta decimal 208 - control change - all notes off 
		writeEventDeltaTime (0xd0); //time = VLQ 81 50 = 0xd0 = decimal 208 
		controlChange (CHANNEL_10, 0x7b, 0x00);
			// turn off all notes on channel 10 (pg 10, 15)
			
	//event9: 00 ff 2f 00 = end of track
		writeEventDeltaTime (0x00);
		metaEndOfTrack ();
}