/*
 * Filename: pathfinder.cpp
 * Author: Chao Huang, Yeung-Kit Wong
 * Date: Aug 24 2016
 * Description: TODO
 */

#include <iostream>
#include <fstream>
#include <cstdio>
#include "ActorGraph.hpp"

using namespace std;

// number of command line arguments
const int NUM_ARGC = 5;
// index of movie cast file
const int DATA = 1;
// index of test pairs actor file
const int TARGET = 3;
// index of flag set
const int FLAG = 2;
// index of output file
const int OUTFILE = 4;
// program usage
const string USAGE = "\nUsage: myprog arg1 arg2 arg3 arg4\n"
                     "\targ1: file1 same format as movie_casts.tsv\n"
                     "\targ2: character 'w' or 'u'\n"
                     "\t\tu: build the graph with unweighted edges\n"
                     "\t\tw: build the graph with weighted edges\n"
                     "\targ3: file2 pairs of actors for find paths\n"
                     "\targ4: file3 the output file\n";

/*
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
  cout << buf << endl;

  ActorGraph* graph = new ActorGraph(weighted);

  graph->buildGraph(inData);

  //graph->printAll();

  delete graph;


  return 1;

}
