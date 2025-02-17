<<<<<<< HEAD
# Build the library here
all: libaudiotrack.a

libaudiotrack.a: AudioTrack.o endian_io.o WAVFile.o
	ar crus $@ $^

AudioTrack.o: AudioTrack.cpp AudioTrack.h
	g++ -I../include -o $@ -c $<

endian_io.o: endian_io.cpp endian_io.h
	g++ -I../include -o $@ -c $<

WAVFile.o: WAVFile.cpp WAVFile.h
	g++ -I../include -o $@ -c $<

# Install the library for other parts of the project to use
install: ../lib/libaudiotrack.a ../include/AudioTrack.h ../include/endian_io.h ../include/WAVFile.h

../lib/libaudiotrack.a: libaudiotrack.a
	cp $< $@

../include/AudioTrack.h: AudioTrack.h
	cp $< $@

../include/endian_io.h: endian_io.h
	cp $< $@

../include/WAVFile.h: WAVFile.h
	cp $< $@

clean:
	-rm -f *.o libaudiotrack.a
=======
LIBRARY := audiofiles
include ../make-help/library.mk
>>>>>>> b63ca74 (curts quads or burts?)
