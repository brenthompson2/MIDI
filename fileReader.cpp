// FILE: FileReader.cpp
// R England, Brendan Thompson, Andrew Ellis Transy U
// CS 3114 MIDI, Fall 2016
//
//      Read and parse a music file from NotMIDI format into the measureList
//

#include "main.h"
#include <stdlib.h>

    unsigned trackCount;
    unsigned measureNumber;

////
/// main program
//
void fileReader () {
    char buffer[BUFF_SIZE];
    char* fileName;
    int temp;

    // try to open the NotMIDI format input file for reading
    cout<<"What notMIDI file would you like to import?";
    scanf("%[^\n]", fileName);
    FILE  *inputFile  = fopen (fileName, "r");
    if (!inputFile) {
        cout << "ERROR: Couldn't open input file" << endl;
        exit (1);
    }
    
    // read each line of the input file and process it
    while ((temp = fscanf (inputFile, "%[^\n]", buffer)) != EOF) {
        if (temp) {
            // comment --- ignore
            if (buffer[0] == COMMENT_CHAR) {
                #ifdef DEBUG
                printf ("(Comment)\n");
                #endif
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
                printf ("(ERROR: unknown line type: -->%s<--)\n", buffer);
                exit(1);
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
//    process the info for a Note event line and put it in the 
void processNote(char buffer[]) {
    int beatIndex, beatIndexOff;
    unsigned char noteNumber;

    #ifdef DEBUG
        printf("Note line: -->%s<--\n", buffer);
    #endif

    // pick apart the pieces of a Note event line
    char   beatNumber[SMALL_BUFF_SIZE];
    char   noteName[SMALL_BUFF_SIZE];
    char   noteDuration[SMALL_BUFF_SIZE];
    sscanf (buffer, "%s %s %s", beatNumber, noteName, noteDuration);

    // the beat...
    beatIndex = processBeatNumber(beatNumber);
    
    // the note name...
    noteNumber = processNoteName(noteName);
    
    // and the duration
    beatIndexOff = processNoteDuration(noteDuration);
    printf ("\n");

    // add the noteOn event to measureList
    EVENT noteOnEvent;
    noteOnEvent.eventName = "noteOn";
    noteOnEvent.data1 = noteNumber;
    measureList.addEvent(measureNumber, beatIndex, noteOnEvent);

    // add the noteOff event to meaureList
    EVENT noteOffEvent;
    noteOffEvent.eventName = "noteOff";
    noteOffEvent.data1 = noteNumber;
    measureList.addEvent(measureNumber, beatIndexOff, noteOffEvent);
}

// processTrackCount
//    set the global track count for the MIDI file
//    how create another measureList for new track
void processTrackCount(char buffer[]) {
    // pick apart the pieces of the track count line
    char    garbage[SMALL_BUFF_SIZE];
    sscanf (buffer, "%s %u", garbage, &trackCount);

    #ifdef DEBUG
        printf ("Track count line: -->%s<--", buffer);
        printf ("\t(Track count is now %u)\n", trackCount);
    #endif  
}

// processMeasureNumber
//    set the current value for the global measure number variable
void processMeasureNumber (char buffer[]) {
    printf ("Measure number line: -->%s<--\n", buffer);

    // pick apart the pieces of the measure number line
    char    garbage[SMALL_BUFF_SIZE];
    sscanf (buffer, "%s %u", garbage, &measureNumber);
    printf ("\tCurrent measure number is %u\n\n", measureNumber);

    measureList.newMeasure(measureNumber);
}

// processNoteName
//    parse the string representation of a note name and return the MIDI note number
int processNoteName (char buffer[]) {
    bool  sharp = false, flat = false;
    unsigned noteOctaveNumber;

    int noteNumber;
    int letterMultiplier;
    
    // first char has to the be base note name (I think)
    char noteLetterName = buffer[0];
    letterMultiplier = noteLetterName - 'A'; // A = 0, B = 1, C = 2, D = 3, E = 4, F = 5, G = 6
    switch (letterMultiplier){
        case 0 : letterMultiplier = letterMultiplier + 9; // A = 9
        case 1 : letterMultiplier = letterMultiplier + 10; // B = 11
        case 2 : letterMultiplier = letterMultiplier - 2; // C = 0
        case 3 : letterMultiplier = letterMultiplier - 1; // D = 2
        case 4 : letterMultiplier; // E = 4
        case 5 : letterMultiplier; // F = 5
        case 6 : letterMultiplier = letterMultiplier + 1; // G = 7
    }

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

    // convert all of the data into a note number
    noteNumber = (letterMultiplier + (noteOctaveNumber * 12));

    
    #ifdef DEBUG
        // print what we know about this note
        printf ("\t(That's Letter name: %c", noteLetterName);
        if (sharp) {
            printf ("-sharp");
        }
        if (flat) {
            printf ("-flat");
        }
        printf ("  octave: %u)\n", noteOctaveNumber);
        printf ("  noteNumber: %d)\n", noteNumber);
    #endif

    return noteNumber;
}

// processNoteDuration
//    parse the string representation of a note's duration
int processNoteDuration (char buffer[]) {
    int beatIndexOff;
    printf ("     (That's %c", buffer[0]);
    for (int i = 1; i < strlen(buffer); ++i) {
        printf (" and %c", buffer[i]);
    }
    printf (")\n");

    beatIndexOff = 4;

    return beatIndexOff;
}

// processBeatNumber
//    split the beat into main and sub and then calculate the beatNumber
int processBeatNumber (char buffer[]) {
    int beatNumber;
    unsigned int mainBeat, subBeat;
    sscanf (buffer, "%u.%u", &mainBeat, &subBeat);
    beatNumber = ((mainBeat * 4) + subBeat);
    return beatNumber;
    printf ("     (MainBeat %u and subBeat %u is MeasureIndex %d)\n", mainBeat, subBeat, beatNumber);
}