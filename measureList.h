// Brendan Thompson & Andrew Ellis
// measureList.h
// 12/7/16

// Header file for the measureList ADT

#include main.h

#ifndef MEASURELIST_H
#define MEASURELIST_H

class MeasureList:

public:

// constructor:
	measureList();

// Accessors:
	Measure getMeasure(int measureNum);

// Mutators:

	// create a new measure at the measureNum
	void newMeasure(int measureNum);

	// takes in a measureNum, subBeatIndex, and the newEvent
		// adds the EVENT to the measureList at the correct location
	void addEvent(int measureNum, int subBeatIndex, EVENT newEvent);

private:
	Measure measureList<>;

#endif