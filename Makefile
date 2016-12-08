# Brendan Thompson & Andrew Ellis
# Makefile for MIDI prog7
# 12/7/16

default: 
	g++ *.cpp -o main

#removes exe and midi files
clean:
	rm main prog7.mid