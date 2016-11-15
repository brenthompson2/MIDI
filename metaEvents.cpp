//	Brendan Thompson
//  metaEvents.cpp
//  11/10/16
//
//  Functions that write meta events
//  page numbers reference Standard MIDI-File Format Spec. 1.1, updated

#include "main.h"

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