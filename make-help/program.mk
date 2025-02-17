CXX := g++
CXXFLAGS := -Wall -I ../include -std=c++20
LDFLAGS  := -L../lib -lcommands -lapplication -laudiofiles -lwaveform -lenvelope
DEPENDFLAGS := -MMD -MP

SOURCES := $(wildcard *.cpp)
OBJECTS := $(patsubst %.cpp,%.o,$(SOURCES))
DEPENDS := $(patsubst %.cpp,%.d,$(SOURCES))
LIBS    := $(wildcard ../lib/*.a)

all: $(PROGRAM_NAME)

$(PROGRAM_NAME): $(OBJECTS) $(LIBS)
	$(CXX) $(CXXFLAGS) -o $@ $< $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(DEPENDFLAGS) -o $@ -c $<

-include $(DEPENDS)

clean:
	-rm -f *.o $(PROGRAM_NAME) *.d
