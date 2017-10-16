/*
 * Name: Chao Huang, Yeung-Kit Wong
 * Date: Aug 25, 2016
 * File: Actor.hpp
 * Description: header file contains a Actor class represent a Actor(Vertex in graph)
 */

#ifndef ACTOR_HPP
#define ACTOR_HPP

#include <unordered_set>
#include <limits>
#include <map>
#include <set>

#include "Movie.hpp"

using namespace std;

class Movie;

// a class represent an actor(Vertex in graph)
class Actor{
private:

  /* All fields */

  // actor's name
  string name;

  // all movies that actor casts
  unordered_set<Movie*> movies;

  // set to store all the movies that actor casts in sorted order
  set<Movie*, Movie::MoviePtrComp> sortedMovies;

  // all connections of this actor
  unordered_map<Actor*, int> connections;

  // boolean for if the shortest dist is found
  bool done;

  // shortest distance
  int dist;

  // previous actor
  Actor* prev;

  // edge connect previour actor and this actor
  Movie* edge;

public:

  /* All functions */

  // constructor
  Actor(string name):name(name){}

  // destructor
  ~Actor(){}



  /* Mutator */

/*
 * Function name: addMovie
 * Description: add a movie this actor casts
 */
  void addMovie(Movie* m){movies.insert(m);sortedMovies.insert(m);}

/*
 * Function name: addConnections
 * Description: add a new connection of this actor
 */
  void addConnections(Actor* actor, int year){
    connections.insert(pair<Actor*, int>(actor, year));
  }

/*
 * Function name: clear
 * Description: clear four members for find shortest path
 */
  void clear(){
    setDone(false);
    setDist(numeric_limits<int>::max());
    setPrev(nullptr);
    setEdge(nullptr);
  }

/*
 * Function name: setDone
 * Description: set done
 */
  void setDone(bool newDone){done = newDone;}

/*
 * Function name: setDist
 * Description: set dist
 */
  void setDist(int newDist){dist = newDist;}

/*
 * Function name: setPrev
 * Description: set prevActor
 */
  void setPrev(Actor* newPrev){prev = newPrev;}

/*
 * Function name: setEdge
 * Description: set edge
 */
  void setEdge(Movie* movie){edge = movie;}



  /* Accessor */

/*
 * Function name: getName
 * Description: get name
 * Return Value: the name of this actor
 */
  string getName(){return name;}

/*
 * Function name: getMovies
 * Description: get movies
 * Return Value: a copy of the movies that this actor casts
 */
  unordered_set<Movie*> getMovies(){return movies;}

/*
 * Function name: getSortedMovies
 * Description: get sorted movies
 * Return Value: a copy of the sorted movies that this actor casts
 */
  set<Movie*, Movie::MoviePtrComp> getSortedMovies(){return sortedMovies;}

/*
 * Function name: getConnections
 * Description: get connections
 * Return Value: a copy of the connections that this actor has
 */
  unordered_map<Actor*, int> getConnections(){return connections;}

/*
 * Function name: getDone
 * Description: get done
 * Return Value: the done field of this actor
 */
  bool getDone(){return done;}

/*
 * Function name: getDist
 * Description: get dist
 * Return Value: the dist field of this actor
 */
  int getDist(){return dist;}

/*
 * Function name: getPrev
 * Description: get prev
 * Return Value: a pointer represent the previous actor in path before this actor
 */
  Actor* getPrev(){return prev;}

/*
 * Function name: getEdge
 * Description: get edge
 * Return Value: a pointer of Movie(edge) connect this actor and prev actor
 */
  Movie* getEdge(){return edge;}



  /* helper functions */

  // comparison class for actor pointer
  class ActorPtrComp{
  public:
    bool operator()(Actor* l, Actor* r){return *l < *r;}
  };

  // comparison class for actor pointer in priority_queue
  class ActorPtrCompPQ{
  public:
    bool operator()(Actor* l, Actor* r){return *r < *l;}
  };

/*
 * Function name: toString
 * Description: toString function
 * Return Value: a string contains all information of this actor
 */
  string toString(){
    string str;
    str.append("("+name+")");
    str.append(" #Movies("+to_string(movies.size())+")");
    str.append(" Done("+to_string(done)+")");
    str.append(" Dist("+to_string(dist)+")");
    if(prev)
      str.append(" Prev("+prev->getName()+")");
    if(edge)
      str.append(" Edge("+edge->getName()+")");
    return str;
  }

  // a operator < overload function for Actor object
  bool operator<(const Actor& other){
    if(dist != other.dist)
      return dist < other.dist;
    else if(name.compare(other.name) < 0)
      return name.compare(other.name);
    return false;
  }

};

#endif
