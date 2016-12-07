# Brendan Thompson & Andrew Ellis
# Makefile for MIDI prog7
# 12/7/16

default: main

main: main.cpp events.cpp fileReader.cpp writeTrack.cpp measure.cpp measureList.cpp main.h MIDIconst.h
	g++ main.cpp events.cpp fileReader.cpp writeTrack.cpp measure.cpp measureList.cpp  -o main

#removes exe and midi files
clean:
	rm main prog7.mid