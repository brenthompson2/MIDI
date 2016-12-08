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
struct Event {
	string eventName;
	unsigned char data1;
	unsigned char data2;
	unsigned char data3;
};

struct Beat {
	int numEvents;
	Event eventList[30];
};
#endif

class Measure {
public:

// Constructor:
	Measure(void);

// Accessors:
	// returns a pointer to the Beat at beatIndex
	Beat getBeat(int beatIndex);

// Mutators:

	// adds the newEvent to the measure at beatIndex
	void addEvent(int beatIndex, Event newEvent);

private:
	Beat beatArray[16];
};

#endif