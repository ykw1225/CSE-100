/*
 * Name: Chao Huang, Yeung-Kit Wong
 * Date: Aug 25, 2016
 * File: ActorGraph.hpp
 * Description: Header file that contains an ActorGraph class that represent the graph
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

// class that represent the graph with vertex(Actor) and edge(Movie)
class ActorGraph {
private:

  /* All fields */

  // vector to store ptrs to all the actors
  unordered_map<string, Actor*> allActors;

  // map to store all the movies
  unordered_map<string, Movie*> allMovies;

  // set to store all the movies in sorted order
  set<Movie*, Movie::MoviePtrComp> sortedAllMovies;

  // boolean to indicate if build a weighted graph
  bool weighted;

public:

  /* All functions */

  // constructor
  ActorGraph(bool weighted):weighted(weighted){}

  // destructor
  ~ActorGraph(){deleteAll();}



  /* Mutator */

/*
 * Function name: buildGraph
 * Description: function for building the graph
 */
  void buildGraph(ifstream&);

/*
 * Function name: addActor
 * Description: add a new actor to allActors field
 */
  void addActor(string name, Actor* actor){
    allActors.insert(pair<string, Actor*>(name, actor));
  }

/*
 * Function name: addMovie
 * Description: add a new movie to allMovies field
 */
  void addMovie(string name, Movie* movie){
    allMovies.insert(pair<string, Movie*>(name, movie));
    sortedAllMovies.insert(movie);
  }

/*
 * Function name: findPath
 * Description: find the shortest path from start actor to dest actor
 * Return Value: true for successfully find the path, otherwise false
 */
  bool findPath(string start, string dest);

/*
 * Function name: getPath
 * Description: save the shortest path into the stack
 * Return Value: true for successfully get the path, otherwise false
 */
  bool getPath(string dest, stack<string>& container);



  /* Accessor */

/*
 * Function name: getAllActors
 * Description: get all actors
 * Return Value: the copy of map contains all actors
 */
  unordered_map<string, Actor*> getAllActors(){return allActors;}

/*
 * Function name: getAllMovies
 * Description: get all movies
 * Return Value: the copy of map contains all movies
 */
  unordered_map<string, Movie*> getAllMovies(){return allMovies;}

/*
 * Function name: getSortedAllMovies
 * Description: get sorted movies
 * Return Value: the copy of sorted map contains all movies
 */
  set<Movie*, Movie::MoviePtrComp> getSortedAllMovies(){return sortedAllMovies;}

/*
 * Function name: findActor
 * Description: find the actor in all actors field and return an iterator
 * Return Value: the iterator point to the actor, otherwise end()
 */
  unordered_map<string, Actor*>::iterator findActor(string actor){
    return allActors.find(actor);
  }

/*
 * Function name: findMovie
 * Description: find the movie in all movies field and return an iterator
 * Return Value: the iterator point to the movie, otherwise end()
 */
  unordered_map<string, Movie*>::iterator findMovie(string movie){
    return allMovies.find(movie);
  }



  /* helper functions */

/*
 * Function name: clearAll
 * Description: clear dist, done, prev, edge fields for all actors
 */
  void clearAll();

/*
 * Function name: clearDone
 * Description: clear done field of all actors
 */
  void clearDone();

/*
 * Function name: printAll
 * Description: print out all actors and movies
 */
  void printAll();

/*
 * Function name: printMovies
 * Description: print out all movies in sorted order by year
 */
  void printMovies();

/*
 * Function name: deleteAll
 * Description: delete all alocation of all objects
 */
  void deleteAll();

};


#endif // ACTORGRAPH_HPP
