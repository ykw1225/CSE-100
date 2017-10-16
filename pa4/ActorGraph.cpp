#include "ActorGraph.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>


ActorGraph::ActorGraph(void){}

ActorGraph::~ActorGraph(){}

bool ActorGraph::loadFromFile(const char* in_filename, bool use_weighted_edges)
{
  // Initialize the file stream
  ifstream infile(in_filename);

  bool have_header = false;

  // keep reading lines until the end of file is reached
  while (infile){
    string s;

    // get the next line
    if (!getline( infile, s )) break;

    if (!have_header){
      // skip the header
      have_header = true;
      continue;
    }

    istringstream ss( s );
    vector <string> record;

    while (ss){
      string next;

      // get the next string before hitting a tab character and put it in 'next'
      if (!getline( ss, next, '\t' )) break;

      record.push_back( next );
    } // end of while(ss)

    if (record.size() != 3){
      // we should have exactly 3 columns
      continue;
    }

    string actor_name(record[0]);
    string movie_title(record[1]);
    int movie_year = stoi(record[2]);

  } // end of while(infile)

  if (!infile.eof()){
    cerr << "Failed to read " << in_filename << "!\n";
    return false;
  }
  infile.close();

  return true;

} // end of load
