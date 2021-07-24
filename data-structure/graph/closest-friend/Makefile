# A simple makefile for CSE 100 PA4

CC=g++
CXXFLAGS=-std=c++11

ifeq ($(type),opt)
    CPPFLAGS += -O3
    LDFLAGS += -O3
else
    CPPFLAGS += -g
    LDFLAGS += -g
endif

all: pathfinder movietraveler

pathfinder: ActorGraph.o Movie.o Actor.o

movietraveler: ActorGraph.o Movie.o Actor.o

ActorGraph.o: ActorGraph.hpp Movie.o Actor.o

Movie.o: Movie.hpp

Actor.o: Actor.hpp

clean:
	rm -f pathfinder *.o core* .*.gch *.gch
