/*
 * Name: Chao Huang, Yeung-Kit Wong
 * Date: Aug 13, 2016
 * File: compress.cpp
 */

#include <iostream>
#include <fstream>
#include <cstring>
#include "HCTree.hpp"

using namespace std;

const int ARG_NUM = 3;
const int OUT_FILE_INDEX = 2;
const int TOTAL_CHAR = 256;

int main(int argc, char* argv[]){

  // check if command line argument numbers
  if( argc != ARG_NUM ){
    cout << "Invalid number of argument!" << endl;
    return EXIT_FAILURE;
  }

  // check if input file and output file have the same name
  if(!strcmp(argv[1], argv[OUT_FILE_INDEX])){
    cout << "In and out filename are the same!" << endl;
    return EXIT_FAILURE;
  }

  // setup all local variables
  ifstream iFile;
  ofstream oFile;
  int count = 0;
  int uniqueSymbol = 0;
  byte symbol;

  //vector to store characters frequencies
  vector<int> freqs( TOTAL_CHAR,0 );

  iFile.open(argv[1], ios::binary);


  // check for empty file
  if( iFile.peek() != std::ifstream::traits_type::eof() ) {

    iFile.close();

    // re-open the original file
    iFile.open(argv[1], ios::binary);

    // read in bytes from origin file
    while(1) {

      // read the single symbol from file
      symbol = iFile.get();
 
      // if reach the end of file
      if(iFile.eof()) break;

      // increment of total number of all symbol in file
      count++;

      // increment of total number of this symbol in file
      freqs[symbol]++;

    }

    // finished 1st time reading file
    iFile.close();

    //build the HCTree
    HCTree t;
    t.build(freqs);

    // count number of unique symbol in input file
    for( int x = 0; x < freqs.size(); x++ ){
      if( freqs[x] > 0 ) 
        uniqueSymbol++;
    }

    //write to compress file
    oFile.open(argv[OUT_FILE_INDEX], ios::binary);
    BitOutputStream os(oFile);

    //write header info first
    for( int i = 0; i < freqs.size(); i++ ){
      os.writeInt(freqs[i]);
    }

    os.writeByte();

    // no need to encode if input only has one unique symbol
    if ( uniqueSymbol == 1 ) {
      iFile.close();
      oFile.close();
    }

    // only encode Huffman code if input contains more than one unique symbol
    else {
      //encode origin file thru HCTree
      iFile.open(argv[1], ios::binary);
    
      for( int j = 0; j < count; j++ ) {
        symbol = iFile.get();
        t.encode(symbol, os);
      }

      os.writeByte();
      iFile.close();
      oFile.close();
    }
  }

  // only create empty file if original file is empty
  else {
    oFile.open(argv[OUT_FILE_INDEX], ios::out);
    iFile.close();
    oFile.close();
  }

  return 0;
}


