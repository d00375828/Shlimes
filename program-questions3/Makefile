<<<<<<< HEAD
all: questions3

questions3: questions3.o ../lib/libapplication.a ../lib/libcommands.a ../lib/libaudiotrack.a
	g++ -L../lib -o $@ $< -lcommands -lapplication -laudiotrack

questions3.o: questions3.cpp ../include/questions3_aux.h ../include/ApplicationData.h ../include/AudioTrack.h
	g++ -I../include -o $@ -c $<

clean:
	-rm -f *.o questions3
=======
PROGRAM_NAME := questions3
include ../make-help/program.mk
>>>>>>> b63ca74 (curts quads or burts?)
