/*
 * Name: Chao Huang, Yeung-Kit Wong
 * Date: Aug 30, 2016
 * File: UnionGraph.hpp
 * Description: Header file of UnionGraph object for uFind
 *              declares class member, functions prototype
 */

#ifndef UNIONGRAPH_HPP
#define UNIONGRAPH_HPP

#include <unordered_map>
#include <set>
#include <fstream>
#include <iostream>
#include <queue>
#include <stack>
#include <string>

#include "UnionActor.hpp"
#include "UnionMovie.hpp"

using namespace std;

/** a class that represents all the data and connections between 
 *  movies and actors
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

  /**
   * Function name: buildGraph
   * Description: function to build the graph
   */
  void buildGraph(ifstream&);

  /**
   * Function name: addActor
  * Description: add a new actor to allActors field
   */
  void addActor(string name, UnionActor* actor){
    allActors.insert( pair<string, UnionActor*>(name, actor) );
  }

  /**
   * Function name: addMovie
   * Description: add a new movie to allMovies field
   */
  void addMovie(string name, UnionMovie* movie){
    allMovies.insert( pair<string, UnionMovie*>(name, movie) );
  }

  /**
   * Function name: addSortMovie
   * Description: add a new movie to the sortedMovies field
   */
  void addSortMovie(UnionMovie* movie){
    sortedMovies.insert( movie );
  }

  /**
   * Function name: findActor
   * Description: find the actor in all actors field and return an iterator
   * Return Value: the iterator point to the UnionActor, otherwise end()
   */
  unordered_map<string, UnionActor*>::iterator findActor(string actor){
    return allActors.find(actor);
  }

  /**
   * Function name: findMovie
   * Description: find the movie in all movies field and return an iterator
   * Return Value: the iterator point to the UnionMovie, otherwise end()
   */
  unordered_map<string, UnionMovie*>::iterator findMovie(string movie){
    return allMovies.find(movie);
  }

  /**
   * Function name: uFind
   * Description: use union find to search earliest year two actors gets
   *              connected. returns the connected year 
   */
  int uFind( string fromActor, string toActor );

  /** Function name: findRoot
   *  Description: find and return the root actor of an actor
   */
  UnionActor* findRoot(UnionActor* actor); 

  /** Function name: unionNodes
   *  Description: Function to union two disjoint set
   */
  void unionNodes( UnionActor* actorA, UnionActor* actorB);

  /*
   * Function name: getAllActors
   * Description: get all actors
   * Return Value: the copy of map contains all actors
   */
  unordered_map<string, UnionActor*> getAllActors(){return allActors;}

  /** Function name: getSortedMovies
   *  Description: return the sorted UnionMovie* set
   */
  set<UnionMovie*, UnionMovie::MovPtrComp> getSortedMovies()
    {return sortedMovies;}

  /**
   * Function name: getAllMovies
   * Description: function to return all the movies stored in the graph
   */
  unordered_map<string, UnionMovie*> getAllMovies(){return allMovies;}

  /** Function name: cleanParent
   *  Description: futnion to reset parent actor of all the actors
   */
  void cleanParent();

  /**
   * Function name: deleteAll
   * Description: delete all alocation of all objects
   */
  void deleteAll();

};


#endif // ACTORGRAPH_HPP
