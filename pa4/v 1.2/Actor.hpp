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
private:

  /* All fields */

  // actor's name
  string name;

  // all movies that actor casts
  unordered_set<Movie*> movies;

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
  Actor(string name):name(name){clear();}

  // add a movie this actor casts
  void addMovie(Movie* m){movies.insert(m);}

  // clear three member for find shortest path
  void clear(){

/*
cout << "\tStart clear(" << name << "):\n";
cout << "\t\t(" << done << ")(" << dist << ")";
if(prev)cout << "(" << prev->getName() << ")(" << edge->getName() << ")";
cout << endl;
*/

    setDone(false);
    setDist(numeric_limits<int>::max());
    setPrev(nullptr);
    setEdge(nullptr);

/*
cout << "\t\t(" << done << ")(" << dist << ")";
if(prev)cout << "(" << prev->getName() << ")(" << edge->getName() << ")";
cout << endl;
*/

  }

  // set done
  void setDone(bool newDone){done = newDone;}

  // set dist
  void setDist(int newDist){dist = newDist;}

  // set prevActor
  void setPrev(Actor* newPrev){prev = newPrev;}

  // set edge
  void setEdge(Movie* movie){edge = movie;}

  // get name
  string getName(){return name;}

  // get movies
  unordered_set<Movie*> getMovies(){return movies;}

  // get done
  bool getDone(){return done;}

  // get dist
  int getDist(){return dist;}

  // get prev
  Actor* getPrev(){return prev;}

  // get edge
  Movie* getEdge(){return edge;}

  // toString function
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
      return dist > other.dist;
    else if(name.compare(other.name) < 0)
      return name.compare(other.name);
      return false;
  }

};

#endif
