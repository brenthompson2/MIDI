# Brendan Thompson & Andrew Ellis
# Makefile for MIDI prog7
# 12/7/16

# Main necessary to make an executable unless -c

default: 
	g++ *.cpp -o main

main: main.cpp measureList.o measure.o fileReader.o writeTrack.o main.h
	g++ -o main.o main.cpp measureList.o measure.o fileReader.o writeTrack.o

writeTrack: writeTrack.cpp main.h
	g++ -o writeTrack.o -c writeTrack.cpp

event: event.cpp
	g++ -o event.o -c event.cpp

fileReader: fileReader.cpp main.h
	g++ -o fileReader.o -c fileReader.cpp

measureList: measureList.cpp measure.o measureList.h measure.h main.h
	g++ -o measureList.o -c measureList.cpp

measure: measure.cpp measure.h main.h
	g++ -o measure.o -c measure.cpp

#removes exe and midi files
clean:
	rm prog8.mid *.o