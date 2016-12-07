// Brendan Thompson & Andrew Ellis
// measure.h
// 12/7/16

// Header file for the measureList ADT

#include main.h

#ifndef MEASURE_H
#define MEASURE_H

class Measure {
public:

// Constructor:
	measure(void);

// Accessors:
	// returns a pointer to the BEAT at beatIndex
	BEAT getBeat(int beatIndex);

// Mutators:

	// adds the newEvent to the measure at beatIndex
	void addEvent(int beatIndex, EVENT newEvent);

private:
	BEAT beatArray[16];


#endif