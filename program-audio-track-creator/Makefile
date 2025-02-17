<<<<<<< HEAD
all: audio_track_creator 

audio_track_creator: audio_track_creator.o ../lib/libcommands.a ../lib/libaudiotrack.a 
	g++ -L../lib -o $@ $< -lcommands -lapplication -laudiotrack

audio_track_creator.o: audio_track_creator.cpp ../include/audio_track_creator_aux.h ../include/ApplicationData.h ../include/AudioTrack.h
	g++ -I../include -o $@ -c $<

clean:
	-rm -f *.o audio_track_creator
=======
PROGRAM_NAME := audio_track_creator
include ../make-help/program.mk
>>>>>>> b63ca74 (curts quads or burts?)
