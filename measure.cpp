// Brendan Thompson
// Measure.cpp

// creates one measure object, 
	// represented as a measureArray of 15 BEAT elements
	// Accessors:
		// getBeat(int subBeatIndex)
	// Mutators:
		// addEvent(int subBeatIndex, EVENT newEvent)

#include "main.h"

// Constructor:
	public Measure(){
		BEAT beatArray[15];
		for (int i = 0; i < 15; i++){
			beatArray[i] = new Beat();
		}
	}

// Accessors:
	// returns a pointer to the BEAT at subBeatIndex
	public BEAT *Measure.getBeat(int subBeatIndex){
		BEAT *currentBeat;

		&currentBeat = beatArray[subBeatIndex];
		
		return currentBeat;
	}

// Mutators:
	// adds the newEvent to the measure 
	public void Measure.addEvent(int subBeatIndex, EVENT newEvent){
		BEAT *currentBeat;
		int eventIndex;

		&currentBeat = beatArray[subBeatIndex];
		eventIndex = &currentBeat.numEvents++;
		

		&currentBeat.eventList[eventIndex] = newEvent;
	}

