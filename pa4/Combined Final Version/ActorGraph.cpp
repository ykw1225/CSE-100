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
// constant used for not connection or actor does not exist
const int YEAR_ERROR = 9999;




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
 * Function name: bfsFind
 * Description: find connection between start and dest actor by BFS
 * Return Value: the year when connection is exist, or 9999 for otherwise
 */
int ActorGraph::bfsFind(string start, string dest){

  // get the iterator for both actor
  auto sItr = findActor(start);
  auto dItr = findActor(dest);

  // check if they are exist
  if(sItr == getAllActors().end() || dItr == getAllActors().end())
    return YEAR_ERROR;

  // check if two actors are the same
  if(sItr == dItr) return YEAR_ERROR;

  // initialize two ptr for both actors
  Actor* sActor = sItr->second;
  Actor* dActor = dItr->second;

  // check if we already have the connection information for this pair
  if(sActor->getConnections().find(dActor) != sActor->getConnections().end())
    return sActor->getConnections().find(dActor)->second;

  // initialize the iterator of front of sorted movies
  auto mItr = sortedAllMovies.begin();

  // initialize the pointer to last element
  auto endMovie = *(sortedAllMovies.rbegin());

  // initialize current year to the earliest year from existed movie
  int currYear = (*mItr)->getYear();

  // initialize last possible year
  int lastYear = endMovie->getYear();

  // go through all possible year
  while(currYear <= lastYear){

    // initialize container
    unordered_set<Actor*> s;

    // initialize all actors' field(dist, done, prev, edge)
    clearAll();

    // insert the start actor into container
    s.insert(sActor);

    // start check if connection exist for current year
    while(s.size()){

      // temporary pointer to tack current actor
      Actor* curr = *(s.begin());

      // update done field for current actor
      curr->setDone(true);

      // delete the front actor from container
      s.erase(s.begin());

      // check if a path is already found
      if(dActor->getDone()){

        // update their connection
        sActor->addConnections(dActor, currYear);
        dActor->addConnections(sActor, currYear);
        return currYear;
      }

      // go through all edges(no beyond current year) of current actor
      for(auto i: curr->getSortedMovies()){

        // check if i movie year is beyond current year
        if(i->getYear() > currYear) break;

        // go through all neighbors of current actor
        for(auto j: i->getActors()){

          // check if a path is already found
          if(dActor == j){

            // update their connection
            sActor->addConnections(dActor, currYear);
            dActor->addConnections(sActor, currYear);
            return currYear;
          }

          // check if j actor is already in the container
          if(s.find(j) != s.end()) continue;

          // check if already visited j actor
          if(!j->getDone()){

            // check if cycle loop
            if(j->getName().compare(curr->getName())){

              // check if this neighbor has edge in current year
              if((*(j->getSortedMovies().begin()))->getYear() <= currYear)

                // insert j actor into container
                s.insert(j);

            } // end of check cycle loop

          } // end of check done

        } // end of inner for

      } // end of outer for

    } // end of inner while

    // find the next possible year in sorted movies
    while((*mItr)->getYear() == currYear){

      // increment the interator
      mItr++;

      // if no more possible year;
      if(mItr == sortedAllMovies.end()){

        // update their connection
        sActor->addConnections(dActor, YEAR_ERROR);
        dActor->addConnections(sActor, YEAR_ERROR);
        return YEAR_ERROR;
      }

    } // end of while

    // update the current Year
    currYear = (*mItr)->getYear();

  } // end of outer while

  // update their connection
  sActor->addConnections(dActor, YEAR_ERROR);
  dActor->addConnections(sActor, YEAR_ERROR);

  return YEAR_ERROR;

}





/*
 * Function name: uFind
 * Description: Union find connection function
 * Return Value: the Year of connection is made between fromActor to toActor
 */
int ActorGraph::uFind(string fromActor, string toActor){

  // initialize local variable
  int connectYr = 9999;
  auto mItr = sortedAllMovies.begin();
  int firstYr = (*mItr)->getYear();

  // initialize all needed memeber of all actors
  uFindInit();

  // check if actor1 exists
  auto actor1Itr = findActor(fromActor);

  // if itr at last element, actor name doesnt match, actor not exist
  if(actor1Itr == allActors.end())
    return connectYr;

  // check if actor2 exists
  auto actor2Itr = findActor(toActor);

  // if itr at last element, actor name doesnt match, actor not exist
  if(actor2Itr == allActors.end())
    return connectYr;

  // if same actor, return ealiest year
  if(fromActor == toActor)
    return firstYr;

  // make temp ptr for each actor if exists
  Actor* fromAct = actor1Itr->second;
  Actor* toAct = actor2Itr->second;
  int currentYear;

  // iterate thru all the movies by released year
  for(auto movItr = sortedAllMovies.begin(); movItr!= sortedAllMovies.end(); ++movItr){

  currentYear = (*movItr)->getYear();
  Actor* firstActorPtr = *((*movItr)->getActors().begin());

    // merge each of the movie's actor into one set
    for(auto actItr: (*movItr)->getActors()) {
      Actor* actorToMerge = actItr;
      unionNodes(firstActorPtr, actorToMerge );
  }

    // check if fromActor and toActor in the same set after merging
    if(findRoot(fromAct)->getName() == findRoot(toAct)->getName()){
      connectYr = currentYear;
      // reset parent of all nodes
      cleanParent();
      break;
    }
  }

  // reset parent of all nodes after each search
  cleanParent();
  return connectYr;
}





/*
 * Function name: unionNodes
 * Description: union two sets of nodes set the smaller set to be subtree
 *              of the larger one
 */
void ActorGraph::unionNodes(Actor* actorA, Actor* actorB){

  // get root of the actors
  Actor* rootActorA = findRoot(actorA);
  Actor* rootActorB = findRoot(actorB);

  // if root same, in the same set, no need to union
  if(rootActorA->getName() == rootActorB->getName())
    return;

  // otherwise merge smaller set to larger one
  if(rootActorA->getSize() > rootActorB->getSize()){
    rootActorB->setParent(rootActorA);
    rootActorA->setSize(rootActorA->getSize() + rootActorB->getSize());
  }
  else{
    rootActorA->setParent(rootActorB);
    rootActorB->setSize(rootActorA->getSize() + rootActorB->getSize());
  }
}





/*
 * Function name: findRoot
 * Description: find the root node of an UnionActor object performs path
 *              compression for all the nodes it traverses
 * Return Value: the root of this upTree
 */
Actor* ActorGraph::findRoot(Actor* actor){

  // check if actor is already a root actor a root actor's parent is nullptr
  if(actor->getParent() != nullptr)
    actor->setParent(findRoot(actor->getParent()));

  if (actor->getParent() == nullptr)
    return actor;

  return actor->getParent();
}





/*
 * Function name: cleanParent
 * Description: reset parent of all the actors
 */
void ActorGraph::cleanParent() {
  for(auto i: allActors )
    i.second->setParent(nullptr);
}





/*
 * Function name: uFindInit
 * Description: initialize all actors' memebers needed for union find
 */
void ActorGraph::uFindInit() {
  for(auto i: allActors){
    i.second->setParent(nullptr);
    i.second->setSize(1);
  }
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
