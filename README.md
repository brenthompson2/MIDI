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

