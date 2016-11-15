# Brendan Thompson 
# Makefile for MIDI prog7
# 11/10/16

# -Wall = extra warning messages

default: main

main: main.cpp main.h MIDIconst.h
	g++ main.cpp trackChords.cpp trackMelody.cpp trackDrums.cpp metaEvents.cpp channelMessages.cpp -o main

# main.o: main.cpp main.h MIDIconst.h
# 	g++ -Wall -o main.o main.cpp

# trackEvents.o: trackEvents.cpp main.h MIDIconst.h
# 	g++ -Wall -o trackEvents.o trackEvents.cpp
	
# channelMessages.o: channelMessages.cpp main.h MIDIconst.h
# 	g++ -Wall -o channelMessages.o channelMessages.cpp
	
# metaEvents.o: metaEvents.cpp main.h MIDIconst.h
# 	g++ -Wall -o metaEvents.o metaEvents.cpp

#removes exe, object, and backup files
# clean:
# 	rm sort *.o *~
	
# g++ main.cpp trackEvents.cpp metaEvents.cpp channelMessages.cpp -o main
# ./main

