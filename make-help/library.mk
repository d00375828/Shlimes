CXX := g++
CXXFLAGS := -Wall -I ../include -std=c++20
DEPENDFLAGS := -MMD -MP

SOURCES := $(wildcard *.cpp)
OBJECTS := $(patsubst %.cpp,%.o,$(SOURCES))
DEPENDS := $(patsubst %.cpp,%.d,$(SOURCES))
HEADERS := $(wildcard *.h)
INSTALLED_HEADERS := $(patsubst %.h,../include/%.h,$(HEADERS))

# Build the library here
all: lib$(LIBRARY).a

lib$(LIBRARY).a: $(OBJECTS)
	ar crus $@ $?

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(DEPENDFLAGS) -o $@ -c $<

-include $(DEPENDS)

# Install the library for other parts of the project to use
install: ../lib/lib$(LIBRARY).a $(INSTALLED_HEADERS)

# pattern rule
../lib/%.a: %.a
	cp $< $@

# pattern rule
../include/%.h: %.h
	cp $< $@


clean:
	-rm -f *.o lib$(LIBRARY).a  *.d