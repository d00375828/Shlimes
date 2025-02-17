<<<<<<< HEAD
# Build the library here
all: libapplication.a

libapplication.a: ApplicationData.o
	ar crus $@ $^

ApplicationData.o: ApplicationData.cpp ApplicationData.h
	g++ -I../include -o $@ -c $<

# Install the library for other parts of the project to use
install: ../lib/libapplication.a ../include/ApplicationData.h

../lib/libapplication.a: libapplication.a
	cp $< $@

../include/ApplicationData.h: ApplicationData.h
	cp $< $@


clean:
	-rm -f *.o libapplication.a
=======
LIBRARY := application
include ../make-help/library.mk
>>>>>>> b63ca74 (curts quads or burts?)
