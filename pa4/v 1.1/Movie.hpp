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
public:

  // the name of movie
  string name;

  // all actors cast this movie
  unordered_set <Actor*> actorCast;

  // the year of movie
  int year;

  // constructor
  Movie(string n, int y):name(n), year(y){}

  // add an actor who casts this movie
  void addActor(Actor* a){actorCast.insert(a);}

};

#endif
