/*
 * Filename: pathfinder.cpp
 * Author: Chao Huang, Yeung-Kit Wong
 * Date: Aug 24 2016
 * Description: TODO
 */

#include <iostream>
#include <fstream>
#include <cstdio>
#include <queue>
#include "ActorGraph.hpp"

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


/* function prototype, function to load pairs from file */
queue< pair<string, string> > loadPairs(ifstream&);

void writeOutput(stack<string>&, ofstream&);

void findPath(ActorGraph*, queue<pair<string, string>>&, ofstream&);


/**
 * Function name: main
 * Description: TODO
 * Parameters: TODO
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

  // skip the header
  string buf;
  getline(inData, buf);
  //cout << buf << endl;

  ActorGraph* graph = new ActorGraph(weighted);

  graph->buildGraph(inData);

  //graph->printAll();

  //graph->printAll();
  //cout << "#of actors in movie_cast file: " << graph-> allActors.size() << endl;
  //cout << "#of movies in movie_cast file: " << graph-> allMovies.size() << endl;

  // read pairs from file
  queue< pair<string, string> > actorPairs = loadPairs( inTarget );

  // outFile header
  outFile << "(actor)--[movie#@year]-->(actor)--...\n";

  findPath(graph, actorPairs, outFile);


  //cout << "#of pairs in file: " << actorPairs.size() << endl;
  //cout << "---------------------------------------------\n";

  // iterate thru each actor pair
  /*while( !actorPairs.empty() ) {
    cout << actorPairs.front().first << "\t" << actorPairs.front().second << endl;
  actorPairs.pop();
  }*/


  delete graph;

  return 1;

} // end of main


/**
 * Function name: loadPairs
 * Description: TODO
 * Parameters: TODO
 * Return Value: queue of all the actor pairs
 */
queue< pair<string, string> > loadPairs(ifstream& infile)
{

  // queue to store all the actor pairs
  queue<pair<string, string>> loadedPairs;

  bool have_header = false;

  // keep reading lines until the end of file is reached
  while (infile)
  {
    string s;

    // get the next line
    if (!getline( infile, s )) break;

    if (!have_header)
    {
      // skip the header
      have_header = true;
      continue;
    }

    istringstream ss( s );
    vector <string> record;

    while (ss)
    {
      string next;

      // get the next string before hitting a tab character and put it in 'next'
      if (!getline( ss, next, '\t' )) break;

      record.push_back( next );
    }

    if (record.size() != 2)
    {
      // we should have exactly 2 columns
      continue;
    }

  // store a pair to the queue
    string first_actor(record[0]);
    string second_actor(record[1]);

  loadedPairs.push( make_pair( first_actor, second_actor) );
  }

  if (!infile.eof())
  {
    cerr << "Failed to read inFile!\n";
    return loadedPairs;
  }
  infile.close();

  return loadedPairs;

}

void findPath(ActorGraph* graph, queue< pair<string, string> >& target, ofstream& out){
  string prev;
  bool first = true;
  stack<string> s;

  //cout << "\nStart findPath:\n\n";

  while(target.size()){
    //cout << "size of queue:" << target.size() << endl;
    if(!first){
      first = false;
      if(!prev.compare(target.front().first)) continue;
    }
    else{
      bool x = graph->findPath(target.front().first, target.front().second);
      if(x){
        //cout << "\tFindpath success!\n";
        x = graph->getPath(target.front().second, s);
        if(x){
          //cout << "\tGetpath success!\n";
          writeOutput(s, out);
        }
      }
      //else cout << "\tFindpath fail!\n";
    }
    prev = target.front().first;
    target.pop();
  }

  //cout << "\nFinished findPath!\n\n";
}

void writeOutput(stack<string>& s, ofstream& out){
  //cout << "\n\tStart output:\n";
  //cout << "\t\tsizeof stack: " << s.size() << "\n";
  //cout << "\tPath:\n";
  while(s.size()){
    //cout << "\t\t(" << s.top() << ")\n";
    out << "(" << s.top() << ")";
    s.pop();
    if(s.size()){
      out << "--[" << s.top() << "#@";
      s.pop();
    }
    if(s.size()){
      out << s.top() << "]-->";
      s.pop();
    }
  }
  out << "\n";
  //cout << "\tFinished output!\n\n";
}

