main.cpp                                                                                            0000775 0001750 0001750 00000013154 13012757263 007446                                                                                                                                                                               0000000 0000000                                                                                                                                                                        //	Brendan Thompson
//  main.cpp
//  prog7
//  11/15/16
//   
//  Read in a file and output it as MIDI song
//  page numbers reference Standard MIDI-File Format Spec. 1.1, updated

#include "main.h"

//Global Declarations
#ifndef GLOBAL
#define GLOBAL
	unsigned long int GCOUNT;
	ofstream globalOutputFile;
	ifstream globalInputFile;
	unsigned char noteArray[MAXARRAYSIZE];
	unsigned int lengthArray;
	unsigned char division;
	unsigned char numTracks;
#endif

int main() {
	
	string fileName;
	
	#ifdef DEBUG
	cout<< "Attempting to write MIDI file prog7.mid..."<< endl;
	#endif
	
	//attempt to open globalOutputFile	
	globalOutputFile.open("prog7.mid", ios::binary);
	if (!globalOutputFile)
	{
		cerr<< "Can't open prog7.mid; aborting." <<endl;
		return 0;
	}
	
	//attempt to open globalInputFile
	cout<<"What file would you like to read in? ";
	cin>>fileName;	
    cout << endl << "Attempting to read in file: " << fileName << " ..." << endl;
    globalInputFile.open(fileName.c_str(), ios::binary);
    if (!globalInputFile) {
        cerr << "Can't open " << fileName << " for input; aborting." << endl;
        return 0;
    }

    //populate the noteArray
    rb();

	writeSMF ();	
	
	globalInputFile.close();
	globalOutputFile.close();

	#ifdef DEBUG
	cout<< "Done with prog7.mid" <<endl;
	#endif
	
	//system ("Pause");
	return 0;
}


// *** Function Definitions ****

// wb = takes in a single Byte Hex value and prints it to the output file
void wb (unsigned value) {
	globalOutputFile<< char(value);
	GCOUNT++;
}

// rb = reads values from a file, converts them to notes between C3 and B5,
	// and puts the notes into an array 
void rb (){
	unsigned char value;

	lengthArray = 0;

	for(int i = 0; i < MAXARRAYSIZE; i++){
		globalInputFile>> hex>> value;
		#ifdef DEBUG
		cout<<"\t\tRB = "<< char(value)<<endl;
		#endif
		if (globalInputFile.eof()){ break;}

		value = (int(value) % 35) + 48;

		noteArray[i] = value;

		lengthArray = i;
	}
}

// writeEventDeltaTime (numTicks) = takes in a hex value and writes it as a VLQ to the file
void writeEventDeltaTime (unsigned int numTicks) {
	#ifdef DEBUG
	cout<<"\t\t\tWriting Delta Time = "<<numTicks<<endl;
	#endif
	
	writeVLQ (numTicks);
}

// writeVLQ = takes in a hex value and writes the converted array of VLQ Bytes to the file
void writeVLQ (unsigned int hexNum)
{
	#ifdef DEBUG
	//cout<<" Writing VLQ to the file "<<endl;
	#endif
	
	unsigned int numCopy, backVLQ[5];
	int i, length;
	length =1;
	numCopy = hexNum;
	
	//puts first 7 digits into array backVLQ & flag
	backVLQ[length] = numCopy & 0x7F;
		//cout<<"The first two places are: "<<hex<<backVLQ[length]<<endl;
	numCopy = numCopy>>7;
	
	 //While numCopy still has a value, get the next 7 and OR for the flag bit
	 while (numCopy > 0)
	 {
		length++;
		backVLQ[length] = numCopy & 0x7F;
		backVLQ[length] = backVLQ[length] | 0x80;
		numCopy = numCopy>>7;
			 //cout<<hex<<backVLQ[length]<<" "<<dec<<length<<endl;
	 }
	
	//write the VLQ array to the file
	//cout<<"The VLQ equivalent is: ";
	for (i=length; i > 0; i--)
	{
		//cout<<setfill('0')<<setw(2)<<hex<<(int)backVLQ[i]<<" ";
		wb (backVLQ[i]);
	}
	//cout<<endl<<"It has a length of: "<<dec<<length<<endl;
}

// writeSMF = calls the functions to write an entire Standard MIDI File 
void writeSMF () {
	#ifdef DEBUG
	cout<<"Writing Standard MIDI File "<<endl;
	#endif
	
	writeHeadChunk ();
	writeTrackChunk ();
}

// writeHeadChunk = calls the functions to write an entire header chunk to a file
void writeHeadChunk () {
	#ifdef DEBUG
	cout<<"\tWriting Head Chunk "<<endl;
	#endif

		unsigned format;
	
		//MThd [4 bytes] (pg 3)
		#ifdef DEBUG
		cout<<"\t\tWriting MThd "<<endl;
		#endif
		wb (0x4d); wb (0x54); wb (0x68); wb (0x64);
		
		//Head Length = always 0x 00 00 00 06 [4 bytes] (pg 3)
		#ifdef DEBUG
		cout<<"\t\tWriting HeadLength"<<endl;
		#endif	
		wb (0x00); wb (0x00); wb (0x00); wb (0x06);
	
		format = 1;
		#ifdef DEBUG
		cout<<"\t\tWriting Head Format: "<< format <<endl;
		#endif
		wb (0x00); wb (format);
		
		numTracks = 3;
		#ifdef DEBUG
		cout<<"\t\tWriting NTracks = "<<hex<<numTracks<<endl;
		#endif
		wb (0x00); wb (numTracks);
		
		#ifdef DEBUG
		cout<<"\t\tWriting Division "<<endl;
		#endif		
		wb (0x00); wb (0x60); 
}

// writeTrackChunk = calls the functions to write an entire track chunk to a file (pg 5)
void writeTrackChunk () {

	#ifdef DEBUG
	cout<<"\tWriting Track Chunk "<<endl;
	#endif
	
	//TRACK 1
		// MTrk [4 Bytes] (pg 5)
		#ifdef DEBUG
		cout<<"\t\tWriting MTrk "<<endl;
		#endif
		wb (0x4d); wb (0x54); wb (0x72); wb (0x6b);
	
		#ifdef DEBUG
		cout<<"\t\tWriting Track Length "<<endl;
		#endif
		wb (0x00); wb (0x00); wb (0x18); wb (0x64);

		GCOUNT = 0;

		writeTrackChords(noteArray, lengthArray);

		cout<<"CHORDS LENGTH: "<<hex<<GCOUNT<<endl;

	//TRACK 2
		// MTrk [4 Bytes] (pg 5)
		#ifdef DEBUG
		cout<<"\t\tWriting MTrk "<<endl;
		#endif
		wb (0x4d); wb (0x54); wb (0x72); wb (0x6b);
	
		#ifdef DEBUG
		cout<<"\t\tWriting Track Length "<<endl;
		#endif
		wb (0x00); wb (0x00); wb (0x17); wb (0x3b);

		GCOUNT = 0;

		writeTrackMelody(noteArray, lengthArray);

		cout<<"MELODY LENGTH: "<<hex<<GCOUNT<<endl;

	//TRACK 3
		// MTrk [4 Bytes] (pg 5)
		#ifdef DEBUG
		cout<<"\t\tWriting MTrk "<<endl;
		#endif
		wb (0x4d); wb (0x54); wb (0x72); wb (0x6b);
	
		#ifdef DEBUG
		cout<<"\t\tWriting Track Length "<<endl;
		#endif
		wb (0x00); wb (0x00); wb (0x22); wb (0xb8);
		
		GCOUNT = 0;
		
		writeTrackDrums(lengthArray);

		cout<<"DRUMS LENGTH: "<<hex<<GCOUNT<<endl;
}                                                                                                                                                                                                                                                                                                                                                                                                                    metaEvents.cpp                                                                                      0000775 0001750 0001750 00000001577 13012665144 010637                                                                                                                                                                               0000000 0000000                                                                                                                                                                        //	Brendan Thompson
//  metaEvents.cpp
//  11/15/16
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
}                                                                                                                                 trackChords.cpp                                                                                     0000775 0001750 0001750 00000005120 13012763031 010751                                                                                                                                                                               0000000 0000000                                                                                                                                                                        //	Brendan Thompson
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
}                                                                                                                                                                                                                                                                                                                                                                                                                                                trackDrums.cpp                                                                                      0000775 0001750 0001750 00000005222 13012757153 010634                                                                                                                                                                               0000000 0000000                                                                                                                                                                        //	Brendan Thompson
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
			noteOn(CHANNEL_10, 0x23, 0x60);

			writeEventDeltaTime (0x60);
			noteOn(CHANNEL_10, 0x23, 0x60);
		}

	// Pattern 2: Bass on the beat, snare on the AND
		for (i; i < (lengthArray/2); i++) {
			writeEventDeltaTime (0x00);
			noteOn(CHANNEL_10, 0x23, 0x60);
			writeEventDeltaTime (0x30);
			noteOff(CHANNEL_10, 0x2D, 0x60);

			writeEventDeltaTime (0x00);
			noteOn(CHANNEL_10, 0x23, 0x30);
			writeEventDeltaTime (0x30);
			noteOff(CHANNEL_10, 0x2D, 0x60);

			writeEventDeltaTime (0x00);
			noteOn(CHANNEL_10, 0x23, 0x30);
			writeEventDeltaTime (0x30);
			noteOff(CHANNEL_10, 0x2D, 0x60);

			writeEventDeltaTime (0x00);
			noteOn(CHANNEL_10, 0x23, 0x30);
			writeEventDeltaTime (0x30);
			noteOff(CHANNEL_10, 0x2D, 0x60);
		}

	// Pattern 3: Bass on the beat, snare on the AND, clap on 2 4
		for (i; i < lengthArray; i++) {
			writeEventDeltaTime (0x00);
			noteOn(CHANNEL_10, 0x23, 0x60);
			writeEventDeltaTime (0x30);
			noteOff(CHANNEL_10, 0x2D, 0x60);

			writeEventDeltaTime (0x30);
			noteOn(CHANNEL_10, 0x23, 0x60);
			writeEventDeltaTime (0x00);
			noteOn(CHANNEL_10, 0x27, 0x60);
			writeEventDeltaTime (0x30);
			noteOff(CHANNEL_10, 0x2D, 0x60);

			writeEventDeltaTime (0x30);
			noteOn(CHANNEL_10, 0x23, 0x60);
			writeEventDeltaTime (0x30);
			noteOff(CHANNEL_10, 0x2D, 0x60);

			writeEventDeltaTime (0x30);
			noteOn(CHANNEL_10, 0x23, 0x60);
			writeEventDeltaTime (0x00);
			noteOn(CHANNEL_10, 0x27, 0x60);
			writeEventDeltaTime (0x30);
			noteOff(CHANNEL_10, 0x2D, 0x60);
		}

	//event8: 81 50 b0 7b 00 = at delta decimal 208 - control change - all notes off 
		writeEventDeltaTime (0xd0); //time = VLQ 81 50 = 0xd0 = decimal 208 
		controlChange (CHANNEL_10, 0x7b, 0x00);
			// turn off all notes on channel 10 (pg 10, 15)
			
	//event9: 00 ff 2f 00 = end of track
		writeEventDeltaTime (0x00);
		metaEndOfTrack ();
}                                                                                                                                                                                                                                                                                                                                                                              trackMelody.cpp                                                                                     0000775 0001750 0001750 00000010235 13012751032 010761                                                                                                                                                                               0000000 0000000                                                                                                                                                                        //	Brendan Thompson
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
		programChange (CHANNEL_1, 0x00); // new program = 0x0b = decimal 1 = (pg 17)
	
	//Pattern 1: for the first 4 measures, output them sequentially as Half notes
		i = 0; 
		for (i; i < 8; i++){
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
	writeEventDeltaTime (0x18); // time = 32
	noteOff (CHANNEL_1, root, volume); 

	//turn note on
	writeEventDeltaTime (0x00); // time = 0
	noteOn (CHANNEL_1, second, volume);

	//turn note off	
	writeEventDeltaTime (0x18); // time = 32
	noteOff (CHANNEL_1, second, volume); 

	//turn note on
	writeEventDeltaTime (0x00); // time = 0
	noteOn (CHANNEL_1, third, volume);

	//turn note off	
	writeEventDeltaTime (0x18); // time = 32
	noteOff (CHANNEL_1, third, volume); 

	//turn note on
	writeEventDeltaTime (0x00); // time = 0
	noteOn (CHANNEL_1, fourth, volume);

	//turn note off	
	writeEventDeltaTime (0x18); // time = 32
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
}                                                                                                                                                                                                                                                                                                                                                                   main.h                                                                                              0000775 0001750 0001750 00000005344 13012740237 007106                                                                                                                                                                               0000000 0000000                                                                                                                                                                        //	Brendan Thompson
//  main.h
//  11/15/16
//
//  Basic Header for writing a midi file. 
//  page numbers reference Standard MIDI-File Format Spec. 1.1, updated

#ifndef    MAIN_H
#define    MAIN_H

// #define DEBUG

#define MAXARRAYSIZE 250

#include <iostream>
#include <fstream>
#include <iomanip>
#include "MIDIconst.h"
using namespace std;


// *** Main Function Declarations ****

	// write byte = takes in a Hex value and prints it to the output file
	void wb (unsigned value);
		
	// rb = reads values from a file, converts them to notes between C3 and B5,
		// and puts the notes into an array 
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
	void writeTrackMelody (unsigned char noteArray[], int lengthArray);
	void makeMajorScale(unsigned char channel, unsigned char root, unsigned int volume);

	//writeTrackChords
	void writeTrackChords (unsigned char noteArray[], int lengthArray);
	void makeMajorChord (unsigned char channel, unsigned char root, unsigned int volume, unsigned int noteLength);

	//writeTrackDrums = write track events for the drums to the file
	void writeTrackDrums (int lengthArray);

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
                                                                                                                                                                                                                                                                                            MIDIconst.h                                                                                         0000755 0001750 0001750 00000010524 13011122013 007726                                                                                                                                                                               0000000 0000000                                                                                                                                                                        // FILE: MIDIconst.h
// CS 3114, Fall 2016
// R England, Transy U
//
// EDITED 10/27/16 by BRENDAN THOMPSON
//
//   Various symbolic constants that may be useful in generating
//      Standard MIDI Files
//
#ifndef MIDICONST_H
#define MIDICONST_H

const unsigned char CHANNEL_1 = 0x00;
const unsigned char CHANNEL_2 = 0x01;
const unsigned char CHANNEL_3 = 0x02;
const unsigned char CHANNEL_4 = 0x03;
const unsigned char CHANNEL_5 = 0x04;
const unsigned char CHANNEL_6 = 0x05;
const unsigned char CHANNEL_7 = 0x06;
const unsigned char CHANNEL_8 = 0x07;
const unsigned char CHANNEL_9 = 0x08;
const unsigned char CHANNEL_10 = 0x09;
const unsigned char CHANNEL_11 = 0x0A;
const unsigned char CHANNEL_12 = 0x0B;
const unsigned char CHANNEL_13 = 0x0C;
const unsigned char CHANNEL_14 = 0x0D;
const unsigned char CHANNEL_15 = 0x0E;
const unsigned char CHANNEL_16 = 0x0F;

const unsigned char C0 = 12;
const unsigned char Cs0 = 13;
const unsigned char D0 = 14;
const unsigned char Ds0 = 15;
const unsigned char E0 = 16;
const unsigned char F0 = 17;
const unsigned char Fs0 = 18;
const unsigned char G0 = 19;
const unsigned char Gs0 = 20;
const unsigned char A0 = 21;
const unsigned char As0 = 22;
const unsigned char B0 = 23;

const unsigned char C1 = 24;
const unsigned char Cs1 = 25;
const unsigned char D1 = 26;
const unsigned char Ds1 = 27;
const unsigned char E1 = 28;
const unsigned char F1 = 29;
const unsigned char Fs1 = 30;
const unsigned char G1 = 31;
const unsigned char Gs1 = 32;
const unsigned char A1 = 33;
const unsigned char As1 = 34;
const unsigned char B1 = 35;

const unsigned char C2 = 36;
const unsigned char Cs2 = 37;
const unsigned char D2 = 38;
const unsigned char Ds2 = 39;
const unsigned char E2 = 40;
const unsigned char F2 = 41;
const unsigned char Fs2 = 42;
const unsigned char G2 = 43;
const unsigned char Gs2 = 44;
const unsigned char A2 = 45;
const unsigned char As2 = 46;
const unsigned char B2 = 47;

const unsigned char C3 = 48;
const unsigned char Cs3 = 49;
const unsigned char D3 = 50;
const unsigned char Ds3 = 51;
const unsigned char E3 = 52;
const unsigned char F3 = 53;
const unsigned char Fs3 = 54;
const unsigned char G3 = 55;
const unsigned char Gs3 = 56;
const unsigned char A3 = 57;
const unsigned char As3 = 58;
const unsigned char B3 = 59;

const unsigned char C4 = 60;
const unsigned char Cs4 = 61;
const unsigned char D4 = 62;
const unsigned char Ds4 = 63;
const unsigned char E4 = 64;
const unsigned char F4 = 65;
const unsigned char Fs4 = 66;
const unsigned char G4 = 67;
const unsigned char Gs4 = 68;
const unsigned char A4 = 69;
const unsigned char As4 = 70;
const unsigned char B4 = 71;

const unsigned char C5 = 72;
const unsigned char Cs5 = 73;
const unsigned char D5 = 74;
const unsigned char Ds5 = 75;
const unsigned char E5 = 76;
const unsigned char F5 = 77;
const unsigned char Fs5 = 78;
const unsigned char G5 = 79;
const unsigned char Gs5 = 80;
const unsigned char A5 = 81;
const unsigned char As5 = 82;
const unsigned char B5 = 83;

const unsigned char C6 = 84;
const unsigned char Cs6 = 85;
const unsigned char D6 = 86;
const unsigned char Ds6 = 87;
const unsigned char E6 = 88;
const unsigned char F6 = 89;
const unsigned char Fs6 = 90;
const unsigned char G6 = 91;
const unsigned char Gs6 = 92;
const unsigned char A6 = 93;
const unsigned char As6 = 94;
const unsigned char B6 = 95;

const unsigned char C7 = 96;
const unsigned char Cs7 = 97;
const unsigned char D7 = 98;
const unsigned char Ds7 = 99;
const unsigned char E7 = 100;
const unsigned char F7 = 101;
const unsigned char Fs7 = 102;
const unsigned char G7 = 103;
const unsigned char Gs7 = 104;
const unsigned char A7 = 105;
const unsigned char As7 = 106;
const unsigned char B7 = 107;

const unsigned char C8 = 108;
const unsigned char Cs8 = 109;
const unsigned char D8 = 110;
const unsigned char Ds8 = 111;
const unsigned char E8 = 112;
const unsigned char F8 = 113;
const unsigned char Fs8 = 114;
const unsigned char G8 = 115;
const unsigned char Gs8 = 116;
const unsigned char A8 = 117;
const unsigned char As8 = 118;
const unsigned char B8 = 119;

const unsigned char C9 = 120;
const unsigned char Cs9 = 121;
const unsigned char D9 = 122;
const unsigned char Ds9 = 123;
const unsigned char E9 = 124;
const unsigned char F9 = 125;
const unsigned char Fs9 = 126;
const unsigned char G9 = 127;

const unsigned char VOL_LOUD = 0x7F;
const unsigned char VOL_MEDIUM = 0x60;
const unsigned char VOL_SOFT = 0x30;


#endif
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            