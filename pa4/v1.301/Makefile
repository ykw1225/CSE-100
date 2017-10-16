 # Filename: Makefile
 # Author: Chao Huang, Yeung-Kit Wong
 # Date: Aug 23 2016
 # Description: 

CC=g++
CXXFLAGS=-std=c++11 -g -Wall -gdwarf-2 -O3
LDFLAGS=-g

all: pathfinder actorconnections

pathfinder: ActorGraph.o

actorconnections: UnionGraph.o

UnionGraph.o: UnionGraph.hpp UnionActor.o

ActorGraph.o: ActorGraph.hpp Actor.o

UnionActor.o: UnionActor.hpp UnionMovie.o

Actor.o: Actor.hpp Movie.o

UnionMovie.o: UnionMovie.hpp

Movie.o: Movie.hpp

clean:
	rm -f *.o core* *~ pathfinder
