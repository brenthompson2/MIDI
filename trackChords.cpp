//	Brendan Thompson
//  trackChords.cpp
//  11/15/16
//
//  Calls the functions that write the events for a chord track
//  page numbers reference Standard MIDI-File Format Spec. 1.1, updated

#include "main.h"

// writeTrackOne = writes a track event to the file
void writeTrackChords (unsigned char noteArray[], int lengthArray) {
	#ifdef DEBUG
	cout<<"\t\tWriting Track Events "<<endl;
	#endif
	
	int i;
	char noteInput;
	
	//event 1: 	00 ff 51 03 0f 42 40 == at delta 0 - set tempo - to hex 0f4240
		writeEventDeltaTime (0x00); // time = 0
		metaSetTempo (0x0f, 0x42, 0x40); // new tempo = decimal 1000000 microseconds per quarter note = 1 second per quarter note
		
	//event 2: 00 c0 0b = at delta 0 - set program of channel 1 - to program decimal 1, the Basic Piano
		writeEventDeltaTime (0x00); // time = 0
		programChange (CHANNEL_2, 0x6D); // new program = 0x0b = decimal 1 = (pg 17)
	
	//Pattern 1: for first half of the array, output chords sequentially as Half notes
		i = 0; 
		for (i; i < (lengthArray/2); i++){
			noteInput = noteArray[i];
			#ifdef DEBUG
				cout<<"\t\t\tChord Pattern1: note: "<< noteInput <<"count: "<< i <<endl;
			#endif
			makeMajorChord(CHANNEL_2, noteInput, 0x60, 0xc0);
		}

	//Pattern 2: for the next 50 bytes, output major chords based off root note
		for (i; i < lengthArray; i++){
			noteInput = noteArray[i];
			#ifdef DEBUG
				cout<<"\t\t\tChord Pattern2: note: "<< noteInput <<"count: "<< i <<endl;
			#endif
			makeMajorChord(CHANNEL_2, noteInput, 0x60, 0xc0);

		}

	//event8: 81 50 b0 7b 00 = at delta decimal 208 - control change - all notes off 
		writeEventDeltaTime (0xd0); //time = VLQ 81 50 = 0xd0 = decimal 208 
		controlChange (CHANNEL_2, 0x7b, 0x00);
			// turn off all notes on channel 2 (pg 10, 15)
			
	//event9: 00 ff 2f 00 = end of track
		writeEventDeltaTime (0x00);
		metaEndOfTrack ();
}

void makeMajorChord (unsigned char channel, unsigned char root, unsigned int volume, unsigned int noteLength){
	int i;
	unsigned char third, fifth;

	third = root + 4;
	fifth = root + 7;

	//turn note on
	writeEventDeltaTime (0x00);
	noteOn (CHANNEL_2, root, volume);

	//turn note on
	writeEventDeltaTime (0x00);
	noteOn (CHANNEL_2, third, volume);

	//turn note on
	writeEventDeltaTime (0x00);
	noteOn (CHANNEL_2, fifth, volume);

	//turn note off	
	writeEventDeltaTime (noteLength);
	noteOff (CHANNEL_2, root, volume); 

	//turn note off	
	writeEventDeltaTime (0x00);
	noteOff (CHANNEL_2, third, volume); 

	//turn note off	
	writeEventDeltaTime (0x00);
	noteOff (CHANNEL_2, fifth, volume); 
}