/*
 * Name: Chao Huang, Yeung-Kit Wong
 * Date: Aug 30, 2016
 * File: UnionActor.hpp
 * Description: Header file of UnionActor object for uFind
 *              declares class members, and function prototypes
 */

#ifndef UNIONACTOR_HPP
#define UNIONACTOR_HPP

#include <string>
#include "UnionMovie.hpp"

using namespace std;

class UnionMovie;

/** a class represent an actor(Vertex in union graph)
 *  also saves the name and parent actor of this actor
 */
class UnionActor{
private:

  // actor's name
  string name;

  // size of the upTree
  int size;

public:

  // constructor
  UnionActor(string name):name(name){clear();}

  // parent actor
  UnionActor* parent;

  /** Function name: clean
   *  Description: futnion to reset parent actor of all the actors
   */
  void clear(){
    size = 1;
    parent = nullptr; //parent is nullptr by default
  }

  /* function to return this actor's name */
  string getName(){return name;}

  /* function to return the size of the upTree stored in the root actor */
  int getSize() {return size;}

  /* function to update a root's size */
  void setSize(int updatedsiz) { size = updatedsiz;}
};

#endif
