// Brendan Thompson & Andrew Ellis
// Measure.cpp
// 12/7/16

// creates one measure object, 
	// represented as a measureArray of 15 Beat elements
	// Accessors:
		// getBeat(int subBeatIndex)
	// Mutators:
		// addEvent(int subBeatIndex, Event newEvent)

#include "main.h"

// Constructor:
	Measure::Measure(){
		Beat beatArray[15];
		for (int i = 0; i < 15; i++){
			beatArray[i] = new Beat;
		}
	}

// Accessors:
	// returns a pointer to the Beat at subBeatIndex
	Beat *Measure::getBeat(int subBeatIndex){
		Beat *currentBeat;

		&currentBeat = beatArray[subBeatIndex];
		
		return currentBeat;
	}

// Mutators:
	// adds the newEvent to the measure 
	void Measure::addEvent(int subBeatIndex, Event newEvent){
		Beat currentBeat;
		int eventIndex;

		currentBeat = beatArray[subBeatIndex];
		eventIndex = currentBeat.numEvents++;
		
		currentBeat.eventList[eventIndex] = newEvent;
	}

