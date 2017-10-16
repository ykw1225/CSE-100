 # Filename: Makefile
 # Author: Chao Huang, Yeung-Kit Wong
 # Date: Aug 23 2016
 # Description: 

CC=g++
CXXFLAGS=-std=c++11 -g -Wall -gdwarf-2 -O3
LDFLAGS=-g

all: pathfinder actorconnections

pathfinder: ActorGraph.o

actorconnections: ActorGraph.o

ActorGraph.o: ActorGraph.hpp Actor.o Timer.o Movie.o

Actor.o: Actor.hpp

Movie.o: Movie.hpp

Timer.o: Timer.hpp

clean:
	rm -f *.o core* *~ pathfinder out output mine ref actorconnections
