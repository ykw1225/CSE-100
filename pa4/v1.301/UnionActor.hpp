/*
 * Name: Chao Huang, Yeung-Kit Wong
 * Date: Aug 25, 2016
 * File: UnionActor.hpp
 * Description:
 */

#ifndef UNIONACTOR_HPP
#define UNIONACTOR_HPP

#include <string>
#include "UnionMovie.hpp"

using namespace std;

class UnionMovie;

// a class represent an actor(Vertex in graph)
class UnionActor{
private:

  /* All fields */

  // actor's name
  string name;

  // previous actor
  UnionActor* parent;

public:

  /* All functions */

  // constructor
  UnionActor(string name):name(name){clear();}

  // set the parent actor
  void setParent(UnionActor* parentActor){ parent = parentActor;}

  // clear three member for find shortest path
  void clear(){
    setParent(nullptr);
  }

  // get name
  string getName(){return name;}

  // get parent actor
  UnionActor* getParent(){return parent;}

};

#endif
