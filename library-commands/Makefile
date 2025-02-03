# Build the library here
all: libcommands.a

libcommands.a: questions3_aux.o audio_track_creator_aux.o wav_file_creator_aux.o
	ar crus $@ $^

questions3_aux.o: questions3_aux.cpp questions3_aux.h ../include/ApplicationData.h
	g++ -I ../include -o $@ -c $<

audio_track_creator_aux.o: audio_track_creator_aux.cpp audio_track_creator_aux.h ../include/ApplicationData.h
	g++ -I ../include -o $@ -c $<

wav_file_creator_aux.o: wav_file_creator_aux.cpp wav_file_creator_aux.h ../include/ApplicationData.h
	g++ -I ../include -o $@ -c $<

# Install the library for other parts of the project to use
install: ../lib/libcommands.a ../include/questions3_aux.h ../include/audio_track_creator_aux.h ../include/wav_file_creator_aux.h

../lib/libcommands.a: libcommands.a
	cp $< $@

../include/questions3_aux.h: questions3_aux.h
	cp $< $@

../include/audio_track_creator_aux.h: audio_track_creator_aux.h
	cp $< $@

../include/wav_file_creator_aux.h: wav_file_creator_aux.h
	cp $< $@
	
clean:
	-rm -f *.o libcommands.a

