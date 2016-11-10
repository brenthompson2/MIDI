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

	// Pattern 1: for the next 50 bytes, output major scales based off of the root note
		counter = 0;
		for (int i = 0; i < numBits; i++) {
			makeMajorScale(CHANNEL_1, noteInput, 0x60);
			noteInput = notesFromFile[i];
			counter++;
		}

	//event8: 81 50 b0 7b 00 = at delta decimal 208 - control change - all notes off 
		writeEventDeltaTime (0xd0); //time = VLQ 81 50 = 0xd0 = decimal 208 
		controlChange (CHANNEL_1, 0x7b, 0x00);
			// turn off all notes on channel 1 (pg 10, 15)
			
	//event9: 00 ff 2f 00 = end of track
		writeEventDeltaTime (0x00); // time = 0
		metaEndOfTrack ();
}


void makeMajorScale(unsigned char channel, unsigned char root, unsigned int volume){
	int i;
	unsigned char second, third, fourth, fifth, sixth;

	second = root + 2;
	third = root + 4;
	fourth = root +5;
	fifth = root + 7;
	sixth = root + 9;


	//turn note on
	writeEventDeltaTime (0x00); // time = 0
	noteOn (CHANNEL_1, root, volume);

	//turn note off	
	writeEventDeltaTime (0x20); // time = 32
	noteOff (CHANNEL_1, root, volume); 

	//turn note on
	writeEventDeltaTime (0x00); // time = 0
	noteOn (CHANNEL_1, second, volume);

	//turn note off	
	writeEventDeltaTime (0x20); // time = 32
	noteOff (CHANNEL_1, second, volume); 

	//turn note on
	writeEventDeltaTime (0x00); // time = 0
	noteOn (CHANNEL_1, third, volume);

	//turn note off	
	writeEventDeltaTime (0x20); // time = 32
	noteOff (CHANNEL_1, third, volume); 

	//turn note on
	writeEventDeltaTime (0x00); // time = 0
	noteOn (CHANNEL_1, fourth, volume);

	//turn note off	
	writeEventDeltaTime (0x20); // time = 32
	noteOff (CHANNEL_1, fourth, volume); 

	//turn note on
	writeEventDeltaTime (0x00); // time = 0
	noteOn (CHANNEL_1, fifth, volume);

	//turn note off	
	writeEventDeltaTime (0x20); // time = 32
	noteOff (CHANNEL_1, fifth, volume); 

	//turn note on
	writeEventDeltaTime (0x00); // time = 0
	noteOn (CHANNEL_1, sixth, volume);

	//turn note off	
	writeEventDeltaTime (0x20); // time = 32
	noteOff (CHANNEL_1, sixth, volume); 
}

void musicThing (unsigned char channel, unsigned char root, unsigned int volume){
	int i;
	unsigned char second, third, fourth, fifth, sixth;

	second = root + 2;
	third = root + 4;
	fourth = root +5;
	fifth = root + 7;
	sixth = root + 9;

	//chord on
	//turn note on
	writeEventDeltaTime (0x00); // time = 0
	noteOn (CHANNEL_1, root, volume);

	//turn note on
	writeEventDeltaTime (0x00); // time = 0
	noteOn (CHANNEL_1, third, volume);

	//turn note on
	writeEventDeltaTime (0x00); // time = 0
	noteOn (CHANNEL_1, fifth, volume);

	//scale
	//turn note on
	writeEventDeltaTime (0x00); // time = 0
	noteOn (CHANNEL_1, root, volume);

	//turn note off	
	writeEventDeltaTime (0x20); // time = 32
	noteOff (CHANNEL_1, root, volume); 

	//turn note on
	writeEventDeltaTime (0x00); // time = 0
	noteOn (CHANNEL_1, second, volume);

	//turn note off	
	writeEventDeltaTime (0x20); // time = 32
	noteOff (CHANNEL_1, second, volume); 

	//turn note on
	writeEventDeltaTime (0x00); // time = 0
	noteOn (CHANNEL_1, third, volume);

	//turn note off	
	writeEventDeltaTime (0x20); // time = 32
	noteOff (CHANNEL_1, third, volume); 

	//turn note on
	writeEventDeltaTime (0x00); // time = 0
	noteOn (CHANNEL_1, fourth, volume);

	//turn note off	
	writeEventDeltaTime (0x20); // time = 32
	noteOff (CHANNEL_1, fourth, volume); 

	//turn note on
	writeEventDeltaTime (0x00); // time = 0
	noteOn (CHANNEL_1, fifth, volume);

	//turn note off	
	writeEventDeltaTime (0x20); // time = 32
	noteOff (CHANNEL_1, fifth, volume); 

	//turn note on
	writeEventDeltaTime (0x00); // time = 0
	noteOn (CHANNEL_1, sixth, volume);

	//turn note off	
	writeEventDeltaTime (0x20); // time = 32
	noteOff (CHANNEL_1, sixth, volume); 

	//chord off
	//turn note off	
	writeEventDeltaTime (0x00); // time = 32
	noteOff (CHANNEL_1, root, volume); 

	//turn note off	
	writeEventDeltaTime (0x00); // time = 32
	noteOff (CHANNEL_1, third, volume); 

	//turn note off	
	writeEventDeltaTime (0x00); // time = 32
	noteOff (CHANNEL_1, fifth, volume); 
}
