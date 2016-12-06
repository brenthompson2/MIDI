// Brendan Thompson
// measureList.cpp

// creates the measureList abstract data type
	// Vector
	//		list of measure objects
	// indexOfEvent = [(measureNumber * 16) + (mainBeat * 4) + subBeat]

// constructor:
	public measureList(){
		Measure measureList[BUFF_SIZE]; //change to a vector
	}

// Accessors:
	MeasureList:MeasureList.getMeasure(int measureNum);

// Mutators:
	// takes in a measureNum, subBeatIndex, and the newEvent
		// adds it to the measureList at the correct location
	public measureList.addEvent(int measureNum, int subBeatIndex, EVENT newEvent){
		Measure *currentMeasure;

		&currentMeasure = measureList[measureNum];
		&currentMeasure.addEvent(subBeatIndex, newEvent);
	}

