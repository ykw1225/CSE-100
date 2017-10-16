/*
 * Name: Chao Huang, Yeung-Kit Wong
 * Date: Aug 21, 2016
 * File: DictionaryTrie.hpp
 * Description: This is the header file for DictionaryTrie,
 *              declares DictionaryTrie class members and
 *              function prototypes.
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
#include <set>
#include <cctype>
#include <iomanip>

using namespace std;

/** struct that represents a node in our DictionaryTrie
 *  stores the freq, word, and child nodes
 */
struct Node{
  unsigned int freq; // frequency of the word appears in dicionary
  string word; // only set if a node reprensent a word in dictionary
  // pointer to child nodes
  Node* a;Node* b;Node* c;Node* d;Node* e;Node* f;Node* g;Node* h;Node* i;
  Node* j;Node* k;Node* l;Node* m;Node* n;Node* o;Node* p;Node* q;Node* r;
  Node* s;Node* t;Node* u;Node* v;Node* w;Node* x;Node* y;Node* z;Node* space;
  
  /* less than comparison for nodes, higher freq is considered larger */
  bool operator<(Node const& other)const{return freq < other.freq;}

  unsigned int max;
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

  /* print all words in the trie */
  void printAll()const;

  /* find the frequency of word */
  unsigned int findFreq(string word)const;

private:
  // Add your own data members and methods here

  // root node
  Node* root;

  /* create a new node and add to trie */
  Node* addNode(string word = "", unsigned int freq = 0);
  Node* addNode(unsigned int freq){return addNode("", freq);}

  /** create the path when insert a new node
   *  Also return a pointer to the new node
   */
  Node* createPath(string word, unsigned int freq);

  /** find the node represents the string word
   *  return pointer to that node, return nullptr if not found
   */
  Node* findPath(string word)const;

  /* find all words rooted by n and push into the given collection structure*/
  void findWords(Node* n, set<Node> &s, unsigned int num_completion )const;
  void findWords(Node* n, vector<Node*>* v)const;

  /* recursive function to delete all the nodes in trie */
  void deleteAll(Node* n);

};

#endif // DICTIONARY_TRIE_HPP
