// Brendan Thompson & Andrew Ellis
// Measure.cpp
// 12/7/16

// creates one measure object, 
	// represented as a measureArray of 15 BEAT elements
	// Accessors:
		// getBeat(int subBeatIndex)
	// Mutators:
		// addEvent(int subBeatIndex, EVENT newEvent)

#include "main.h"

// Constructor:
	Measure::Measure(){
		BEAT beatArray[15];
		for (int i = 0; i < 15; i++){
			BEAT newBeat;
			beatArray[i] = newBeat;
		}
	}

// Accessors:
	// returns the BEAT at subBeatIndex
	BEAT Measure::getBeat(int subBeatIndex){
		BEAT currentBeat;

		currentBeat = beatArray[subBeatIndex];
		
		return currentBeat;
	}

// Mutators:
	// adds the newEvent to the measure 
	void Measure::addEvent(int subBeatIndex, EVENT newEvent){
		BEAT currentBeat;
		int eventIndex;

		currentBeat = beatArray[subBeatIndex];
		eventIndex = currentBeat.numEvents++;
		
		currentBeat.eventList[eventIndex] = newEvent;
	}

