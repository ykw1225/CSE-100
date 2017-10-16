
/*
 * Filename: benchdict.cpp
 * Name    : Chao Huang, Yeung-Kit Wong
 * Date    : Aug 21 2016
 * Descritpion: This file is for benchmarking the running time of
 *              the find() method of DictionaryBST, DictionaryHashtable
 *              and Dictionary Trie. It prints out the running time
 *              for each clas to find ten words not in the dictionary.
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include "DictionaryBST.hpp"
#include "DictionaryHashtable.hpp"
#include "DictionaryTrie.hpp"
#include "util.hpp"

using namespace std;

const int ARG_NUM = 5;
const unsigned int STEP_INDEX = 2;
const unsigned int ITR_INDEX = 3;
const unsigned int FILE_INDEX = 4;
const unsigned int LOOP_NUM = 1000;
const int NUM_WORDS = 10;
const string strsNotInDict[] = {
  "      aaaaaaaaaa",
  "      bbbbbbbbbb",
  "      cccccccccc",
  "      dddddddddd",
  "      eeeeeeeeee",
  "      ffffffffff",
  "      gggggggggg",
  "      hhhhhhhhhh",
  "      iiiiiiiiii",
  "      jjjjjjjjjj"};

/** count function for counting total words in
 *  the input file and returns the total number of words
 */
unsigned int countWords(istream& in){

  // buffer for store a line
  string buf;

  // counter for counting the number of lines in file
  unsigned int count;

  // start counting
  while(1){

    getline(in, buf);

    if(in.eof()) break;

    count++;

  }

  return count;

}


/** Main method to open and read the input file, create
 *  dictionary objects, call find method, calculate
 *  running time and prints out the running time.
 */
int main( int argc, char* argv[] ) {

  // 1st command argument
  unsigned int min_size;

  // 2nd command argument
  unsigned int step_size;

  // 3rd command argument
  unsigned int num_itrs;

  // min_size + i*step_size
  unsigned int num_toLoad = 0;

  // total time for find 10 words for LOOP_NUM number times
  long long totalTime = 0;

  // total time / LOOP_NUM
  long long avgTime;

  // file name
  string dictfile;

  // in file stream
  ifstream inFile;

  // timer object
  Timer t;

  // total number of word in the file
  unsigned int totalWords;

  //check number of argument
  if( argc != ARG_NUM ) {

    cout << "Invalid number of argument!" << endl;

    cout << "Expect: min_size, step_size, num_iterations, dictfile\n\n";

    return EXIT_FAILURE;

  }

  // save arguments to local variables
  min_size = atoi(argv[1]);
  step_size = atoi(argv[STEP_INDEX]);
  num_itrs = atoi(argv[ITR_INDEX]);

  dictfile = argv[FILE_INDEX];

  inFile.open( dictfile, std::ifstream::in);

  // check if file open success
  if( !inFile.is_open() ) {

    cout << "Invalid dictionary filename!" << endl;

    return EXIT_FAILURE;

  }

  // counting total words in the file
  totalWords = countWords(inFile);

  inFile.close();
  inFile.open( dictfile, std::ifstream::in);


  // Test on DictionaryBST class

  // create dict obj, load (min + step) words
  DictionaryBST* bstDictPtr = new DictionaryBST() ;
  DictionaryBST& bstDict = *bstDictPtr;

  cout << "DictionaryBST\n";

  for( unsigned int i = 0; i < num_itrs; i++ ) {

    num_toLoad = min_size + i*step_size;

    Utils::load_dict( bstDict, inFile, num_toLoad );

    if(totalWords < num_toLoad)

      cout << "Warning! There are fewer than " << num_toLoad << " words in the file!\n";

    // loop to calculate average run time
    for( unsigned int j = 0; j < LOOP_NUM; j++ ) {

      t.begin_timer();

      // find ten words not present in dictionary
      for( int x = 0; x < NUM_WORDS; x++ )

        bstDict.find(strsNotInDict[x]);

      totalTime = totalTime + t.end_timer();

    }

    avgTime = totalTime / LOOP_NUM;

    cout << num_toLoad << "\t" << avgTime << endl;

  }

  // reset time and count
  totalTime = 0;
  cout << "\n";
  inFile.close();
  delete bstDictPtr;



  // Test on DictionaryHashtable class
  inFile.open( dictfile, std::ifstream::in);

  // create dict obj, load (min + step) words
  DictionaryHashtable* hashDictPtr = new DictionaryHashtable();
  DictionaryHashtable& hashDict = *hashDictPtr;

  cout << "DictionaryHashtable\n";

  for( unsigned int i = 0; i < num_itrs; i++ ) {

    num_toLoad = min_size + i*step_size;

    Utils::load_dict( hashDict, inFile, num_toLoad );

    if(totalWords < num_toLoad)

      cout << "Warning! There are fewer than " << num_toLoad << " words in the file!\n";

    // loop to calculate average run time
    for( unsigned int j = 0; j < LOOP_NUM; j++ ){

      t.begin_timer();

      // find ten words not present in dictionary
      for( int x = 0; x < NUM_WORDS; x++ )

        hashDict.find(strsNotInDict[x]);

      totalTime = totalTime + t.end_timer();

    }

    avgTime = totalTime / LOOP_NUM;

    cout << num_toLoad << "\t" << avgTime << endl;

  }

  // reset time and count
  totalTime = 0;
  cout << "\n";
  inFile.close();
  delete hashDictPtr;



  // Test on DictionaryTrie class
  inFile.open( dictfile, std::ifstream::in);

  // create dict obj, load (min + step) words
  DictionaryTrie* trieDictptr = new DictionaryTrie();
  DictionaryTrie& trieDict = *trieDictptr;

  cout << "DictionaryTrie\n";

  for( unsigned int i = 0; i < num_itrs; i++ ) {

    num_toLoad = min_size + i*step_size;

    Utils::load_dict( trieDict, inFile, num_toLoad );

    if(totalWords < num_toLoad)
      cout << "Warning! There are fewer than " << num_toLoad << " words in the file!\n";

    // loop to calculate average run time
    for( unsigned int j = 0; j < LOOP_NUM; j++ ) {

      t.begin_timer();

      // find ten words not present in dictionary
      for( int x = 0; x < NUM_WORDS; x++ )

        trieDict.find(strsNotInDict[x]);

      totalTime = totalTime + t.end_timer();

    }

    avgTime = totalTime / LOOP_NUM;

    cout << num_toLoad << "\t" << avgTime << endl;

  }

  // reset time and count
  totalTime = 0;
  cout << "\n";
  inFile.close();
  delete trieDictptr;


  cout << "\n";
  return 0;

}


