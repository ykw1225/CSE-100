/*
 * Name: Chao Huang, Yeung-Kit Wong
 * Date: Aug 016, 2016
 * File: DictionaryTrie.hpp
 */

/**
 *  CSE 100 PA3 C++ Autocomplete
 *  Authors: Jor-el Briones, Christine Alvarado
 */

#ifndef DICTIONARY_TRIE_HPP
#define DICTIONARY_TRIE_HPP

#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

// struct that represents a node in our DictionaryTrie
struct Node{
  unsigned int freq;
  string word;
  Node* a;Node* b;Node* c;Node* d;Node* e;Node* f;Node* g;Node* h;Node* i;
  Node* j;Node* k;Node* l;Node* m;Node* n;Node* o;Node* p;Node* q;Node* r;
  Node* s;Node* t;Node* u;Node* v;Node* w;Node* x;Node* y;Node* z;Node* space;
  bool operator<(const Node& other){return freq < other.freq;}
};

// compare class for priority queue
class NodeComp{
  public:
  bool operator()(Node*& l, Node*& r)const{return *l < *r;}
};

// compare class for min priority queue
class MinComp {
  public:
  bool operator()(Node*& l, Node*& r)const{return *r < *l;}
};


/**
 *  The class for a dictionary ADT, implemented as a trie
 *  You may implement this class as either a mulit-way trie
 *  or a ternary search trie, but you must use one or the other.
 *
 */
class DictionaryTrie
{
public:

  /* Create a new Dictionary that uses a Trie back end */
  DictionaryTrie();

  /* Insert a word with its frequency into the dictionary.
   * Return true if the word was inserted, and false if it
   * was not (i.e. it was already in the dictionary or it was
   * invalid (empty string) */
  bool insert(std::string word, unsigned int freq);

  /* Return true if word is in the dictionary, and false otherwise */
  bool find(std::string word) const;

  /* Return up to num_completions of the most frequent completions
   * of the prefix, such that the completions are words in the dictionary.
   * These completions should be listed from most frequent to least.
   * If there are fewer than num_completions legal completions, this
   * function returns a vector with as many completions as possible.
   * If no completions exist, then the function returns a vector of size 0.
   * The prefix itself might be included in the returned words if the prefix
   * is a word (and is among the num_completions most frequent completions
   * of the prefix)
   */
  std::vector<std::string>
  predictCompletions(std::string prefix, unsigned int num_completions)const;

  /* Destructor */
  ~DictionaryTrie();

  // print all words
  void printAll()const;

private:
  // Add your own data members and methods here

  // create a new node
  Node* addNode(string word = "", unsigned int freq = 0)const;

  // root node
  Node* root;

  // find the node that represent the word
  Node* findNode(string word)const;


  // find all words and push into the queue
  void findWords(Node* n, priority_queue<Node*, vector<Node*>, MinComp> &mq,
               unsigned int num_completion )const;

  void findWords(Node* n, vector<string>* v)const;

  // recursive function for delete all nodes in tree
  void deleteAll(Node* n);

};

#endif // DICTIONARY_TRIE_HPP
