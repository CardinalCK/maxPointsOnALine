CC=clang++
CFLAGS= -std=gnu++11 -g #-Weverything -Wno-c++98-compat -Wno-padded
SOURCES= maxPointsOnALine.cpp 
DEPS= 
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=maxPoints

all: $(EXECUTABLE)
	@echo Make has finished.

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS)  $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) -c $*.cpp

clean: 
	$(RM) *.o *~ $(EXECUTABLE)