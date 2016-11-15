//	Brendan Thompson
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
	unsigned long int GCOUNT = 0;
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

		unsigned int format;
	
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
		wb (format);
		
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
		wb (0x00); wb (0x00); wb (0x1a); wb (0x6b);

		writeTrackChords(noteArray, lengthArray);

		cout<<"CHORDS LENGTH: "<<hex<<GCOUNT<<endl;
		GCOUNT = 0;

	//TRACK 2
		// MTrk [4 Bytes] (pg 5)
		#ifdef DEBUG
		cout<<"\t\tWriting MTrk "<<endl;
		#endif
		wb (0x4d); wb (0x54); wb (0x72); wb (0x6b);
	
		#ifdef DEBUG
		cout<<"\t\tWriting Track Length "<<endl;
		#endif
		wb (0x00); wb (0x00); wb (0x17); wb (0x5f);

		writeTrackMelody(noteArray, lengthArray);

		cout<<"MELODY LENGTH: "<<hex<<GCOUNT<<endl;
		GCOUNT = 0;

	//TRACK 3
		// MTrk [4 Bytes] (pg 5)
		#ifdef DEBUG
		cout<<"\t\tWriting MTrk "<<endl;
		#endif
		wb (0x4d); wb (0x54); wb (0x72); wb (0x6b);
	
		#ifdef DEBUG
		cout<<"\t\tWriting Track Length "<<endl;
		#endif
		wb (0x00); wb (0x00); wb (0x22); wb (0xc0);
		
		writeTrackDrums(lengthArray);

		cout<<"DRUMS LENGTH: "<<hex<<GCOUNT<<endl;
		GCOUNT = 0;
}