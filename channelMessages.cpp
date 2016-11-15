//	Brendan Thompson
//  channelMessages.cpp
//  11/10/16
//
//  Functions that write channel message events
//  page numbers reference Standard MIDI-File Format Spec. 1.1, updated

#ifndef    channelMessages_H
#define    channelMessages_H

#include "main.h"

// **** CHANNEL MESSAGE DEFINITIONS ****

// note on = 9channel = turn on note on channel at volume
void noteOn (unsigned char channel, unsigned char note, unsigned int volume)
{
	
	//convert to the channel and append with prefix 9
	unsigned int newByte;

	newByte = channel | 0x90;

	// midNote = (int(note) % 35) + 48;
	// cout<<dec<<midNote<<endl;

	// finalNote = char(midNote);
	// cout<<dec<<int(finalNote)<<endl;
	
	#ifdef DEBUG
	cout << "\t\t\t\tWriting Event Note On on channel: " << hex << channel << " note: " << note << " volume: " << volume << endl;
	#endif
	
	// write Event Note On on channel
	wb (newByte);
	//write the note to the file
	wb (note);
	//write the volume to the file
	wb (volume);
};

// note off = 8channel = turn on note on channel at volume
void noteOff (unsigned char channel, unsigned char note, unsigned int volume)
{
	
	//convert to the channel and append with prefix 9
	unsigned int newByte;

	newByte = channel | 0x80;

	// midNote = (int(note) % 35) + 48;

	// finalNote = char(midNote);
	
	#ifdef DEBUG
	cout << "\t\t\t\tWriting Event Note Off on channel: " << hex << newByte << " note: " << note << " volume: " << volume << endl;
	#endif
	
	// write Event Note Off on channel
	wb (newByte);
	//write the note to the file
	wb (note);
	//write the volume to the file
	wb (volume);
}

// programChange = Cn = set instrument of channel to program (pg 10)
void programChange (unsigned char channel, unsigned int program)
{
	
	//convert to the channel and append with prefix c
	unsigned int newByte;
	//channel--;
	channel--;
	newByte = channel | 0xC0;
	
	#ifdef DEBUG
	cout << "\t\t\t\tWriting Event Program Change on channel " << hex << newByte << " to " << program << endl;
	#endif
	
	//write Event Program Change on channel
	wb (newByte);
	//write the new program to the file
	wb (program);
}

// controlChange = Bchannel = change control of controller to value (pg 10)
void controlChange (unsigned char channel, unsigned int controller, unsigned int value)
{
	
	//convert to the channel and append with prefix b
	unsigned int newByte;
	newByte = channel | 0xB0;
	
	#ifdef DEBUG
	cout << "\t\t\t\tWriting Event Control Change on channel " << hex << newByte << " Controller Number: " << controller << " to value: " << value << endl;
	#endif
	
	//write Event control Change on channel
	wb (newByte);
	//write the controller number to the file (pg 12)
	wb (controller);
	//write the value to the file
	wb (value);
}

#endif










