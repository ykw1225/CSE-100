/*
 * Filename: pathfinder.cpp
 * Author: Chao Huang, Yeung-Kit Wong
 * Date: Aug 24 2016
 * Description: TODO
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <queue>
#include "ActorGraph.hpp"
#include "Timer.hpp"

using namespace std;

const int DATA = 1;     // index of movie cast file
const int FLAG = 2;     // index of flag set
const int TARGET = 3;   // index of test pairs actor file
const int OUTFILE = 4;  // index of output file
const int NUM_ARGC = 5; // number of command line arguments

// program usage
const string USAGE = "\nUsage: myprog arg1 arg2 arg3 arg4\n"
                     "\targ1: file1 same format as movie_casts.tsv\n"
                     "\targ2: character 'w' or 'u'\n"
                     "\t\tu: build the graph with unweighted edges\n"
                     "\t\tw: build the graph with weighted edges\n"
                     "\targ3: file2 pairs of actors for find paths\n"
                     "\targ4: file3 the output file\n";

// output file header
const string HEADER = "(actor)--[movie#@year]-->(actor)--...\n";


/* function prototype, function to load pairs from file */
queue< pair<string, string> > loadPairs(ifstream&);

void writeOutput(stack<string>&, ofstream&);

void findPath(ActorGraph*, queue<pair<string, string>>&, ofstream&);


/**
 * Function name: main
 * Description: the main function handle the program which will take
 *              four command line arguments and find the link (path)
 *              for two actors and write the result in a output file.
 * Parameters:
 *    arg 1: a name of a text file contain actors and movies library
 *    arg 2: single character for flag set to indicate which kind of graph will build
 *    arg 3: a name of a text file each line contain two actors' name that need to find the link
 *    arg 4: a name of output file
 * Return Value: 1 for success, 0 for failure.
 */
int main(int argc, char* argv[]){

  // check number of command line arguments
  if(argc != NUM_ARGC){
    cout << "\nInvalid number of arguments!\n" << USAGE;
    return 0;
  }

  // declare local variables
  ifstream inData;
  ifstream inTarget;
  ofstream outFile;

  // declare variables for command line arguments
  string data, target, out;
  char flag;
  bool weighted;

  // initialize variables
  data = argv[DATA];
  flag = argv[FLAG][0];
  target = argv[TARGET];
  out = argv[OUTFILE];

  // check validity of each command line argument
  inData.open(data, ios::binary);
  if(!inData.is_open()){
    cout << "\nInvalid arg1! Cannot open " << data << "\n" << USAGE;
    return 0;
  }
  inData.close();
  inData.open(data, ios::binary);

  if(flag != 'w' && flag != 'u'){
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
  if(flag == 'u') weighted = false;
  else weighted = true;

  // skip headers of both input file
  string buf;
  getline(inData, buf);
  getline(inTarget, buf);

//cout << buf << endl;

  ActorGraph* graph = new ActorGraph(weighted);

  // build the graph
  graph->buildGraph(inData);

//auto sortedMovies = graph->getSortedMovies();

//cout << "\nSorted Movies' size: " << sortedMovies.size() << endl;

//graph->printMovies();

//return 1;

  cout << "Reading " << data << " ...\n";
  cout << "#nodes: " << graph->getAllActors().size() << endl;
  cout << "#movies: " << graph->getAllMovies().size() << endl;
  cout << "done\n";

//graph->printAll();
//cout << "#of actors in movie_cast file: " << graph-> allActors.size() << endl;
//cout << "#of movies in movie_cast file: " << graph-> allMovies.size() << endl;

  // read pairs from file
  queue< pair<string, string> > actorPairs = loadPairs( inTarget );

  // outFile header
  outFile << HEADER;

  // find the path
  Timer timer;
  timer.begin_timer();
  findPath(graph, actorPairs, outFile);
  cout << "\nTakes " << timer.end_timer() << "  milliseconds!\n";


//cout << "#of pairs in file: " << actorPairs.size() << endl;
//cout << "---------------------------------------------\n";

// iterate thru each actor pair
/*while( !actorPairs.empty() ) {
  cout << actorPairs.front().first << "\t" << actorPairs.front().second << endl;
actorPairs.pop();
}*/

  // close all files
  inData.close();
  inTarget.close();
  outFile.close();

  // delete all allocated space
  delete graph;

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



// a function for find the path bewteen each pair of actor in the queue and output to ofstream
void findPath(ActorGraph* graph, queue< pair<string, string> >& target, ofstream& out){

  // boolean for indicate if findPath success
  bool find = true;

  // boolean for indicate if getPath success
  bool get = true;

  // container for save the path
  stack<string> s;

//cout << "\nStart findPath:\n\n";

  // start finding the path
  while(target.size()){

//cout << "size of queue:" << target.size() << endl;

    cout << "Computing path for (" << target.front().first
           << ") -> (" << target.front().second << ")\n";

    // start find the path
    find = graph->findPath(target.front().first, target.front().second);

    // findpath success
    if(find){

//cout << "\tFindpath success!\n";

      // get the path
      get = graph->getPath(target.front().second, s);

      // if getpath success
      if(get){

//cout << "\tGetpath success!\n";

        // write the path to output file
        writeOutput(s, out);

      } // end of if get
    } // end of if find

    // if fail to find path
    else return;

//else cout << "\tFindpath fail!\n";

    // pop out the pair of actor is used
    target.pop();

  } // end of while

//cout << "\nFinished findPath!\n\n";
}



// a function doing output the path to ofstream action
void writeOutput(stack<string>& s, ofstream& out){

//cout << "\n\tStart output:\n";
//cout << "\t\tsizeof stack: " << s.size() << "\n";
//cout << "\tPath:\n";

  // start to write the path
  while(s.size()){

//cout << "\t\t(" << s.top() << ")\n";

    // write the actor's name
    out << "(" << s.top() << ")";
    s.pop();

    // write the movie's year
    if(s.size()){
      out << "--[" << s.top() << "#@";
      s.pop();
    }

    // write the movie's name
    if(s.size()){
      out << s.top() << "]-->";
      s.pop();
    }

  }// end of while

  // write a newline character
  out << "\n";

//cout << "\tFinished output!\n\n";
}

