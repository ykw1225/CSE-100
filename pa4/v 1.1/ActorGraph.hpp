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
#include <unordered_set>
#include <iostream>
#include <queue>
#include <stack>

#include "Actor.hpp"
#include "Movie.hpp"

using namespace std;

class ActorGraph {
  public:

  // vector to store ptrs to all the actors
  unordered_map <string, Actor*> allActors;

  // map to store all the movies
  unordered_map <string, Movie*> allMovies;

  // boolean to indicate if build a weighted graph
  bool weighted;

  ActorGraph(bool);

  void buildGraph(ifstream&);

  void addActor(string s, Actor* a){
    allActors.insert(pair<string, Actor*>(s, a));
  }

  void addMovie(string s, Movie* m){
    allMovies.insert(pair<string, Movie*>(s, m));
  }

  bool findPath(string start, string end);

  bool getPath(string end, stack<string>& s);

  // clear three member for all actors
  void clearAll();

  void printAll();

  void deleteAll();

  ~ActorGraph(){deleteAll();}

};


#endif // ACTORGRAPH_HPP
