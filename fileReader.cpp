// FILE: FileReader.cpp
// R England, Brendan Thompson, Andrew Elis Transy U
// CS 3114 MIDI, Fall 2016
//
//      Read and parse a music file in NotMIDI format
//

#include "main.h"

    unsigned trackCount;
    unsigned measureNumber;

////
/// main program
//
void fileReader (char* fileName) {
    char   buffer[BUFF_SIZE];
    
    // try to open the NotMIDI format input file for reading
    FILE  *inputFile  = fopen (fileName, "r");
    
    if (!inputFile) {
        cout << "ERROR: Couldn't open input file" << endl;
        exit (1);
    }
    
    int temp;
    
    // read each line of the input file and process it
    while ((temp = fscanf (inputFile, "%[^\n]", buffer)) != EOF) {
        if (temp) {
            // comment --- ignore
            if (buffer[0] == COMMENT_CHAR) {
                printf ("(Comment)\n");
            }
        
            // first char is a digit? then this is the start of a Note line
            else if (isdigit(buffer[0])) {
                processNote (buffer);
            }
        
            // first char is the Track count token
            else if (buffer[0] == TRACK_COUNT_CHAR) {
                processTrackCount (buffer);
            }
            
            // first char is the Measure indicator token
            else if (buffer[0] == MEASURE_CHAR) {
                processMeasureNumber (buffer);
            }
            
            // catch-all for everything else
            // (shouldn't see this message from a finished program!)
            else {
                printf ("(unknown line type: -->%s<--)\n", buffer);
            }
        }
    
        // get the '\n' out of the way
        fgetc (inputFile);
    }
    
    printf("\n\nObsv: global track count is %d, global measure number is currently %d",
           trackCount, measureNumber);
    
    printf ("\n\nDone.\n");
}

// processNote
//    process the info for a Note event line
void processNote (char buffer[]) {
    printf ("Note line: -->%s<--\n", buffer);
    
    // pick apart the pieces of a Note event line
    char   beatNumber[BUFF_SIZE];
    char   noteName[BUFF_SIZE];
    char   noteDuration[BUFF_SIZE];
    sscanf (buffer, "%s %s %s", beatNumber, noteName, noteDuration);
    
    // the beat...
    printf ("\t\tbeat: %s", beatNumber);
    processBeatNumber (beatNumber);
    
    // the note name...
    printf ("\t\tnoteName: %s", noteName);
    processNoteName (noteName);
    
    // and the duration
    printf ("\t\tnoteDuration: %s", noteDuration);
    processNoteDuration (noteDuration);
    printf ("\n");
}

// processTrackCount
//    set the global track count for the MIDI file
void processTrackCount (char buffer[]) {
    printf ("Track count line: -->%s<--", buffer);
    
    // pick apart the pieces of the track count line
    char    garbage[BUFF_SIZE];
    sscanf (buffer, "%s %u", garbage, &trackCount);
    printf ("\t(Track count is now %u)\n", trackCount);
}

// processMeasureNumber
//    set the current value for the global measure number variable
void processMeasureNumber (char buffer[]) {
    printf ("Measure number line: -->%s<--\n", buffer);

    // pick apart the pieces of the measure number line
    char    garbage[BUFF_SIZE];
    sscanf (buffer, "%s %u", garbage, &measureNumber);
    printf ("\tCurrent measure number is %u\n\n", measureNumber);
}

// processNoteName
//    parse the string representation of a note name
void processNoteName (char buffer[]) {
    bool  sharp = false, flat = false;
    unsigned noteOctaveNumber;
    
    // first char has to the be base note name (I think)
    char noteLetterName = buffer[0];
    
    // second char could be either sharp/flat or octave number
    if (isdigit (buffer[1])) {
        // second char is a number: it's the octave this note is in
        // convert it to an integer from a character
        noteOctaveNumber = buffer[1] - '0';
    }
    else {
        // second char is S or F, for Sharp or Flat
        if (buffer[1] == 'S') {
            sharp = true;
        }
        else {
            flat = true;
        }
        // ... and third char is the octave number
        noteOctaveNumber = buffer[2] - '0';
    }
    
    // print what we know about this note
    printf ("\t(That's Letter name: %c", noteLetterName);
    if (sharp) {
        printf ("-sharp");
    }
    if (flat) {
        printf ("-flat");
    }
    printf ("  octave: %u)\n", noteOctaveNumber);
}

// processNoteDuration
//    parse the string representation of a note's duration
void processNoteDuration (char buffer[]) {
    printf ("     (That's %c", buffer[0]);
    for (int i = 1; i < strlen(buffer); ++i) {
        printf (" and %c", buffer[i]);
    }
    printf (")\n");
}

// processBeatNumber
//    split the beat, man
void processBeatNumber (char buffer[]) {
    unsigned mainBeat, subBeat;
    sscanf (buffer, "%u.%u", &mainBeat, &subBeat);
    printf ("     (That's main beat %u, subbeat %u)\n", mainBeat, subBeat);
}