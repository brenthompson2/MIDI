// Brendan Thompson & Andrew Ellis
// measureList.cpp
// 12/7/16

// creates the measureList abstract data type
	// Vector
	//		list of measure objects
	// indexOfEvent = [(measureNumber * 16) + (mainBeat * 4) + subBeat]

// constructor:
MeasureList::MeasureList(void){

}

MeasureList::~MeasureList(){

}

// Accessors:
Measure MeasureList::getMeasure(int measureNum){
	Measure *tempMeasure;
	&tempMeasure = measureList<measureNum>;
	return tempMeasure;
}

// Mutators:

// create a new measure at the measureNum
void MeasureList::newMeasure(int measureNum){
	Measure *tempMeasure;
	measureList.push_back(tempMeasure);
}

// takes in a measureNum, subBeatIndex, and the newEvent
	// adds it to the measureList at the correct location
void measureList::addEvent(int measureNum, int subBeatIndex, Event newEvent){
	Measure currentMeasure;
	int numMeasures = measureList.size;
		// if the measure doesn't already exist, make it
	while (numMeasures < measureNum){
		measureList.newMeasure(numMeasures);
		numMeasures++;
	} 
	currentMeasure = measureList[measureNum];
	currentMeasure.addEvent(subBeatIndex, newEvent);
}

