/*
 * Filename: actorconnections.cpp
 * Author: Chao Huang, Yeung-Kit Wong
 * Date: Aug 28 2016
 * Description: TODO
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include "UnionActor.hpp"
#include "UnionGraph.hpp"

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
                     "\targ4: \"bfs\" or \"ufind\", default(ufind)\n";

// output file header
const string HEADER = "Actor1\tActor2\tYear\n";


/* function prototype, function to load pairs from file */
queue< pair<string, string> > loadPairs(ifstream&);
void findConnections(UnionGraph* uGraph, queue< pair<string, string> >& target, ofstream& out);

void writeOutput();

void uFindConnections();


/**
 * Function name: main
 * Description: the main function handle the program which will take
 *              four command line arguments and find the earliest year
 *              for two actors to be connected.
 * Parameters:
 *    arg 1: name of tsv file containing  the movie casts
 *    arg 2: name of tsv file containing the names of actor pairs to find
 *    arg 3: name of output text file
 *    arg 4: search algorithm bfs/ufind
 * Return Value: 1 for success, 0 for failure.
 */
int main(int argc, char* argv[]){

  // check number of command line arguments
  if(argc < NUM_ARGC_MIN || argc > NUM_ARGC_MAX){
    cout << "\nInvalid number of arguments!\n" << USAGE;
    return 0;
  }

  // declare local variables
  ifstream inData;
  ifstream inTarget;
  ofstream outFile;

  // declare variables for command line arguments
  string data, target, out, flag;
  bool BFSflag = false;

  // initialize variables
  data = argv[DATA];
  target = argv[TARGET];
  out = argv[OUTFILE];

  // only set flag if user enters flag
  if( argc == NUM_ARGC_MAX)
    flag = argv[FLAG];

  // check validity of each command line argument
  inData.open(data, ios::binary);
  if(!inData.is_open()){
    cout << "\nInvalid arg1! Cannot open " << data << "\n" << USAGE;
    return 0;
  }
  inData.close();
  inData.open(data, ios::binary);

  if(flag != "bfs" && flag != "ufind"){
    cout << "\nInvalid arg2!\n" << USAGE;
    return 0;
  }

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

  // start to build the graph
  if(flag == "bfs") BFSflag = true;

  // skip headers of both input file
  string buf;
  getline(inData, buf);
  getline(inTarget, buf);

  UnionGraph* uGraph = new UnionGraph();

  // build the graph
  uGraph->buildGraph(inData);

  cout << "Reading " << data << " ...\n";
  cout << "#nodes: " << uGraph->getAllActors().size() << endl;
  cout << "#movies: " << uGraph->getSortedMovies().size() << endl;
  cout << "done\n";

  cout << "unsortedMovies: " << uGraph->getAllMovies().size() << endl;

  // read pairs from file
  queue< pair<string, string> > actorPairs = loadPairs( inTarget );

  uGraph->printAll();

  if(!BFSflag){
    // use uFind search
  }

  else{
    // use BFS search
  }


  // outFile header
  outFile << HEADER;

  // find the connections
  findConnections(uGraph, actorPairs, outFile);
  

  // close all files
  inData.close();
  inTarget.close();
  outFile.close();

  // delete all allocated space
  delete uGraph;

  return 1;

} // end of main


/**
 * Function name: loadPairs
 * Description: TODO
 * Parameters: TODO
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

    while (ss){

      string next;

      // get the next string before hitting a tab character and put it in 'next'
      if (!getline( ss, next, '\t' )) break;

      record.push_back( next );

    } // end of while ss

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



// a function for find the connection bewteen each pair of actor in the queue and output to ofstream
void findConnections(UnionGraph* uGraph, queue< pair<string, string> >& target, ofstream& out){

  stack<string> resultStrs;

  while(target.size()) {

    string tempStr = uGraph->uFind(target.front().first, target.front().second);

    resultStrs.push( tempStr );

    target.pop();
  }

}



// a function doing output to ofstream
void writeOutput(){

}

