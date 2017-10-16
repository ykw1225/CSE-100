/*
 * Name: Chao Huang, Yeung-Kit Wong
 * Date: Aug 016, 2016
 * File: DictionaryTrie.cpp
 */

#include "util.hpp"
#include "DictionaryTrie.hpp"

using namespace std;

/* Create a new Dictionary that uses a Trie back end */
DictionaryTrie::DictionaryTrie(){root = addNode();}

/* Insert a word with its frequency into the dictionary.
 * Return true if the word was inserted, and false if it
 * was not (i.e. it was already in the dictionary or it was
 * invalid (empty string) */
bool DictionaryTrie::insert(std::string word, unsigned int freq)
{

  // check empty string
  if(!word.length()){
    cout << "Invalid word!\n";
    return false;
  }

  // check if freq is valid
  if(freq < 1){
    cout << "Invalid freq!\n";
    return false;
  }

  // temporary pointer to track current node
  auto curr = createPath(word);

  if(!curr) return false;

  // if the word is not exist
  if(!(curr->word.length())){
    curr->word = word;
    curr->freq = freq;
    return true;
  }

  // the word is exist
  return false;
}

/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryTrie::find(std::string word) const{

  // check empty string
  if(!word.length()){
    cout << "Invalid word!\n";
    return false;
  }

  // temporary vector to save the node
  auto v = findPath(word);

  // if the node is not exist
  if(!v) return false;

  // the word is exist
  else if(v->word.length()) return true;

  // the word is not exist
  return false;
}

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
std::vector<std::string> DictionaryTrie::predictCompletions(std::string prefix, unsigned int num_completions)const{

  // return value
  vector<string> word;

  // check zero num_completions and empty string
  if(num_completions < 1 || prefix.empty()) return word;

  // temporary pointer to track current node
  auto curr = findPath(prefix);

  // if the dictionary does not have this prefix
  if(!curr) return word;

  set<Node*, lessThan> s;

  // find all words have prefix and store into set
  findWords(curr, s, num_completions);

  // store num_completions number of words into vector
  for(unsigned int i = 0; i < num_completions; i++){
    if(s.size()){
      set<Node*, lessThan>::iterator itr = s.end();
      itr--;
      word.push_back((*itr)->word);
      s.erase(itr);
    }
  }

  return word;
}


Node* DictionaryTrie::addNode(string word, unsigned int freq)const{
  Node* x = new Node;
  x->word = word;
  x->freq = freq;
  /*for(char c='a'; c<='z'; c++)
    x->children.insert(x->children.begin(), pair<char, Node*>(c,nullptr));
  x->children.insert(x->children.begin(), pair<char, Node*>(' ',nullptr));*/
  return x;
}

Node* DictionaryTrie::createPath(string word)const{
  // check empty string
  if( word.empty() ) return 0;
  // temporary pointer to track current node
  auto curr = root;
  // start finding the location for new node
  for(unsigned int i=0; i < word.length(); i++){
    char c = word[i];
    if(curr->children.find(c) == curr->children.end())
      curr->children.insert(pair<char, Node*>(c,nullptr));
    if(!curr->children[c]) curr->children[c] = addNode();
    curr = curr->children[c];
  }
  return curr;
} // end of createPath

Node* DictionaryTrie::findPath(string word)const{
  // check empty string
  if( word.empty() ) return 0;
  // temporary pointer to track current node
  auto curr = root;
  // start finding the location for new node
  for(unsigned int i=0; i < word.length(); i++){
    char c = word[i];
    if(curr->children.find(c) == curr->children.end()) return nullptr;
    if(!curr->children[c]) return nullptr;
    curr = curr->children[c];
  }
  return curr;
} // end of createPath

void DictionaryTrie::findWords(Node* n, vector<string>* v)const{
  if(!n || !v) return;
  if(n->word.length())v->push_back(n->word);
  map<char, Node*>::iterator itr = n->children.begin();
  for(;itr!=n->children.end();itr++)
    findWords(itr->second, v);
} // end of findWords

void DictionaryTrie::findWords(Node* n, set<Node*, lessThan> &s, unsigned int num_completion )const{
  if(!n) return;
  // if the set has less than required completion stored
  // directly store the matching node
  if( n->word.length() && s.size() < num_completion )
    s.insert(n);
  else if( n->word.length() && s.size() >= num_completion ){
    // replace the lowest count element if new word has higher count
    if( (*s.begin())->freq < n->freq) {
      s.erase(s.begin());
      s.insert(n);
    }
  }
  map<char, Node*>::iterator itr = n->children.begin();
  for(;itr!=n->children.end();itr++)
    findWords(itr->second, s, num_completion);
} // end of findWords

void DictionaryTrie::deleteAll(Node* n){
  if(!n) return;
  map<char, Node*>::iterator itr = n->children.begin();
  for(;itr!=n->children.end();itr++)
    deleteAll(itr->second);
  delete n;
} // end of deleteAll;

/* Destructor */
DictionaryTrie::~DictionaryTrie(){deleteAll(root);}


void DictionaryTrie::printAll()const{
  if(!root)
    cout << "\nEmpty trie!!!" << endl;
  else{
    vector<string> v;
    findWords(root, &v);
    if(v.empty()){
      cout << "\nEmpty vector!!!" << endl;
      return;
    }
    cout << "\nStart printing all node:\n";
    vector<string>::iterator itr = v.begin();
    for(; itr != v.end(); itr++)
      cout << "\t" << *itr << endl;
    cout << "Finished printing all node!!!\n";
  }
}