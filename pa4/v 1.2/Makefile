 # Filename: Makefile
 # Author: Chao Huang, Yeung-Kit Wong
 # Date: Aug 23 2016
 # Description: 

CC=g++
CXXFLAGS=-std=c++11 -g -Wall -gdwarf-2 -O3
LDFLAGS=-g

all: pathfinder

pathfinder: ActorGraph.o

ActorGraph.o: ActorGraph.hpp Actor.o

Actor.o: Actor.hpp Movie.o

Movie.o: Movie.hpp

clean:
	rm -f *.o core* *~ pathfinder out output mine ref
