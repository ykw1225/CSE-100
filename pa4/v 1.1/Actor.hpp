/*
 * Name: Chao Huang, Yeung-Kit Wong
 * Date: Aug 25, 2016
 * File: Actor.hpp
 * Description:
 */

#ifndef ACTOR_HPP
#define ACTOR_HPP

#include <unordered_set>
#include <limits>

#include "Movie.hpp"

using namespace std;

class Movie;

// a class represent an actor(Vertex in graph)
class Actor{
public:

  // actor's name
  string name;

  // all movies that actor casts
  unordered_set <Movie*> movies;

  // constructor
  Actor(string n){
    name = n;
    clear();
  }

  // add a movie this actor casts
  void addMovie(Movie* m){movies.insert(m);}

  // clear three member for find shortest path
  void clear(){
    setDone(false);
    setDist(numeric_limits<int>::max());
    setPrev(nullptr);
    setEdge(nullptr);
  }

  // set done
  void setDone(bool b){done = b;}

  // set dist
  void setDist(int d){dist = d;}

  // set prevActor
  void setPrev(Actor* p){prevActor = p;}

  // set edge
  void setEdge(Movie* m){edge = m;}

  // a operator < overload function for Actor object
  bool operator<(const Actor& other){return dist > other.dist;}

  // boolean for if the shortest dist is found
  bool done;

  // shortest distance
  int dist;

  // previous actor
  Actor* prevActor;

  // edge connect previour actor and this actor
  Movie* edge;

};

#endif
