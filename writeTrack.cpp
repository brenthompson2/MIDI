//	Brendan Thompson & Andrew Ellis
//  writeTrack.cpp
//  12/7/16
//
//  Takes in a measureList and outputs it as a MIDI file
//  page numbers reference Standard MIDI-File Format Spec. 1.1, updated

#include "main.h"

// writeTrack = takes in a measureList and writes it as a MIDI track event to the file
void writeTrack (MeasureList measureList) {
	#ifdef DEBUG
		cout<<"\t\tWriting Track"<<endl;
	#endif
	int measureCounter = 0;


	// Set Tempo: 00 ff 51 03 0f 42 40 == at delta 0 - set tempo - to hex 0f4240
		writeEventDeltaTime (0x00); // time = 0
		metaSetTempo (0x0f, 0x42, 0x40); // new tempo = decimal 1000000 microseconds per quarter note = 1 second per quarter note

	// Set Instrument: 00 c0 0b = at delta 0 - set program of channel 1 - to program decimal 1, the Basic Piano
		writeEventDeltaTime (0x00); // time = 0
		programChange(0x00);

	// Write measureList to MIDI file
	// for every MEASURE in the song
	for (measureCounter; measureCounter < measureList.size(); measureCounter++){
		int currentMeasure = measureList.getMeasure(measureCounter);
		int beatCounter = 0;

		// for every BEAT in the measure
		for (beatCounter; beatCounter < 16; beatCounter++){
			BEAT curentBeat = currentMeasure.getBeat(beatCounter);
			int eventCounter = 0;
			// imaginary noteOn event to make all deltaTimes for rest of BEAT 0
			writeEventDeltaTime(SIXTEENTH_DELTA);
			noteOn(CHANNEL_1, 0x00, 0x00);

			// for every EVENT in the BEAT
			for (eventCounter; eventCounter < curentBeat.numEvents; eventCounter++){
				EVENT currentEvent = curentBeat.eventList[eventCounter];
				processEvent(currentEvent);
			}
		}
	}	

	// All Notes Off: 81 50 b0 7b 00 = at delta decimal 208 - control change - all notes off 
		writeEventDeltaTime (0xd0); //time = VLQ 81 50 = 0xd0 = decimal 208 
		controlChange (CHANNEL_1, 0x7b, 0x00);
			// turn off all notes on channel 1 (pg 10, 15)
			
	// End of Track: 00 ff 2f 00 = end of track
		writeEventDeltaTime (0x00); // time = 0
		metaEndOfTrack ();
}

void processEvent(EVENT currentEvent){
	if (currentEvent.eventName == "noteOn"){
		writeEventDeltaTime (0x00);
		noteOn(CHANNEL_1, currentEvent.data1, VOL_MEDIUM);
	}
	if (currentEvent.eventName == "noteOff"){
		writeEventDeltaTime (0x00);
		noteOff(CHANNEL_1, currentEvent.data1, VOL_MEDIUM);
	}
}