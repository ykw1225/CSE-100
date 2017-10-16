/*
 * Name: Chao Huang, Yeung-Kit Wong
 * Date: Aug 25, 2016
 * File: ActorGraph.cpp
 * Description: cpp file that implement member functions of ActorGraph class
 */

#include "ActorGraph.hpp"

using namespace std;

// constant for latest possible year
const int LATESTYEAR = 2015;





/*
 * Function name: buildGraph
 * Description: function for building the graph
 */
void ActorGraph::buildGraph(ifstream& in){

  // strat to load file
  while(1){

    /* declare local variable */

    // name of actor
    string actor;

    // movie+year
    string movie;

    // name of movie
    string movieName;

    // year of movie in string
    string year;

    // year of movie in integer
    int yearInt;

    // weight of movie
    int weight = 1;

    // get 1st block
    getline(in, actor, '\t');

    // skip the newline character
    if(in.eof()) break;

    // get 2nd block
    getline(in, movieName, '\t');

    // get 3rd block
    getline(in, year);

    // the movie key which include movie's name and year in string
    movie.append(movieName);
    movie.append(year);

    // convert year string to int
    yearInt = stoi(year);

    // check if the graph is weighted or unweighted
    if(weighted) weight = 1+(LATESTYEAR-yearInt);

    // check if we already have this movie
    auto mItr = findMovie(movie);

    // temporary pointer to tack movie
    Movie* mPtr;

    // check if we already have this actor
    auto aItr = findActor(actor);

    // temporary pointer to tack actor
    Actor* aPtr;

    // if both actor and movie exist
    if(mItr != allMovies.end() && aItr != allActors.end()){

      // make the pointer to the actor exist
      aPtr = aItr->second;

      // make the pointer to the movie exist
      mPtr = mItr->second;

    }

    // if only actor exist
    else if(mItr == allMovies.end() && aItr != allActors.end()){

      // create a movie object in heap
      mPtr = new Movie(movieName, yearInt, weight);

      // make the pointer to the actor exist
      aPtr = aItr->second;

    }

    // if only movie exist
    else if(mItr != allMovies.end() && aItr == allActors.end()){

      // create an actor object in heap
      aPtr = new Actor(actor);

      // make the pointer to the movie exist
      mPtr = mItr->second;

    }

    // if both not exist
    else{

      // create a movie object in heap
      mPtr = new Movie(movieName, yearInt, weight);

      // create an actor object in heap
      aPtr = new Actor(actor);

    }

    // make the connection between actor and movie
    aPtr->addMovie(mPtr);
    mPtr->addActor(aPtr);

    // add actor and movie to allActors and allMovies field
    addActor(actor, aPtr);
    addMovie(movie, mPtr);

  } // end of while

} // end of build





/*
 * Function name: findPath
 * Description: find the shortest path from start actor to dest actor
 * Return Value: true for successfully find the path, otherwise false
 */
bool ActorGraph::findPath(string start, string dest){

  // check if both actor exist
  auto sItr = findActor(start);
  auto eItr = findActor(dest);

  // start actor doesn't exist
  if(sItr == allActors.end()){

    // print out the warning
    cout << "\t\tStart Actor (" << start << ")doesn't exist!\n";
    return false;

  }

  // end actor doesn't exist
  if(eItr == allActors.end()){

    // print out the warning
    cout << "\t\tEnd Actor (" << dest << ")doesn't exist!\n";
    return false;

  }

  // declare two actors' pointers
  Actor* startPtr = sItr->second;
  Actor* endPtr = eItr->second;

  // initialize all actors' dist, done, prev field
  clearAll();

  // initialize the dist of start vertex
  startPtr->setDist(0);

  // if two actors are the same name
  if(!startPtr->getName().compare(endPtr->getName())){

    return true;
  }

  // declare the container
  set<Actor*, Actor::ActorPtrComp> s;

  // insert the start vertex
  s.insert(startPtr);

  // start finding the shortest path
  while(s.size()){

    // temporary pointer to track current actor
    Actor* curr = *(s.begin());

    // delete the lowest dist actor from container
    s.erase(s.begin());

    // set its path is found
    curr->setDone(true);

    // check if the shortest path to end actor is already found
    if(endPtr->getDone()) break;

    // for every i movie of current actor
    for(auto i: curr->getMovies()){

      // for every j actor of i movie
      for(auto j: i->getActors()){

        // check if it is done
        if(!j->getDone()){

          // check if it is a self loop
          if(curr->getName().compare(j->getName())){

            // initialize the new dist
            int newDist = curr->getDist() + i->getWeight();

            // check if the new dist is shorter
            if(newDist < j->getDist()){

              // update all field for j movie
              j->setPrev(curr);
              j->setEdge(i);
              j->setDist(newDist);

              // insert the j actor to the container
              s.insert(j);

            } // end of check dist

          } // end of check self loop

        } // end of check if done

      } // end of inner for

    } // end of outer for

  } // end of while

  return true;

}





/*
 * Function name: getPath
 * Description: save the shortest path into the stack
 * Return Value: true for successfully get the path, otherwise false
 */
// save the shortest path into the stack
bool ActorGraph::getPath(string dest, stack<string>& container){

  // check if empty stack
  if(container.size()) return false;

  // get the destination actor of path
  auto curr = findActor(dest)->second;

  // boolean to determind if first time iteration
  bool first = true;

  // start traverse backward from dest actor to start actor to get the path
  while(curr->getPrev()){

    // check if first time iteration
    if(first){

      // update the variable to false
      first = false;

      // put the name of destination actor's name
      container.push(curr->getName());

    } // end of if 1st time

    // put the year of movie(edge)
    container.push(to_string(curr->getEdge()->getYear()));

    // put the name of movie(edge)
    container.push(curr->getEdge()->getName());

    // put the name of actor(vertex)
    container.push(curr->getPrev()->getName());

    // update current vertex to previous vertex
    curr = curr->getPrev();

  } // end of while

  return true;

}





/*
 * Function name: clearAll
 * Description: clear dist, done, prev, edge fields for all actors
 */
void ActorGraph::clearAll(){
  for(auto i: allActors)
    i.second->clear();
}





/*
 * Function name: clearDone
 * Description: clear done field of all actors
 */
void ActorGraph::clearDone(){
  for(auto i: allActors)
    i.second->setDone(false);
}





/*
 * Function name: printAll
 * Description: print out all actors and movies
 */
void ActorGraph::printAll(){
  cout << "\nStart printing graph:" << endl;
  for(auto i: allActors){
    cout << i.second->toString() << "\n";
    for(auto j: i.second->getMovies()){
      cout << "\t" << j->toString() << "\n";
      for(auto k: j->getActors()){
        cout << "\t\t" << k->toString() << "\n";
        if(k == i.second) cout << "\t\tSelf loop!\n";
      }
    }
  }
  cout << "Finished printing graph!" << endl;
}





/*
 * Function name: printMovies
 * Description: print out all movies in sorted order by year
 */
void ActorGraph::printMovies(){
  cout << "\nStart printing movies in sorted order by year:\n";
  for(auto i: sortedAllMovies)
    cout << "\t" << i->toString() << "\n";
  cout << "\nFinished printing!\n";
}





/*
 * Function name: deleteAll
 * Description: delete all alocation of all objects
 */
void ActorGraph::deleteAll(){
  for(auto i: allActors) delete i.second;
  for(auto i: allMovies) delete i.second;
}
