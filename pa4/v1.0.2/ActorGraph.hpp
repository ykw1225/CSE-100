/*
 * Name: Chao Huang, Yeung-Kit Wong
 * Date: Aug 25, 2016
 * File: ActorGraph.hpp
 * Description:
 */

#ifndef ACTORGRAPH_HPP
#define ACTORGRAPH_HPP

#include <unordered_map>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>

#include "Actor.hpp"
#include "Movie.hpp"

using namespace std;

class ActorGraph {
  public:

  // vector to store ptrs to all the actors
  vector <Actor*> allActors;

  // map to store all the movies
  unordered_map <string, Movie*> allMovies;

  // boolean to indicate if build a weighted graph
  bool weighted;

  ActorGraph(bool);

  void buildGraph(ifstream&);

  void addActor(Actor* a){allActors.push_back(a);}

  void printAll();

  void deleteAll();

  ~ActorGraph(){deleteAll();}

};


#endif // ACTORGRAPH_HPP
