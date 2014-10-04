CC   = gcc
CXX  = g++

INCLUDE     = -I.
CFLAGS  = $(INCLUDE) -g -Wall
LFLAGS  =
LIBS    =

SRC     = main.cpp
HEADERS = AddressDecoder.h Cache.h CustomTypes.h MainMemory.h Memory.h ResultGenerator.h TraceReader.h

TARGET  = sim_cache

OBJECTS = $(SRC:%.cpp=%.o)

all: BINARY

clean:
	rm -f $(OBJECTS) $(TARGET) .depend

clobber:
	rm -f $(OBJECTS)

BINARY: $(OBJECTS) $(HEADERS)
	$(CXX) $(LFLAGS) $(OBJECTS) $(LIBS) -o $(TARGET)

%.o: %.cpp
	$(CXX) -c $(CFLAGS) $^ -o $@

