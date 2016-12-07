//	Brendan Thompson
//  events.cpp
//  11/10/16
//
//  Functions that write Channel Messages and Meta Events events
//  page numbers reference Standard MIDI-File Format Spec. 1.1, updated

#ifndef    events_H
#define    events_H

#include "main.h"

// **** CHANNEL MESSAGE DEFINITIONS ****

// note on = 9channel = turn on note on channel at volume
void noteOn (unsigned char channel, unsigned char note, unsigned int volume)
{
	
	//convert to the channel and append with prefix 9
	unsigned int newByte;
	newByte = channel | 0x90;

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
	
	//convert to the channel and append with prefix 8
	unsigned int newByte;
	newByte = channel | 0x80;
	
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

// **** META EVENT DEFINITIONS ****

// metaEndOfTrack = FF 2f 00 = writes end of track to the file
void metaEndOfTrack ()
{
	#ifdef DEBUG
	cout << "\t\t\t\tWriting End of Track to file " << endl;
	#endif
	
	wb (0xff); wb (0x2f); wb (0x00);
}

// metaSetTempo = FF 51 03 = takes in the three bytes to set the tempo to and writes the event to the file (pg 8)
void metaSetTempo (unsigned int a, unsigned int b, unsigned int c)
{
	#ifdef DEBUG
	cout << "\t\t\t\tWriting Meta Event Set Tempo to: " << hex << a << " " << b << " " << c << endl;
	#endif
	
	//write Meta Event Type Set Tempo
	wb (0xFF); wb (0x51); wb (0x03);
	//write the new tempo to the file
	wb (a); wb (b); wb (c);
}

#endif










