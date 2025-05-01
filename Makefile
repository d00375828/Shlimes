all: build

build:
	# First build the base libraries that don't depend on other libraries
	make -C library-audiofiles install
	make -C library-envelope install
	make -C library-waveform install
	
	# Build the instrument library (depends on waveform and envelope)
	make -C library-instrument install
	
	# Build the score library (depends on base libraries and instrument)
	make -C library-score install
	
	# Build the score-io library (depends on score library)
	make -C library-score-io install
	
	# Build the application and commands libraries (depend on all previous libraries)
	make -C library-application install
	make -C library-commands install
	
	# Build all executable programs
	make -C program-hello all
	make -C program-questions3 all
	make -C program-difference all
	make -C program-waveform-test all
	make -C program-wav-file-creator all
	make -C program-audio-track-creator all
	make -C program-envelope-test all
	make -C program-instrument-test all
	make -C program-instrument-designer all
	make -C program-score-editor all

clean:
	# Clean libraries
	make -C library-audiofiles clean
	make -C library-envelope clean
	make -C library-waveform clean
	make -C library-instrument clean
	make -C library-score clean
	make -C library-score-io clean
	make -C library-application clean
	make -C library-commands clean
	
	# Clean executables
	make -C program-hello clean
	make -C program-questions3 clean
	make -C program-difference clean
	make -C program-waveform-test clean
	make -C program-wav-file-creator clean
	make -C program-audio-track-creator clean
	make -C program-envelope-test clean
	make -C program-instrument-test clean
	make -C program-instrument-designer clean
	make -C program-score-editor clean
	
	# Clean shared library files and headers
	-cd lib && rm -f *.a 
	-cd include && rm -f *.h
	
