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
#include <iostream>
#include <queue>
#include <stack>

#include "Actor.hpp"
#include "Movie.hpp"

using namespace std;

class ActorGraph {
private:

  /* All fields */

  // vector to store ptrs to all the actors
  unordered_map<string, Actor*> allActors;

  // map to store all the movies
  unordered_map<string, Movie*> allMovies;

  // boolean to indicate if build a weighted graph
  bool weighted;

public:

  /* All functions */

  // constructor
  ActorGraph(bool weighted):weighted(weighted){}

  // destructor
  ~ActorGraph(){deleteAll();}

  // function for building the graph
  void buildGraph(ifstream&);

  // add a new actor to allActors field
  void addActor(string name, Actor* actor){
    allActors.insert(pair<string, Actor*>(name, actor));
  }

  // find the actor in all actors field and return an iterator
  unordered_map<string, Actor*>::iterator findActor(string actor){
    return allActors.find(actor);
  }

  // add a new movie to allMovies field
  void addMovie(string name, Movie* movie){
    allMovies.insert(pair<string, Movie*>(name, movie));
  }

  // find the movie in all movies field and return an iterator
  unordered_map<string, Movie*>::iterator findMovie(string movie){
    return allMovies.find(movie);
  }

  // find the shortest path from start actor to dest actor
  bool findPath(string start, string dest);

  // save the shortest path into the stack
  bool getPath(string dest, stack<string>& container);

  // get actors
  unordered_map<string, Actor*> getAllActors(){return allActors;}

  // get movies
  unordered_map<string, Movie*> getAllMovies(){return allMovies;}

  // clear dist, done, prev fields for all actors
  void clearAll();

  // print out all actors and movies
  void printAll();

  // delete all alocation of all objects
  void deleteAll();

};


#endif // ACTORGRAPH_HPP
