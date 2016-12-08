// Brendan Thompson & Andrew Ellis
// measureList.h
// 12/7/16

// Header file for the measureList ADT

//#include "main.h"

#ifndef MEASURELIST_H
#define MEASURELIST_H

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

class MeasureList{

public:

// constructor:
	MeasureList();

	~MeasureList();

// Accessors:
	Measure getMeasure(int measureNum);
	int getSize();

// Mutators:

	// create a new measure at the measureNum
	void newMeasure(int measureNum);

	// takes in a measureNum, subBeatIndex, and the newEvent
		// adds the EVENT to the measureList at the correct location
	void addEvent(int measureNum, int subBeatIndex, EVENT newEvent);

private:
	vector<Measure> measureList;

};



#endif