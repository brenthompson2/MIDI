Andrew Ellis and Brendan Thompson Git Repo
MIDI Fall 2016 Transylvania University

**** PROJECT OUTLINE ****
main.cpp = basic functions for writing a standard midi file
    including: wb, writeVLQ, writeSMF, writeHeader, writeTrackLength, etc.
    calls writeTrackEvent from trackEvents.cpp to write individual tracks
    will contain algorithms for making chords, arpeggios, scales, etc.

channelMessages.cpp = where channel messages are written

metaEvents.cpp = where metaEvents are written

MIDIconst.h = creates a bunch of constants that make the code easier for the human to read and write

trackMelody.cpp = where a track is written. calls the individual functions to write the events for a track
	calls functions from channelMessages.cpp and metaEvents.cpp to write individual events

trackChords.cpp = where a track is written. calls the individual functions to write the events for a track
	calls functions from channelMessages.cpp and metaEvents.cpp to write individual events
	
trackDrums.cpp = where a track is written. calls the individual functions to write the events for a track
	calls functions from channelMessages.cpp and metaEvents.cpp to write individual events

**** Current Status ****
- need to read an array of bytes from the file
- in melody, output the bytes as eighth notes with one eighth note rest at the end
- in chords, output them as whole notes
- make a sick drum line irrelevant to the input file