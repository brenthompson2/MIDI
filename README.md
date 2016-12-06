Andrew Ellis and Brendan Thompson Git Repo
MIDI Fall 2016 Transylvania University

**** GIT Instructions ****

To pull from repo:
	git fetch
	get pull

To push to repo:
	git add <files>
	git commit -m "<commit message>"
	git fetch
	git pull
	<manual merge if necessary>
		if merge, then re do add and commit
	git push

**** PROJECT OUTLINE ****
main.cpp = basic functions for writing a standard midi file
    including: wb, writeVLQ, writeSMF, writeHeader, etc.
    calls writeTrackEvent from trackMelody.cpp to write individual tracks

channelMessages.cpp = where channel messages are written
metaEvents.cpp = where metaEvents are written
MIDIconst.h = creates a bunch of constants that make the MIDI code easier for the human to read and write

trackMelody.cpp = where the measureList will be translated into the MIDI file

fileReader.cpp = where the notMIDI file will be read into the measureList

measureList.cpp = Implementation for measureList ADT
	represented with a measureList and numMeasures

measure.cpp = Implementation of measure ADT
	represented with an array of 16 BEAT elements

BEAT = represented as a Struct of numEvents and an eventArray of 10 EVENT elements

EVENT = represented as a Struct with eventName and 3 data variables



