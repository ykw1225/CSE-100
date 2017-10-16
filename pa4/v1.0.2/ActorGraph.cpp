
#include "ActorGraph.hpp"

using namespace std;

ActorGraph::ActorGraph(bool weighted):weighted(weighted){}

void ActorGraph::buildGraph(ifstream& in){

  // strat to load file
  while(1){

    //cout << "\n";

    // declare local variable
    string actor;
    string movie; // movie+year
    string movieName; // name of movie
    string year;
    int y;

    // get 1st block
    getline(in, actor, '\t');

    //cout << actor << "\n";

    if(in.eof()) break;

    // create an actor object on heap
    Actor* a = new Actor(actor);

    // get 2nd block
    getline(in, movieName, '\t');
    movie.append(movieName);

    //cout << "\t" << movieName << "\n";

    // get 3rd block
    getline(in, year);
    movie.append(year);

    //cout << "\t  " << year << "\n";

    // convert to int
    y = stoi(year);

    // check if movie has already been stored
    auto mItr = allMovies.find(movie);
    Movie* mPtr;

    // if this movie does not exist
    if(mItr == allMovies.end()){

      // create a movie object in heap
      mPtr = new Movie(movieName, y);

      // add this actor to actorCast set of this movie object
      mPtr->addActor(a);

      // add this movie to all movies field
      allMovies.insert(pair<string, Movie*>(movie, mPtr));
    }

    // this movie exist
    else{

      // update the movie pointer
      mPtr = (*mItr).second;

      // add this actor to actorCast set of this movie object
      mPtr->addActor(a);

    }

    // check if we haven't add any actor yet or this actor does not exist
    // then we put this actor to all actors field
    if(!allActors.size() || allActors.back()->name.compare(actor))
      addActor(a);

    // add this movie to movies set of this actor object
    allActors.back()->addMovie(mPtr);

  } // end of while

}


void ActorGraph::printAll(){
  vector<Actor*>::iterator itr = allActors.begin();
  cout << "\nStart printing graph:" << endl;
  for(;itr != allActors.end(); itr++){
    cout << "(" << (*itr)->name << ")\n";
    unordered_set<Movie*>:: iterator itrM = (*itr)->movies.begin();
    for(;itrM != (*itr)->movies.end(); itrM++){
      cout << "\t(" << (*itrM)->name << ")\n";
      cout << "\t    (" << (*itrM)->year << ")\n";
    }
  }
  cout << "Finished printing graph!" << endl;
}

void ActorGraph::deleteAll(){
  vector<Actor*>::iterator itr = allActors.begin();
  for(;itr != allActors.end(); itr++) delete (*itr);
  unordered_map<string, Movie*>::iterator itrM = allMovies.begin();
  for(;itrM != allMovies.end(); itrM++) delete (*itrM).second;
}