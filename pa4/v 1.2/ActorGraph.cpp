
#include "ActorGraph.hpp"

using namespace std;

const int LATESTYEAR = 2015;



// comparison class for actor pointer
class ActorPtrComp{
public:
  bool operator()(Actor*& l, Actor*& r){return *l < *r;}
};



// function that build a graph base the input file
void ActorGraph::buildGraph(ifstream& in){

  // strat to load file
  while(1){

//cout << "\n";

    // declare local variable

    // name of actor
    string actor;

    // movie+year
    string movie;

    // name of movie
    string movieName;

    // year of movie in string
    string year;

    // year of movie in integer
    int y;

    // weight of movie
    int weight = 1;

    // get 1st block
    getline(in, actor, '\t');

//cout << actor << "\n";

    if(in.eof()) break;

    // get 2nd block
    getline(in, movieName, '\t');

//cout << "\t" << movieName << "\n";

    // get 3rd block
    getline(in, year);

    // the movie key which include movie's name and year in string
    movie.append(movieName);
    movie.append(year);

//cout << "\t  " << year << "\n";

    // convert year string to int
    y = stoi(year);

    // check if the graph is weighted or unweighted
    if(weighted) weight = 1+(LATESTYEAR-y);

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
      mPtr = new Movie(movieName, y, weight);

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
      mPtr = new Movie(movieName, y, weight);

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



// find the shortest path from start actor to end actor
bool ActorGraph::findPath(string start, string dest){

//cout << "\nStart findPath:\n";

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

//cout << "Max int: " << numeric_limits<int>::max() << endl;
//printAll();

  // initialize the dist of start vertex
  startPtr->setDist(0);

  // if two actors are the same name
  if(!startPtr->getName().compare(endPtr->getName())){

//cout << "\t\t two actors are the same!\n";
//cout << "Finished findPath!\n";

    return true;
  }

  // declare the priority queue
  priority_queue<Actor*, vector<Actor*>, ActorPtrComp> pq;

  // enqueue the start vertex
  pq.push(startPtr);

  // start finding the shortest path
  while(pq.size()){

    // temporary pointer to track current actor
    Actor* curr = pq.top();

/*
cout << "\tQueue:\n";
vector<Actor*> v;
while(pq.size()){
Actor* a = pq.top();
v.push_back(a);
pq.pop();}
for(auto i: v){cout << "\t" << i->toString() << "\n";pq.push(i);}
cout << endl;
*/

    // dequeue the lowest dist actor in pq
    pq.pop();

    // set its path is found
    curr->setDone(true);

//cout << "\n\tCurrent Actor: " << curr->toString() << "\n";
//cout << "\t\tMovies:\n";

    // for every i movie of current actor
    for(auto i: curr->getMovies()){

//cout << "\t\t   " << i->toString() << "\n";
//cout << "\t\tActor:\n";

      // for every j actor of i movie
      for(auto j: i->getActors()){

//cout << "\t\t   " << j->toString() << "\n";

        // check if it is a self loop
        if(curr->getName().compare(j->getName())){

          int newDist = curr->getDist() + i->getWeight();

//cout << "\t\t\tNewdist = " << newDist << ") Olddist = " << j->getDist() << ")\n";

          // check if the new dist is shorter
          if(newDist < j->getDist()){

            // update all field for j movie
            j->setPrev(curr);
            j->setEdge(i);
            j->setDist(newDist);
            pq.push(j);

//cout << "\t" << j->toString() << "\n";

          } // end of check dist

//else cout << "no update!\n";

        } // end of check self loop

//else cout << "Selfloop\n";

      } // end of inner for
    } // end of outer for
  } // end of while

//cout << "Finished findPath!\n";

  return true;

}



// save the shortest path into the stack
bool ActorGraph::getPath(string dest, stack<string>& container){

//cout << "\n\tStart getPath:\n";

  // check if empty stack
  if(container.size()){

//cout << "\t\t not empty stack!\n";
//cout << "\tFinished getPath!\n\n";

    return false;

  }

  // get the destination actor of path
  auto curr = findActor(dest)->second;

/*
if(!curr){cout << "\t\t actorc(" << end << ") doesn't exist!\n";cout << "\tFinished getPath!\n\n";return false;}
cout << "\nActor:(" << curr->name << ")\n"<< "done:(" << curr->done << ")\n";
if(curr->prevActor)cout << "prev:(" << curr->prevActor->name << ")\n";
if(curr->edge)cout << "edge:(" << curr->edge->name << ")\n";cout << endl;
*/

  // boolean to determind if first time iteration
  bool first = true;

  // start traverse backward from dest actor to start actor to get the path
  while(curr->getPrev()){

/*
cout << "\t\t\t count = " << count << "\n";
if(curr->done == false || curr->dist < 0){
cout << "\t\t done is false or dist less than 0!\n";
cout << "\tFinished getPath!\n\n";
return false;
}
*/
    // check if first time iteration
    if(first){

      // update the variable to false
      first = false;

      // put the name of destination actor's name
      container.push(curr->getName());

    }

    // put the year of movie(edge)
    container.push(to_string(curr->getEdge()->getYear()));

    // put the name of movie(edge)
    container.push(curr->getEdge()->getName());

    // put the name of actor(vertex)
    container.push(curr->getPrev()->getName());

    // update current vertex to previous vertex
    curr = curr->getPrev();

  }

//cout << "\tFinished getPath!\n\n";

  return true;

}



// clear dist, done, prev fields for all actors
void ActorGraph::clearAll(){
//cout << "\nStart clearAll():\n";
  for(auto i: allActors)
    i.second->clear();
//cout << "\nFinsihed clearAll()!\n";
}



// print out all actors and movies
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



// delete all alocation of all objects
void ActorGraph::deleteAll(){
  for(auto i: allActors) delete i.second;
  for(auto i: allMovies) delete i.second;
}
