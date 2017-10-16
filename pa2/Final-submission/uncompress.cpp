/*
 * Name: Chao Huang, Yeung-Kit Wong
 * Date: Aug 09, 2016
 * File: uncompress.cpp
 */

#include <iostream>
#include <fstream>
#include <cstring>
#include "HCTree.hpp"

using namespace std;

const int ARG_NUM = 3;
const int TOTAL_CHARS = 256;
const int OFILE_INDEX = 2;

int main(int argc, char* argv[]){

  // check if command line argument numbers
  if( argc != ARG_NUM ){
    cout << "Invalid number of argument!" << endl;
    return EXIT_FAILURE;
  }

  // check if input file and output file have the same name
  if( !strcmp(argv[1], argv[OFILE_INDEX]) ){
    cout << "In and out filename are the same!" << endl;
    return EXIT_FAILURE;
  }

  // setup all local variables
  ifstream iFile;
  ofstream oFile;
  int count = 0;
  int uniqueSymbol = 0;
  int charInt;

  //vector to store characters frequencies
  vector<int> freqs(TOTAL_CHARS,0);

  iFile.open(argv[1], ios::binary);

  //check if compressed file is empty
  if(iFile.peek() != std::ifstream::traits_type::eof() ) {

    iFile.close();

    // re-open the compressed file
    iFile.open(argv[1], ios::binary);

    BitInputStream is(iFile);

    //get frequencies from header info
    for( int i = 0; i < freqs.size(); i++ ) {
      freqs[i] = is.readInt();
      count += freqs[i];
    }

    //rebuild HCTree
    HCTree t;
    t.build(freqs);

    // count number of unique symbol in input file
    for( int x = 0; x < freqs.size(); x++ ){
      if( freqs[x] > 0 ) 
        uniqueSymbol++;
    }

    // open output file
    oFile.open(argv[OFILE_INDEX], ios::binary);

    // directly print symbol if only one unique in input file
    if( uniqueSymbol == 1) {
      // find the only unique symbol in input file
      for( int i = 0; i < freqs.size(); i++ ){
        if( freqs[i] > 0 ) 
          charInt = i;
      }

      //print that symbol according to frequency
      for( int j = 0; j < freqs[charInt]; j++) {
        oFile.write((char*)&charInt, sizeof(char));
      }

      iFile.close();
      oFile.close();
    }

    // only decode if input file contains more than one unique symbol 
    else{

      //decode compressed file thru HSTree
      for( int j = 0; j < count; j++ ) {
        charInt = t.decode(is);

        // if the code is not correct
        if(charInt < 0)
          break;
        else if(charInt >= 0)
          oFile.write((char*)&charInt, sizeof(char));
      }
      iFile.close();
      oFile.close();
    }
  }

  //only create empty file if compressed file is empty
  else {
    oFile.open(argv[OFILE_INDEX], ios::out);
    iFile.close();
    oFile.close();
  }

  return 0;
}
