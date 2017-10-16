/*
 * Name: Chao Huang, Yeung-Kit Wong
 * Date: Aug 30, 2016
 * File: UnionGraph.cpp
 * Description: Cpp file of UnionGraph class, contains implementation
 *              of all the class functions, builds a UnionGraph for uFind
 */

#include "UnionGraph.hpp"
#include <string>

using namespace std;

// class function prototype
std::string uFind( string fromActor, string toActor );
UnionActor* findRoot(UnionActor* actor); 
void unionNodes( UnionActor* actorA, UnionActor* actorB);

/**
 * Function name: buildGraph
 * Description: function to build the graph
 */
void UnionGraph::buildGraph(ifstream& in){

  // strat to load file
  while(1){

    // declare local variable

    // name of actor
    string actorName;

    // movie+year
    string movieKey;

    // name of movie
    string movieName;

    // year of movie in string
    string year;

    // year of movie in integer
    int y;

    // get 1st block
    getline(in, actorName,'\t');

    if(in.eof()) break;

    // get 2nd block
    getline(in, movieName, '\t');

    // get 3rd block
    getline(in, year);

    // the movie key which include movie's name and year in string
    movieKey.append(movieName);
    movieKey.append(year);


    // convert year string to int
    y = stoi(year);

    // check if we already have this movie
    auto mItr = findMovie(movieKey);

    // temporary pointer to track movie
    UnionMovie* mPtr;

    // temporary pointer to tack actor
    UnionActor* aPtr;

    // check if we already have this actor
    auto aItr = findActor(actorName);

    // if movie already exist
    if(mItr != allMovies.end()) 
      // make the pointer to the movie exist
      mPtr = mItr->second;
	else
      // create a movie object in heap
      mPtr = new UnionMovie(movieName, y);

    // if actor already exist
	if (aItr != allActors.end()) 
      // make the pointer to the actor exist
      aPtr = aItr->second;
	else 
      // create an actor object in heap
      aPtr = new UnionActor(actorName);

    // make the connection between actor and movie
    mPtr->addActor(aPtr);

    // add actor and movie to allActors and allMovies field
    addActor(actorName, aPtr);
    addMovie(movieKey, mPtr);

  } // end of while

  //sort all the movies by year, store in map
  for(auto itr = allMovies.begin(); itr!= allMovies.end(); ++itr){
    addSortMovie( itr->second );
  }

} // end of build


/**
 * Function name: uFind
 * Description: use union find to search earliest year two actors gets
 *              connected. Takes name of two actors as parameter,
 *              returns the connected year. 
 */
int UnionGraph::uFind( string fromActor, string toActor ){
   
  int connectYr = 9999;
  auto mItr = sortedMovies.begin();
  int firstYr = (*mItr)->getYear();

  // check if actor1 exists
  auto actor1Itr = findActor(fromActor);

  // if itr at last element, actor name doesnt match, actor not exist 
  //if( actor1Itr == allActors.end() && actor1Itr->second->getName() != fromActor )
  if( actor1Itr == allActors.end() ) 
    return connectYr;

  // check if actor2 exists
  auto actor2Itr = findActor(toActor);

  // if itr at last element, actor name doesnt match, actor not exist 
  //if( actor2Itr == allActors.end() && actor2Itr->second->getName() != toActor )
  if( actor2Itr == allActors.end() )
    return connectYr;

  // if same actor, return ealiest year 
  if ( fromActor == toActor )
    return firstYr;

  // make temp ptr for each actor if exists
  UnionActor* fromAct = actor1Itr->second;
  UnionActor* toAct = actor2Itr->second;
  int currentYear;

  // iterate thru all the movies by released year
  for( auto movItr = sortedMovies.begin(); movItr!= sortedMovies.end(); ++movItr){

	currentYear = (*movItr)->getYear();
    UnionActor* firstActorPtr = *((*movItr)->getActors().begin());

    // merge each of the movie's actor into one set
    for( auto actItr: (*movItr)->getActors()) {
      UnionActor* actorToMerge = actItr;
      unionNodes( firstActorPtr, actorToMerge );
	}

    // check if fromActor and toActor in the same set after merging
    if( findRoot(fromAct)->getName() == findRoot(toAct)->getName() ){
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


/** Function name: findRoot
 *    function to find the root node of an UnionActor object,
 *    performs path compression for all the nodes it traverses
 */

UnionActor* UnionGraph::findRoot( UnionActor* actor ) {

  // check if actor is already a root actor
  // a root actor's parent is nullptr
  if ( actor->parent != nullptr ) {
    actor->parent = findRoot(actor->parent);
  }

  if (actor->parent == nullptr) {
    return actor;
  }

  return actor->parent;
}


/** Function name: unionNodes
 *   function to union two sets of actors
 *   set the smaller set to be subtree of the larger one
 */
void UnionGraph::unionNodes( UnionActor* actorA, UnionActor* actorB ){

  // get root of the actors
  UnionActor* rootActorA = findRoot(actorA);
  UnionActor* rootActorB = findRoot(actorB);

  // if root same, in the same set, no need to union
  if( rootActorA->getName() == rootActorB->getName() )
    return;

  // otherwise merge smaller set to larger one
  if( rootActorA->getSize() > rootActorB->getSize() ){
    rootActorB->parent = rootActorA;
    rootActorA->setSize( rootActorA->getSize() + rootActorB->getSize() );
  }
  else {
    rootActorA->parent = rootActorB;
    rootActorB->setSize( rootActorA->getSize() + rootActorB->getSize() );
  }
}


/** Function name: cleanParent:
 *  Description: futnion to reset parent actor of all the actors
 *               each time after looking for a connection
 */
void UnionGraph::cleanParent() {
  for(auto i: allActors )
    i.second->parent = nullptr;
}


/**
 * Function name: deleteAll
 * Description: delete all alocation of all objects
 */
void UnionGraph::deleteAll(){
  for(auto i: allActors) delete i.second;
  for(auto i: allMovies) delete i.second;
}

