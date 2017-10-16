/*
 * Name: Chao Huang, Yeung-Kit Wong
 * Date: Aug 30, 2016
 * File: UnionMovie.hpp
 * Description: Header file of UnionMovie object for uFind
 *              declares UnionMovie class members and function prototypes
 */

#ifndef UNIONMOVIE_HPP
#define UNIONMOVIE_HPP

#include <unordered_set>

#include "UnionActor.hpp"

using namespace std;

class UnionActor;

/** class that represents a movie
 *  saves a movies's name and released year
 */
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

  /* comparison class for movie pointer */
  class MovPtrComp{
  public:
    bool operator()(UnionMovie* l, UnionMovie* r){return *l < *r;}
  };

  /* function to stores an actor when found in a  movie */
  void addActor(UnionActor* actor){actors.insert(actor);}

  /* set year for UnionMovie object */
  void setYear(int year){this->year = year;}

  /* returns name of the movie */
  string getName(){return name;}

  /* returns all the actors in this movie */
  unordered_set<UnionActor*> getActors(){return actors;}

  /* returns the year of this movie */
  int getYear(){return year;}

  /** operator < overload function for UnionMovie object
   *  a movie is considered larger if it gets a later realeased year
   */
  bool operator < (const UnionMovie& other){
    if(year != other.year)
      return year < other.year;
    else if(name.compare(other.name) < 0)
      return name.compare(other.name);
    return false;
  }

};

#endif
