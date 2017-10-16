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

  // declare local variables
  string start; // name of start actor
  string dest;  // name of end actor
  int year;     // the connection year of them

  // check if use bfs
  if(bfs){

    cout << "\n Running BFS\n";

    // find connections for all pairs
    while(target.size()){

      // get the name of start actor
      start = target.front().first;

      // get the name of end actor
      dest = target.front().second;

      // get the connection year of them
      year = graph->bfsFind(start, dest);

      // write these information into output file
      out << start << "\t" << dest << "\t" << year << "\n";

      // pop out the pair is already used
      target.pop();

    } // end of while

  } // end of if bfs

  // use ufind
  else{

    cout << "\n Running Union Find\n";

    // find connections for all pairs
    while(target.size()) {

      // get the name of start actor
      start = target.front().first;

      // get the name of end actor
      dest = target.front().second;

      // get the connection year of them
      year  = graph->uFind(start, dest);

      // write these information into output file
      out << start << "\t" << dest << "\t" << year << "\n";

      // pop out the pair is already used
      target.pop();

    } // end of while

  } // end of ufind

} // end of findConnections