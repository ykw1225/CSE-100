
#include "ActorGraph.hpp"

using namespace std;

class ActorPtrComp{
public:
  bool operator()(Actor*& l, Actor*& r){return *l < *r;}
};

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

    // check if we already have this movie
    auto mItr = allMovies.find(movie);
    Movie* mPtr;

    // check if we already have this actor
    auto aItr = allActors.find(actor);
    Actor* aPtr;

    // if both actor and movie exist
    if(mItr != allMovies.end() && aItr != allActors.end()){
      aPtr = aItr->second;
      mPtr = mItr->second;
    }

    // if only actor exist
    else if(mItr == allMovies.end() && aItr != allActors.end()){

      // create a movie object in heap
      mPtr = new Movie(movieName, y);

      aPtr = aItr->second;

    }

    // if only movie exist
    else if(mItr != allMovies.end() && aItr == allActors.end()){

      // create an actor object in heap
      aPtr = new Actor(actor);

      mPtr = mItr->second;

    }

    // if both not exist
    else{
      mPtr = new Movie(movieName, y);
      aPtr = new Actor(actor);
    }

    aPtr->addMovie(mPtr);
    mPtr->addActor(aPtr);
    addActor(actor, aPtr);
    addMovie(movie, mPtr);

  } // end of while

}

bool ActorGraph::findPath(string start, string end){

  //cout << "\nStart findPath:\n";

  // check if both actor exist
  auto sItr = allActors.find(start);
  auto eItr = allActors.find(end);

  // one of actors or both don't exist
  if(sItr == allActors.end()){
    cout << "\t\tStart Actor (" << start << ")doesn't exist!\n";
    return false;
  }
  if(eItr == allActors.end()){
    cout << "\t\tEnd Actor (" << end << ")doesn't exist!\n";
    return false;
  }

  // declare two actors' pointer
  Actor* startPtr = (*sItr).second;
  Actor* endPtr = (*eItr).second;

  // initialize all actors' dist, done, prev field
  clearAll();

  // initialize the dist of start vertex
  startPtr->setDist(0);

  // if two actors are the same name
  if(!startPtr->name.compare(endPtr->name)){
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

    //cout << "\n\tCurrent(" << curr->name << ")\n";
    //cout << "\tSize of movies(" << curr->movies.size() << ")\n";

    // dequeue the lowest dist actor in pq
    pq.pop();

    // set its path is found
    curr->setDone(true);

    //if(curr->prevActor) cout << "\t(" << curr->prevActor->name << ")(" <<
            //curr->edge->name << ")(" << curr->dist << ")(" << curr->done << ")\n";

    // for every edges of current actor
    for(auto i: curr->movies){

      //cout << "\t\tMovies(" << i->name << ")\n";

      // for every actor of i movie
      for(auto j: i->actorCast){

        //cout << "\t\t\tActor(" << j->name << ")\n";

        // check if it is a self loop
        if(curr->name.compare(j->name)){

          // check if the new dist is shorter
          if((curr->dist+1) < j->dist){
            j->setPrev(curr);
            j->setEdge(i);
            j->setDist(curr->dist+1);
            pq.push(j);
            //cout << "\t(" << j->name << ")(" << j->prevActor->name << ")(" <<
            //j->edge->name << ")(" << j->dist << ")(" << j->done << ")\n";
          }
          //else cout << "no update!\n";
        }
        //else cout << "Selfloop\n";
      } // end of inner for
    } // end of outer for
  } // end of while

  //cout << "Finished findPath!\n";
  return true;
}

bool ActorGraph::getPath(string end, stack<string>& s){
  //cout << "\n\tStart getPath:\n";
  if(s.size()){
    //cout << "\t\t not empty stack!\n";
    //cout << "\tFinished getPath!\n\n";
    return false;
  }
  auto curr = (*(allActors.find(end))).second;
  if(!curr){
    //cout << "\t\t actorc(" << end << ") doesn't exist!\n";
    //cout << "\tFinished getPath!\n\n";
    return false;
  }
/*
  int count =0;

  cout << "\nActor:(" << curr->name << ")\n"
       << "done:(" << curr->done << ")\n";

  if(curr->prevActor)
       cout << "prev:(" << curr->prevActor->name << ")\n";
  if(curr->edge)
       cout << "edge:(" << curr->edge->name << ")\n";
  cout << endl;*/

  bool first = true;

  while(curr->prevActor){
    //cout << "\t\t\t count = " << count << "\n";
    if(curr->done == false || curr->dist < 0){
      //cout << "\t\t done is false or dist less than 0!\n";
      //cout << "\tFinished getPath!\n\n";
      return false;
    }
    if(first){
      first = false;
      s.push(curr->name);
    }
    s.push(to_string(curr->edge->year));
    s.push(curr->edge->name);
    s.push(curr->prevActor->name);
    curr = curr->prevActor;
    //count++;
  }

  //cout << "\tFinished getPath!\n\n";
  return true;
}

void ActorGraph::clearAll(){
  for(auto i: allActors)
    i.second->clear();
}

void ActorGraph::printAll(){
  cout << "\nStart printing graph:" << endl;
  for(auto i: allActors){
    cout << "(" << i.second->name << ")\n";
    for(auto j: i.second->movies){
      cout << "\t(" << j->name << ")\n";
      cout << "\t    (" << j->year << ")\n";
      for(auto k: j->actorCast){
        cout << "\t\t(" << k->name << ") movies(" << k->movies.size() << ")\n";
        if(k == i.second) cout << "\t\tSame actor!\n";
      }
    }
  }
  cout << "Finished printing graph!" << endl;
}

void ActorGraph::deleteAll(){
  for(auto i: allActors) delete i.second;
  for(auto i: allMovies) delete i.second;
}