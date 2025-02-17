all: build

build:
	make -C library-audiofiles install
	make -C library-envelope install
	make -C library-waveform install
	make -C library-application install
	make -C library-commands install
	make -C program-waveform-test all
	make -C program-wav-file-creator all
	make -C program-audio-track-creator all
	make -C program-hello all
	make -C program-questions3 all
	make -C program-difference all
	make -C program-envelope-test all

clean:
	make -C library-audiofiles clean
	make -C library-envelope clean
	make -C library-waveform clean
	make -C library-application clean
	make -C library-commands clean
	make -C program-waveform-test clean
	make -C program-hello clean
	make -C program-questions3 clean
	make -C program-difference clean
	make -C program-envelope-test clean
	
	-cd lib && rm -f *.a 
	-cd include && rm -f *.h
	
