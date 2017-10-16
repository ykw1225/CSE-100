/*
 * Name: Chao Huang, Yeung-Kit Wong
 * Date: Aug 25, 2016
 * File: Movie.hpp
 * Description: header file contains a Movie class represent a Movie(Edge in graph)
 */

#ifndef MOVIE_HPP
#define MOVIE_HPP

#include "Actor.hpp"

using namespace std;

class Actor;

// a class represent a movie(Edge in graph)
class Movie{
private:

  /* All fields */

  // the name of movie
  string name;

  // all actors cast this movie
  unordered_set<Actor*> actors;

  // the year of movie
  int year;

  // the weight of movie
  int weight;

public:

  /* All functions */

  // constructor
  Movie(string name, int year, int weight):
    name(name), year(year), weight(weight){}

  // destructor
  ~Movie(){}



  /* Mutator */

/*
 * Function name: addActor
 * Description: add an actor who casts this movie
 */
  void addActor(Actor* actor){actors.insert(actor);}

/*
 * Function name: setYear
 * Description: set year
 */
  void setYear(int year){this->year = year;}

/*
 * Function name: setWeight
 * Description: set weight
 */
  void setWeight(int weight){this->weight = weight;}



  /* Accessor */

/*
 * Function name: getName
 * Description: get name
 * Return Value: the name of this movie
 */
  string getName(){return name;}

/*
 * Function name: getActors
 * Description: get actors
 * Return Value: a copy of all actors cast this movie
 */
  unordered_set<Actor*> getActors(){return actors;}

/*
 * Function name: getYear
 * Description: get year
 * Return Value: the year of this movie is made
 */
  int getYear(){return year;}

/*
 * Function name: getweight
 * Description: get weight
 * Return Value: the weight of this movie
 */
  int getWeight(){return weight;}



  /* helper functions */

  // comparison class for movie pointer
  class MoviePtrComp{
  public:
    bool operator()(Movie* l, Movie* r){return *l < *r;}
  };

/*
 * Function name: toString
 * Description: toString function
 * Return Value: a string contains all information of this movie
 */
  string toString(){
    string str;
    str.append("("+name+")");
    str.append(" #Actors("+to_string(actors.size())+")");
    str.append(" Year("+to_string(year)+")");
    str.append(" Weight("+to_string(weight)+")");
    return str;
  }

  // a operator < overload function for Actor object
  bool operator<(const Movie& other){
    if(year != other.year)
      return year < other.year;
    else if(name.compare(other.name) < 0)
      return name.compare(other.name);
    return false;
  }

};

#endif
