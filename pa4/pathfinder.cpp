/*
 * Filename: pathfinder.cpp
 * Author: Chao Huang, Yeung-Kit Wong
 * Date: Aug 23 2016
 * Description: TODO
 */

#include <iostream>
#include <fstream>
#include "ActorGraph.hpp"

using namespace std;

void buildUnweighted(ifstream, ifstream, ofstream);
void buildWeighted(ifstream, ifstream, ofstream);

// number of command line arguments
const int NUM_ARGC = 5;
// index of movies file
const int MOVIES = 1;
// index of actors file
const int ACTORS = 3;
// index of flag set
const int FLAG = 2;
// index of output file
const int OUTFILE = 4;
// program usage
const string USAGE = "\nUsage: myprog arg1 arg2 arg3 arg4\n"
                     "\targ1: file1 same format as movie_casts.tsv\n"
                     "\targ2: character 'w' or 'u'\n"
                     "\t\tw: build the graph with unweighted edges\n"
                     "\t\tu: build the graph with weighted edges\n"
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

  // declare variables for command line arguments
  string moviesFile, actorsFile, outFile;
  char flag;

  // declare local variables
  ifstream inMovies;
  ifstream inActors;
  ofstream out;

  // initialize variables
  moviesFile = argv[MOVIES];
  flag = argv[FLAG][0];
  actorsFile = argv[ACTORS];
  outFile = argv[OUTFILE];

  // check validity of command line arguments
  inMovies.open(moviesFile, ios::binary);
  if(!inMovies.is_open()){
    cout << "\nInvalid arg1! Cannot open " << moviesFile << "\n" << USAGE;
    return 0;
  }
  if(flag != 'w' && flag != 'u'){
    cout << "\nInvalid arg2!\n" << USAGE;
    return 0;
  }
  inActors.open(actorsFile, ios::binary);
  if(!inActors.is_open()){
    cout << "\nInvalid arg3! Cannot open " << actorsFile << "\n" << USAGE;
    return 0;
  }
  out.open(outFile, ios::binary);
  if(!outFile.is_open()){
    cout << "\nInvalid arg4! Cannot open " << outFile << "\n" << USAGE;
    return 0;
  }

  // start to build the graph
  if(flag == 'u')buildUnweighted();
  else buildWeighted();

  return 1;

}

/*
 * Function name: TODO
 * Description: TODO
 */
void buildUnweighted(ifstream inMovies, ifstream inActors, ofstream out){
}

/*
 * Function name: TODO
 * Description: TODO
 */
void buildWeighted(ifstream inMovies, ifstream inActors, ofstream out){
}
