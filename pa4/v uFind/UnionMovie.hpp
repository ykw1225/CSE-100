/*
 * Name: Chao Huang, Yeung-Kit Wong
 * Date: Aug 30, 2016
 * File: UnionMovie.hpp
 * Description:
 */

#ifndef UNIONMOVIE_HPP
#define UNIONMOVIE_HPP

#include <unordered_set>

#include "UnionActor.hpp"

using namespace std;

class UnionActor;

// a class represent a movie(Edge in graph)
class UnionMovie{
private:

  // the name of movie
  string name;

  // all actors cast this movie
  unordered_set<UnionActor *> actors;

  // the year of movie
  int year;

public:

  // constructor for union find graph
  UnionMovie(string name, int year):
    name(name), year(year){}

  // comparison class for movie pointer
  class MovPtrComp{
  public:
    bool operator()(UnionMovie* l, UnionMovie* r){return *l < *r;}
  };

  // add an actor who casts this movie
  void addActor(UnionActor* actor){actors.insert(actor);}

  // set year
  void setYear(int year){this->year = year;}

  // get name
  string getName(){return name;}

  // get actors
  unordered_set<UnionActor*> getActors(){return actors;}

  // get year
  int getYear(){return year;}

  // operator < overload function for UnionMovie object
  bool operator < (const UnionMovie& other){
    if(year != other.year)
      return year < other.year;
    else if(name.compare(other.name) < 0)
      return name.compare(other.name);
    return false;
  }

};

#endif
