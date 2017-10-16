/*
 * Filename: actorconnections.cpp
 * Author: Chao Huang, Yeung-Kit Wong
 * Date: Aug 28 2016
 * Description: This file contain a main function that run a program to find the
 *              year when a pair of actor has connection to each other.
 */

#include <sstream>
#include "ActorGraph.hpp"
#include "Timer.hpp"

using namespace std;

const int DATA = 1;         // index of movie cast file
const int FLAG = 4;         // index of flag set
const int TARGET = 2;       // index of test pairs actor file
const int OUTFILE = 3;      // index of output file
const int NUM_ARGC_MAX = 5; // max number of command line arguments
const int NUM_ARGC_MIN = 4; // min number of command line arguments
const int YEAR_ERROR = 9999; // used for not connection or actor does not exist

// program usage
const string USAGE = "\nUsage: myprog arg1 arg2 arg3 arg4(optional)\n"
                     "\targ1: file1 same format as movie_casts.tsv\n"
                     "\targ2: file2 has pairs of actor name\n"
                     "\targ3: file3 the output file\n"
                     "\targ4: \"bfs\" or \"ufind\", default(ufind)\n"
                     "\t\tbfs: find connection by bfs algorithm\n"
                     "\t\tufind: find connection by disjoint set algorithm\n";

// output file header
const string HEADER = "Actor1\tActor2\tYear\n";


/* function prototypes */
queue< pair<string, string> > loadPairs(ifstream&);
void findConnections(ActorGraph*, queue< pair<string, string> >& target,
                      ofstream&, bool);
int bfsFind(ActorGraph*, string, string);


/**
 * Function name: main
 * Description: the main function handle the program which will take
 *              four command line arguments and find the link (path)
 *              for two actors and write the result in a output file.
 * Parameters:
 *    arg 1: a name of a text file contain actors and movies library
 *    arg 2: single character for flag set to indicate which kind of
 *           graph will build
 *    arg 3: a name of a text file each line contain two actors' name that need
 *           to find the link
 *    arg 4: a name of output file
 * Return Value: 1 for success, 0 for failure.
 */
int main(int argc, char* argv[]){

  // check number of command line arguments
  if(argc < NUM_ARGC_MIN || argc > NUM_ARGC_MAX){
    cout << "\nInvalid number(" << argc << ") of arguments!\n" << USAGE;
    return 0;
  }

  // declare local variables
  ifstream inData;
  ifstream inTarget;
  ofstream outFile;

  // declare variables for command line arguments
  string data, target, out, flag;
  bool bfs = false;
  bool weighted = false;

  // initialize variables
  data = argv[DATA];
  target = argv[TARGET];
  out = argv[OUTFILE];

  // check flag set for if use bfs
  if(argc == NUM_ARGC_MAX){
    flag = argv[FLAG];
    if(!flag.compare("bfs"))
      bfs = true;
  }

  // check validity of each command line argument
  inData.open(data, ios::binary);
  if(!inData.is_open()){
    cout << "\nInvalid arg1! Cannot open " << data << "\n" << USAGE;
    return 0;
  }
  inData.close();
  inData.open(data, ios::binary);

  inTarget.open(target, ios::binary);
  if(!inTarget.is_open()){
    cout << "\nInvalid arg3! Cannot open " << target << "\n" << USAGE;
    return 0;
  }
  inTarget.close();
  inTarget.open(target, ios::binary);

  outFile.open(out, ios::binary);
  if(!outFile.is_open()){
    cout << "\nInvalid arg4! Cannot open " << outFile << "\n" << USAGE;
    return 0;
  }
  outFile.close();
  outFile.open(out, ios::binary);

  // skip headers of both input file
  string buf;
  getline(inData, buf);
  getline(inTarget, buf);

  // initialize the graph
  ActorGraph* graph = new ActorGraph(weighted);

  // build the graph
  graph->buildGraph(inData);

  // printing out the report
  cout << "Reading " << data << " ...\n";
  cout << "#nodes: " << graph->getAllActors().size() << endl;
  cout << "#movies: " << graph->getAllMovies().size() << endl;
  cout << "done\n";

  // read pairs from file
  queue< pair<string, string> > actorPairs = loadPairs( inTarget );

  // outFile header
  outFile << HEADER;

  // find the connections and calculate the time spend
  Timer timer;
  timer.begin_timer();
  findConnections(graph, actorPairs, outFile, bfs);
  cout << "\nThe duration in milliseconds is : " << timer.end_timer() << endl;

  // close all files
  inData.close();
  inTarget.close();
  outFile.close();

  // delete all allocated space
  delete graph;

  cout << endl;

  return 1;

} // end of main


/**
 * Function name: loadPairs
 * Description: function that load pairs of actor from input file
 * Return Value: queue of all the actor pairs
 */
queue< pair<string, string> > loadPairs(ifstream& infile){

  // queue to store all the actor pairs
  queue<pair<string, string>> loadedPairs;

  // keep reading lines until the end of file is reached
  while (infile){

    // temporary string buffer
    string s;

    // get the next line
    if (!getline( infile, s )) break;

    // convert to string stream
    istringstream ss( s );

    // container for saving every block of string of one line
    vector <string> record;

    // if string stream still contain block
    while (ss){

      // buffer for save the block
      string next;

      // get the next string before hitting a tab character and put it in 'next'
      if (!getline( ss, next, '\t' )) break;

      // store the block into container
      record.push_back( next );

    } // end of while ss

    // check if container has correct number of block
    if (record.size() != 2)
      // we should have exactly 2 columns
      continue;

    // store a pair to the queue
    string first_actor(record[0]);
    string second_actor(record[1]);
    loadedPairs.push( make_pair( first_actor, second_actor) );

  } // end of while reading lines

  if (!infile.eof())
  {
    cerr << "Failed to read inFile!\n";
    return loadedPairs;
  }

  return loadedPairs;

}



/**
 * Function name: findConnections
 * Description: find the connection bewteen each pair of actor in the queue and
 *              output to ofstream
 * Return Value: None
 */
void findConnections(ActorGraph* graph, queue< pair<string, string> >& target,
                      ofstream& out, bool bfs){

  cout << "\n Running BFS\n";

  // declare local variables
  string start; // name of start actor
  string dest;  // name of end actor
  int year;     // the connection year of them

  // check if use bfs
  if(bfs){

    // find connections for all pairs
    while(target.size()){

      // get the name of start actor
      start = target.front().first;

      // get the name of end actor
      dest = target.front().second;

      // get the connection year of them
      year = bfsFind(graph, start, dest);

      // write these information into output file
      out << start << "\t" << dest << "\t" << year << "\n";

      // pop out the pair is already used
      target.pop();

    } // end of while

  } // end of if bfs

  // use ufind
  else{

    // TODO run ufind

  } // end of ufind

} // end of findConnections



/*
 * Function name: bfsFind
 * Description: find connection between start and dest actor by BFS
 * Return Value: the year when connection is exist, or 9999 for otherwise
 */
int bfsFind(ActorGraph* graph, string start, string dest){

  // get the iterator for both actor
  auto sItr = graph->findActor(start);
  auto dItr = graph->findActor(dest);

  // check if they are exist
  if(sItr == graph->getAllActors().end() || dItr == graph->getAllActors().end())
    return YEAR_ERROR;

  // check if two actors are the same
  if(sItr == dItr) return YEAR_ERROR;

  // initialize two ptr for both actors
  Actor* sActor = sItr->second;
  Actor* dActor = dItr->second;

  // check if we already have the connection information for this pair
  if(sActor->getConnections().find(dActor) != sActor->getConnections().end())
    return sActor->getConnections().find(dActor)->second;

  // get all movie with sorted order
  auto sortedMovies = graph->getSortedAllMovies();

  // initialize the iterator of front of sorted movies
  auto mItr = sortedMovies.begin();

  // initialize the pointer to last element
  auto endMovie = *(sortedMovies.rbegin());

  // initialize current year to the earliest year from existed movie
  int currYear = (*mItr)->getYear();

  // initialize last possible year
  int lastYear = endMovie->getYear();

  // go through all possible year
  while(currYear <= lastYear){

    // initialize container
    unordered_set<Actor*> s;

    // initialize all actors' field(dist, done, prev, edge)
    graph->clearAll();

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
      if(mItr == sortedMovies.end()){

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
