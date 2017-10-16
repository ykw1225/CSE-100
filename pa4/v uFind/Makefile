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

UnionGraph.o: UnionGraph.hpp UnionActor.o UnionMovie.o Timer.o

ActorGraph.o: ActorGraph.hpp Actor.o Movie.o Timer.o

UnionActor.o: UnionActor.hpp 

Actor.o: Actor.hpp

UnionMovie.o: UnionMovie.hpp

Movie.o: Movie.hpp

Timer.o: Timer.hpp

clean:
	rm -f *.o core* *~ pathfinder
