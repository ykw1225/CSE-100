/*
 * Filename: test.cpp
 * Name: Chao Huang, Yeung-Kit Wong
 * Date: Aug 18 2016
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include "DictionaryBST.hpp"
#include "DictionaryHashtable.hpp"
#include "util.hpp"

using namespace std;

int main(){

  Timer t;
  long long time;
  DictionaryBST bst;
  DictionaryHashtable ht;
  DictionaryTrie dt;
  ifstream in;
  string file;
  bool isInvalid;
  string word;
  int count = 0;
  int freq = 0;
  vector<string> v;
  vector<string> v2;

  cout << "\nEnter a dictionary name: ";
  do{
    cin >> file;
    in.open(file, ios::binary);
    isInvalid = false;
    if(!in.is_open()){
      cout << "Invalid dictionary name, enter again: ";
      isInvalid = true;
    }
    else{
      in.seekg(0, ios_base::end);
      unsigned int l = in.tellg();
      if(!l){
        cout << "Empty file, try another file: ";
        isInvalid = true;
      }
    }
  }while(isInvalid);

  in.close(); in.open(file, ios::binary);

  cout << "\nTesting BST:" << endl;
  cout << "\n\tStart loading the dictionary!\n";
  t.begin_timer();
  Utils::load_dict(bst, in);
  time = t.end_timer();
  cout << "\tFinished loading, spend " << time << " nanosecond!\n\n";

  //bst.printAll();

  //return 1;

  in.close();
  in.open(file, ios::binary);

  cout << "\tStart finding each word!\n";
  t.begin_timer();
  while(1){
    in >> freq;
    in.get();
    getline(in, word);
    //cout << "\t\tLooking for word: " << word << "\n";
    if(in.eof()) break;
    if(bst.find(word)){
      count++;
      cout << "\t\tFound word: " << left << setw(10) << word << "(" << freq << ")\n";
    }
    else break;
  }
  cout << "\t\tTest for invalid string: 'asdf'\n";
  if(bst.find("asdf")) cout << "\t\t\tFounded\n";
  else cout << "\t\t\tNot found\n";
  time = t.end_timer();
  cout << "\tFinished finding, spend " << time << " nanosecond!\n\t\t\t\t"
       << count << " words is found!\n\n";
  cout << "Finished testing BST!\n";

  in.close();

  in.open(file, ios::binary);


  count = 0;
  cout << "\nTesting HashTable:" << endl;
  cout << "\n\tStart loading the dictionary!\n";
  t.begin_timer();
  Utils::load_dict(ht, in);
  time = t.end_timer();
  cout << "\tFinished loading, spend " << time << " nanosecond!\n\n";

  in.close(); in.open(file, ios::binary);

  cout << "\tStart finding each word!\n";
  t.begin_timer();
  while(1){
    in >> freq;
    in.get();
    getline(in, word);
    if(in.eof()) break;
    if(ht.find(word)){
      count++;
      cout << "\t\tFound word: " << left << setw(10) << word << "(" << freq << ")\n";
    }
    else break;
  }
  cout << "\t\tTest for invalid string: 'asdf'\n";
  if(ht.find("asdf")) cout << "\t\t\tFounded\n";
  else cout << "\t\t\tNot found\n";
  time = t.end_timer();
  cout << "\tFinished finding, spend " << time << " nanosecond!\n\t\t\t\t"
       << count << " words is found!\n\n";
  cout << "Finished testing BST!\n";

  in.close();

  cout << endl;



  in.open(file, ios::binary);


  count = 0;
  cout << "\nTesting DictionaryTrie:" << endl;
  cout << "\n\tStart loading the dictionary!\n";
  t.begin_timer();
  Utils::load_dict(dt, in);
  time = t.end_timer();
  cout << "\tFinished loading, spend " << time << " nanosecond!\n\n";

  //dt.printAll();

  //return 1;

  in.close(); in.open(file, ios::binary);

  cout << "\tStart finding each word!\n";
  t.begin_timer();
  while(1){
    in >> freq;
    in.get();
    getline(in, word);
    if(in.eof()) break;
    if(dt.find(word)){
      count++;
      cout << "\t\tFound word: " << left << setw(10) << word << "(" << freq << ")\n";
    }
    else break;
  }
  cout << "\t\tTest for no string not in dictionary: 'asdf'\n";
  if(dt.find("asdf")) cout << "\t\t\tFounded\n";
  else cout << "\t\t\tNot found\n";
  time = t.end_timer();
  cout << "\tFinished finding, spend " << time << " nanosecond!\n\t\t\t\t"
       << count << " words is found!\n\n";
  cout << "Finished testing DictionaryTrie!\n";

  in.close();

  cout << "\nStart testing on predictCompletions function:\n";

  cout << "\t\tPrefix = \"a\", num_completions = 5:\n";

  v = dt.predictCompletions("a", 5);

  vector<string>::iterator itr = v.begin();

  for(;itr != v.end(); itr++)
    cout << "\t\t\t" << left << setw(10) << *itr << dt.findFreq(*itr) << endl;

  cout << "\t\tThere are " << v.size() << " words with the prefix!!!\n\n";

  cout << "-- testing invalid prefix = '9', mum_completions = 3:\n";

  v2 = dt.predictCompletions("9" , 3 );

  if ( v2.size() )
    cout << "---Fail invalid prefix test! Found matching word!" << endl;
  else
    cout << "---Pass invalid prefix test!\n\n";

  cout << "Finished testing on predictCompletions function!!!\n";

  dt.printAll();

  cout << endl;

  return 1;
}


