all: build

build:
	make -C library-audiofiles install
	make -C library-application install
	make -C library-commands install
	make -C program-hello all
	make -C program-questions3 all
	make -C program-audio-track-creator all
	make -C program-wav-file-creator all

clean:
	make -C library-audiofiles clean
	make -C library-application clean
	make -C library-commands clean
	make -C program-hello clean
	make -C program-questions3 clean
	make -C program-audio-track-creator clean
	make -C program-wav-file-creator clean 
	-cd lib && rm -f *.a 
	-cd include && rm -f *.h
