// Brendan Thompson
// measureList.cpp

// creates the measureList abstract data type
	// Vector? Linked List? Dynamically allocated?
	//		list of measure objects
	// 		public int numMeasures
	// indexOfEvent = [(measureNumber * 16) + (mainBeat * 4) + subBeat]

// constructor:
	public measureList(){
		Measure measureList[BUFF_SIZE]; // HOW REPRESENT?
		int numMeasures = 0;
	}

// Accessors:


// Mutators:
	// takes in a measureNum, subBeatIndex, and the newEvent
		// adds it to the measureList at the correct location
	public measureList.addEvent(int measureNum, int subBeatIndex, EVENT newEvent){
		Measure *currentMeasure;

		&currentMeasure = measureList[measureNum];
		&currentMeasure.addEvent(subBeatIndex, newEvent);
	}

