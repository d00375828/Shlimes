<<<<<<< HEAD
all: wav_file_creator

wav_file_creator: wav_file_creator.o ../lib/libcommands.a ../lib/libapplication.a ../lib/libaudiotrack.a
	g++ -L../lib -o $@ $< -lcommands -lapplication -laudiotrack

wav_file_creator.o: wav_file_creator.cpp ../include/wav_file_creator_aux.h ../include/ApplicationData.h
	g++ -I../include -o $@ -c $<


clean:
	-rm -f *.o wav_file_creator
=======
PROGRAM_NAME := wav_file_creator
include ../make-help/program.mk
>>>>>>> b63ca74 (curts quads or burts?)
