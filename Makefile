# Brendan Thompson 
# Makefile for MIDI prog7
# 11/10/16

# -Wall = extra warning messages

default: main

main: main.cpp trackChords.cpp trackMelody.cpp trackDrums.cpp metaEvents.cpp channelMessages.cpp fileReader.cpp main.h MIDIconst.h
	g++ fileReader.cpp main.cpp trackChords.cpp trackMelody.cpp trackDrums.cpp metaEvents.cpp channelMessages.cpp -o main

#new: main.o trackDrums.o trackMelody.o trackChords.o metaEvents.o channelMessages.o
#	g++ -o new main.o trackDrums.o trackMelody.o trackChords.o channelMessages.o metaEvents.o 

#main.o: main.cpp main.h MIDIconst.h
# 	g++ -Wall -c main.cpp

#trackDrums.o: trackDrums.cpp main.h MIDIconst.h
#	g++ -Wall -c trackDrums.cpp

#trackMelody.o: trackMelody.cpp main.h MIDIconst.h
#	g++ -Wall -c trackMelody.cpp
	
#trackChords.o: trackChords.cpp main.h MIDIconst.h
#	g++ -Wall -c trackChords.cpp

#channelMessages.o: channelMessages.cpp main.h MIDIconst.h
#	g++ -Wall -c channelMessages.cpp
	
#metaEvents.o: metaEvents.cpp main.h MIDIconst.h
#	g++ -Wall -c metaEvents.cpp

#removes exe and object files
clean:
	rm main prog7.mid
	
# g++ main.cpp trackEvents.cpp metaEvents.cpp channelMessages.cpp -o main
# ./main

