all: hello

hello: hello.o
	g++ -o hello hello.o

hello.o: hello.cpp
	g++ -o hello.o -c hello.cpp

clean:
	-rm -f *~
	-rm -f *.o
	-rm -f hello



