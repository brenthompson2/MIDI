//	Brendan Thompson
//  trackMelody.cpp
//  11/15/16
//
//  Calls the functions that write a melody track
//  page numbers reference Standard MIDI-File Format Spec. 1.1, updated

#include "main.h"

// writeTrackOne = writes a track event to the file
void writeTrackMelody (unsigned char noteArray[], int lengthArray) {
	#ifdef DEBUG
	cout<<"\t\tWriting Melody Track"<<endl;
	#endif
	
	int i;
	char noteInput;
	
	//event 1: 	00 ff 51 03 0f 42 40 == at delta 0 - set tempo - to hex 0f4240
		writeEventDeltaTime (0x00); // time = 0
		metaSetTempo (0x0f, 0x42, 0x40); // new tempo = decimal 1000000 microseconds per quarter note = 1 second per quarter note
		
	//event 2: 00 c0 0b = at delta 0 - set program of channel 1 - to program decimal 1, the Basic Piano
		writeEventDeltaTime (0x00); // time = 0
		programChange (CHANNEL_1, 0x6D); // new program = 0x0b = decimal 1 = (pg 17)
	
	//Pattern 1: for the first 4 measures, output them sequentially as Half notes
		i = 0; 
		for (i; i < 4; i++){
			noteInput = noteArray[i];
			#ifdef DEBUG
				cout<<"\t\t\tMelody Pattern1: note: "<< noteInput <<"count: "<< i <<endl;
			#endif

			//turn note on
			writeEventDeltaTime (0x00); // time = 0
			noteOn (CHANNEL_1, noteInput, 0x60);
				
			//turn note off	
			writeEventDeltaTime (0xc0);
			noteOff (CHANNEL_1, noteInput, 0x60); 
		}

	// Pattern 2: for first half of the array, output them as eighth notes
			// beat = root, AND = 3rd
		for (i; i < (lengthArray/2); i++){
			noteInput = noteArray[i];
			#ifdef DEBUG
				cout<<"\t\t\tMelody Pattern2: note: "<< noteInput <<"count: "<< i <<endl;
			#endif

			// Beat
			writeEventDeltaTime (0x00); // time = 0
			noteOn (CHANNEL_1, noteInput, 0x60);
			writeEventDeltaTime (0x30);	// time = eighth note
			noteOff (CHANNEL_1, noteInput, 0x60); 

			// AND
			writeEventDeltaTime (0x00); // time = 0
			noteOn (CHANNEL_1, (noteInput + 4), 0x60);
			writeEventDeltaTime (0x30); // time = eighth note
			noteOff (CHANNEL_1, (noteInput + 4), 0x60); 

		}
		
	// Pattern 3: for the next 50 bytes, output major scales based off root note
		for (i; i < lengthArray; i++){
			noteInput = noteArray[i];
			#ifdef DEBUG
				cout<<"\t\t\tMelody Pattern3: note: "<< noteInput <<"count: "<< i <<endl;
			#endif
			makeMajorScale(CHANNEL_1, noteInput, 0x60);
		}

	//event8: 81 50 b0 7b 00 = at delta decimal 208 - control change - all notes off 
		writeEventDeltaTime (0xd0); //time = VLQ 81 50 = 0xd0 = decimal 208 
		controlChange (CHANNEL_1, 0x7b, 0x00);
			// turn off all notes on channel 1 (pg 10, 15)
			
	//event9: 00 ff 2f 00 = end of track
		writeEventDeltaTime (0x00); // time = 0
		metaEndOfTrack ();
}

// write 4 notes from the scale as 16th notes (1 beat)
void makeMajorScale(unsigned char channel, unsigned char root, unsigned int volume){
	int i;
	unsigned char second, third, fourth, fifth, sixth;

	second = root + 2;
	third = root + 4;
	fourth = root + 5;
	fifth = root + 7;
	sixth = root + 9;


	//turn note on
	writeEventDeltaTime (0x00); // time = 0
	noteOn (CHANNEL_1, root, volume);

	//turn note off	
	writeEventDeltaTime (0x15); // time = 32
	noteOff (CHANNEL_1, root, volume); 

	//turn note on
	writeEventDeltaTime (0x00); // time = 0
	noteOn (CHANNEL_1, second, volume);

	//turn note off	
	writeEventDeltaTime (0x15); // time = 32
	noteOff (CHANNEL_1, second, volume); 

	//turn note on
	writeEventDeltaTime (0x00); // time = 0
	noteOn (CHANNEL_1, third, volume);

	//turn note off	
	writeEventDeltaTime (0x15); // time = 32
	noteOff (CHANNEL_1, third, volume); 

	//turn note on
	writeEventDeltaTime (0x00); // time = 0
	noteOn (CHANNEL_1, fourth, volume);

	//turn note off	
	writeEventDeltaTime (0x15); // time = 32
	noteOff (CHANNEL_1, fourth, volume); 
/*
	//turn note on
	writeEventDeltaTime (0x00); // time = 0
	noteOn (CHANNEL_1, fifth, volume);

	//turn note off	
	writeEventDeltaTime (0x30); // time = 32
	noteOff (CHANNEL_1, fifth, volume); 

	//turn note on
	writeEventDeltaTime (0x00); // time = 0
	noteOn (CHANNEL_1, sixth, volume);

	//turn note off	
	writeEventDeltaTime (0x30); // time = 32
	noteOff (CHANNEL_1, sixth, volume); 
*/
}