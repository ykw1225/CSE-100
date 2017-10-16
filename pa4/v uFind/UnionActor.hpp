/*
 * Name: Chao Huang, Yeung-Kit Wong
 * Date: Aug 30, 2016
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

  // actor's name
  string name;

  // size of the upTree
  int size;

public:

  // constructor
  UnionActor(string name):name(name){clear();}

  // parent actor
  UnionActor* parent;

  // set the parent actor
  //void setParent(UnionActor* parentActor){ parent = parentActor;}

  // clear three member for find shortest path
  void clear(){
    size = 1;
    parent = nullptr;
  }

  // get name
  string getName(){return name;}

  // get parent actor
  //UnionActor* getParent(){return parent;}

  // get size of the upTree
  int getSize() {return size;}

  // set size
  void setSize(int updatedsiz) { size = updatedsiz;}
};

#endif
