// Brendan Thompson & Andrew Ellis
// measure.h
// 12/7/16

// Header file for the measureList ADT

#include "main.h"

#ifndef MEASURE_H
#define MEASURE_H

using namespace std;

#ifndef BEATEVENT
#define BEATEVENT
struct EVENT {
	string eventName;
	unsigned char data1;
	unsigned char data2;
	unsigned char data3;
};

struct BEAT {
	int numEvents;
	EVENT eventList[30];
};
#endif

class Measure {
public:

// Constructor:
	Measure(void);

// Accessors:
	// returns the BEAT at beatIndex
	BEAT getBeat(int beatIndex);

// Mutators:

	// adds the newEvent to the measure at beatIndex
	void addEvent(int beatIndex, EVENT newEvent);

private:
	BEAT beatArray[16];
};

#endif