/*
 * Name: Chao Huang, Yeung-Kit Wong
 * Date: Aug 25, 2016
 * File: Movie.hpp
 * Description:
 */

#ifndef MOVIE_HPP
#define MOVIE_HPP

#include <unordered_set>

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

  // add an actor who casts this movie
  void addActor(Actor* actor){actors.insert(actor);}

  // set year
  void setYear(int year){this->year = year;}

  // set weight
  void setWeight(int weight){this->weight = weight;}

  // get name
  string getName(){return name;}

  // get actors
  unordered_set<Actor*> getActors(){return actors;}

  // get year
  int getYear(){return year;}

  // get weight
  int getWeight(){return weight;}

  // toString function
  string toString(){
    string str;
    str.append("("+name+")");
    str.append(" #Actors("+to_string(actors.size())+")");
    str.append(" Year("+to_string(year)+")");
    str.append(" Weight("+to_string(weight)+")");
    return str;
  }

};

#endif
