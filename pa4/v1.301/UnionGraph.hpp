/*
 * Name: Chao Huang, Yeung-Kit Wong
 * Date: Aug 30, 2016
 * File: UnionGraph.hpp
 * Description:
 */

#ifndef UNIONGRAPH_HPP
#define UNIONGRAPH_HPP

#include <unordered_map>
#include <set>
#include <fstream>
#include <iostream>
#include <queue>
#include <stack>

#include "UnionActor.hpp"
#include "UnionMovie.hpp"

using namespace std;

/*
// compare class for UnionMovie objects
struct movieComp {
  bool operator()(UnionMovie* lhs, UnionMoive* rhs) {
    return &lhs < &rhs;
  }
};
*/

class UnionGraph {
private:

  // unordered_map to store ptrs to all the actors
  unordered_map<string, UnionActor*> allActors;

  // unordered_map to store ptrs to all the movies
  unordered_map<string, UnionMovie*> allMovies;

  // set to store all the movie ptrs in increasing order of year
  set<UnionMovie*, UnionMovie::MovPtrComp> sortedMovies;

public:

  // constructor
  UnionGraph(){}

  // destructor
  ~UnionGraph(){deleteAll();}

  // function for building the graph
  void buildGraph(ifstream&);

  // add a new actor to allActors field
  void addActor(string name, UnionActor* actor){
    allActors.insert( pair<string, UnionActor*>(name, actor) );
  }

  // add a new movie to allMovies field
  void addMovie(string name, UnionMovie* movie){
    allMovies.insert( pair<string, UnionMovie*>(name, movie) );
  }

  // add a movie to sortedMovies
  void addSortMovie(UnionMovie* movie){
    sortedMovies.insert( movie );
  }

  // find the actor in all actors field and return an iterator
  unordered_map<string, UnionActor*>::iterator findActor(string actor){
    return allActors.find(actor);
  }

  // find the movie in all movies field and return an iterator
  unordered_map<string, UnionMovie*>::iterator findMovie(string movie){
    return allMovies.find(movie);
  }

  // Union find connection function
  std::string uFind(string fromActor, string toActor); 

  // get actors
  unordered_map<string, UnionActor*> getAllActors(){return allActors;}

  // get sorted movies
  set<UnionMovie*, UnionMovie::MovPtrComp> getSortedMovies(){return sortedMovies;}

  // get movies
  unordered_map<string, UnionMovie*> getAllMovies(){return allMovies;}

  // print out all actors and movies
  void printAll();

  // delete all alocation of all objects
  void deleteAll();

};


#endif // ACTORGRAPH_HPP
