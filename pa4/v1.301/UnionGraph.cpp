/*
 * Name: Chao Huang, Yeung-Kit Wong
 * Date: Aug 30, 2016
 * File: UnionGraph.cpp
 * Description:
 */

#include "UnionGraph.hpp"

using namespace std;

const int LATESTYEAR = 2015;

// prototype
std::string uFind( string fromActor, string toActor );

// function that build a graph base the input file
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



std::string UnionGraph::uFind( string fromActor, string toActor ){
   
  string resultStr = fromActor + "\t" + toActor + "\t";
  //int resultyear = 9999;
  //int currentYear = 0;

  // iterate thru all the movies by released year
  for( auto movItr = sortedMovies.begin(); movItr!= sortedMovies.end(); ++movItr){



  }


  return resultStr;
}


// function to find the root node of an UnionActor object
UnionActor* find( UnionActor* actor ) {

  UnionActor* temp = actor;

  // track parent actor til reach root
  while( temp->getParent()){
    temp = temp->getParent();
  }

  // compress path, set actor's parent to root actor
  actor->setParent( temp );

  return temp;
}

// print out all actors and movies
void UnionGraph::printAll(){
  cout << "\nAcotrs:" << endl;
  for(auto it: allActors)
    cout << it.second->getName() << "\n";

  cout << "\n";

  cout << "\nMoives: Name Year" << endl;
  for(auto itr: sortedMovies){
    cout << itr->getName() << "  "
         << itr->getYear() << "\n";
	cout << "----";
	unordered_set<UnionActor*> tempSet = itr->getActors();
	for( auto aItr = tempSet.begin(); aItr != tempSet.end(); ++aItr )
      cout << (*aItr)->getName();
	cout << "\n";
  }
   cout << "\n";
}


// delete all alocation of all objects
void UnionGraph::deleteAll(){
  for(auto i: allActors) delete i.second;
  for(auto i: allMovies) delete i.second;
}

