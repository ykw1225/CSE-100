/*
 * Name: Chao Huang, Yeung-Kit Wong
 * Date: Aug 016, 2016
 * File: DictionaryTrie.cpp
 */

#include <stack>
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
  auto curr = findNode(word);

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

  // temporary vector to save the word
  auto v = predictCompletions(word,1);

  // if the word is not exist
  if(!v.size()) return false;

  // the word is exist
  return true;
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
  auto curr = findNode(prefix);

  // min priority_queue to store all words have prefix
  priority_queue<Node*, vector<Node*>, MinComp> mq;

  // priority_queue to store all words have prefix
  // priority_queue<Node*, vector<Node*>, NodeComp> pq;

  // use stack instead pq
  stack<string> s;

  // find all words have prefix and store into queue
  findWords(curr, mq, num_completions);

  // iterator thru the Min priority queue, store in to priority queue
  // from highest count to lowest
  for( unsigned int i = 0; i < num_completions; i++) {
    if( mq.size() ) {
      s.push( mq.top()->word );
      mq.pop();
    }
  }

  // store num_completions number of words into vector
  for(unsigned int i = 0; i < num_completions; i++){
    if(s.size()){
      word.push_back(s.top());
      s.pop();
    }
  }

  return word;
}


Node* DictionaryTrie::addNode(string word, unsigned int freq)const{
  Node* x = new Node;
  x->word = word;
  x->freq = freq;
  x->a = x->b = x->c = x->d = x->e = x->f = x->g = x->h = x->i = x->j = x->k = x->l = x->m =
  x->n = x->o = x->p = x->q = x->r = x->s = x->t = x->u = x->v = x->w = x->x = x->y = x->z =
  x->space = 0;
  return x;
}

Node* DictionaryTrie::findNode(string word)const{
  // check empty string
  if( word.empty() ) return 0;
  // temporary pointer to track current node
  auto curr = root;
  // start finding the location for new node
  for(unsigned int i=0; i < word.length(); i++){
    char c = word[i];
    switch(c){
      case 'a': if(!curr->a) curr->a = addNode();
                curr = curr->a;
                break;
      case 'b': if(!curr->b) curr->b = addNode();
                curr = curr->b;
                break;
      case 'c': if(!curr->c) curr->c = addNode();
                curr = curr->c;
                break;
      case 'd': if(!curr->d) curr->d = addNode();
                curr = curr->d;
                break;
      case 'e': if(!curr->e) curr->e = addNode();
                curr = curr->e;
                break;
      case 'f': if(!curr->f) curr->f = addNode();
                curr = curr->f;
                break;
      case 'g': if(!curr->g) curr->g = addNode();
                curr = curr->g;
                break;
      case 'h': if(!curr->h) curr->h = addNode();
                curr = curr->h;
                break;
      case 'i': if(!curr->i) curr->i = addNode();
                curr = curr->i;
                break;
      case 'j': if(!curr->j) curr->j = addNode();
                curr = curr->j;
                break;
      case 'k': if(!curr->k) curr->k = addNode();
                curr = curr->k;
                break;
      case 'l': if(!curr->l) curr->l = addNode();
                curr = curr->l;
                break;
      case 'm': if(!curr->m) curr->m = addNode();
                curr = curr->m;
                break;
      case 'n': if(!curr->n) curr->n = addNode();
                curr = curr->n;
                break;
      case 'o': if(!curr->o) curr->o = addNode();
                curr = curr->o;
                break;
      case 'p': if(!curr->p) curr->p = addNode();
                curr = curr->p;
                break;
      case 'q': if(!curr->q) curr->q = addNode();
                curr = curr->q;
                break;
      case 'r': if(!curr->r) curr->r = addNode();
                curr = curr->r;
                break;
      case 's': if(!curr->s) curr->s = addNode();
                curr = curr->s;
                break;
      case 't': if(!curr->t) curr->t = addNode();
                curr = curr->t;
                break;
      case 'u': if(!curr->u) curr->u = addNode();
                curr = curr->u;
                break;
      case 'v': if(!curr->v) curr->v = addNode();
                curr = curr->v;
                break;
      case 'w': if(!curr->w) curr->w = addNode();
                curr = curr->w;
                break;
      case 'x': if(!curr->x) curr->x = addNode();
                curr = curr->x;
                break;
      case 'y': if(!curr->y) curr->y = addNode();
                curr = curr->y;
                break;
      case 'z': if(!curr->z) curr->z = addNode();
                curr = curr->z;
                break;
      case ' ': if(!curr->space) curr->space = addNode();
                curr = curr->space;
                break;
      default:  cout << "Invalid character found: " << c << endl;
                break;
    } // end of switch
  } // end of for loop
  return curr;
} // end of findNode

void DictionaryTrie::findWords(Node* n,
   priority_queue <Node*, vector<Node*>, MinComp> &mq, unsigned int num_completion )const{

  if(!n) return;

  // if the min priority queue has less than required completion stored
  // directly store the matching node
  if( n->word.length() && mq.size() < num_completion )
    mq.push(n);

  else if( n->word.length() && mq.size() >= num_completion ){
    // replace the lowest count element if new word has higher count
    if( mq.top()->freq < n->freq) {
      mq.pop();
      mq.push(n);
    }
  }

  if((n->a)) findWords(n->a, mq, num_completion);
  if((n->b)) findWords(n->b, mq, num_completion);
  if((n->c)) findWords(n->c, mq, num_completion);
  if((n->d)) findWords(n->d, mq, num_completion);
  if((n->e)) findWords(n->e, mq, num_completion);
  if((n->f)) findWords(n->f, mq, num_completion);
  if((n->g)) findWords(n->g, mq, num_completion);
  if((n->h)) findWords(n->h, mq, num_completion);
  if((n->i)) findWords(n->i, mq, num_completion);
  if((n->j)) findWords(n->j, mq, num_completion);
  if((n->k)) findWords(n->k, mq, num_completion);
  if((n->l)) findWords(n->l, mq, num_completion);
  if((n->m)) findWords(n->m, mq, num_completion);
  if((n->n)) findWords(n->n, mq, num_completion);
  if((n->o)) findWords(n->o, mq, num_completion);
  if((n->p)) findWords(n->p, mq, num_completion);
  if((n->q)) findWords(n->q, mq, num_completion);
  if((n->r)) findWords(n->r, mq, num_completion);
  if((n->s)) findWords(n->s, mq, num_completion);
  if((n->t)) findWords(n->t, mq, num_completion);
  if((n->u)) findWords(n->u, mq, num_completion);
  if((n->v)) findWords(n->v, mq, num_completion);
  if((n->w)) findWords(n->w, mq, num_completion);
  if((n->x)) findWords(n->x, mq, num_completion);
  if((n->y)) findWords(n->y, mq, num_completion);
  if((n->z)) findWords(n->z, mq, num_completion);
  if((n->space)) findWords(n->space, mq, num_completion);
} // end of findWords

void DictionaryTrie::findWords(Node* n, vector<string>* v)const{
  if(!n || !v) return;
  if(n->word.length())v->push_back(n->word);
  if((n->a)) findWords(n->a, v);
  if((n->b)) findWords(n->b, v);
  if((n->c)) findWords(n->c, v);
  if((n->d)) findWords(n->d, v);
  if((n->e)) findWords(n->e, v);
  if((n->f)) findWords(n->f, v);
  if((n->g)) findWords(n->g, v);
  if((n->h)) findWords(n->h, v);
  if((n->i)) findWords(n->i, v);
  if((n->j)) findWords(n->j, v);
  if((n->k)) findWords(n->k, v);
  if((n->l)) findWords(n->l, v);
  if((n->m)) findWords(n->m, v);
  if((n->n)) findWords(n->n, v);
  if((n->o)) findWords(n->o, v);
  if((n->p)) findWords(n->p, v);
  if((n->q)) findWords(n->q, v);
  if((n->r)) findWords(n->r, v);
  if((n->s)) findWords(n->s, v);
  if((n->t)) findWords(n->t, v);
  if((n->u)) findWords(n->u, v);
  if((n->v)) findWords(n->v, v);
  if((n->w)) findWords(n->w, v);
  if((n->x)) findWords(n->x, v);
  if((n->y)) findWords(n->y, v);
  if((n->z)) findWords(n->z, v);
  if((n->space)) findWords(n->space, v);
} // end of findWords

void DictionaryTrie::deleteAll(Node* n){
  if(!n) return;
  if((n->a)) deleteAll(n->a);
  if((n->b)) deleteAll(n->b);
  if((n->c)) deleteAll(n->c);
  if((n->d)) deleteAll(n->d);
  if((n->e)) deleteAll(n->e);
  if((n->f)) deleteAll(n->f);
  if((n->g)) deleteAll(n->g);
  if((n->h)) deleteAll(n->h);
  if((n->i)) deleteAll(n->i);
  if((n->j)) deleteAll(n->j);
  if((n->k)) deleteAll(n->k);
  if((n->l)) deleteAll(n->l);
  if((n->m)) deleteAll(n->m);
  if((n->n)) deleteAll(n->n);
  if((n->o)) deleteAll(n->o);
  if((n->p)) deleteAll(n->p);
  if((n->q)) deleteAll(n->q);
  if((n->r)) deleteAll(n->r);
  if((n->s)) deleteAll(n->s);
  if((n->t)) deleteAll(n->t);
  if((n->u)) deleteAll(n->u);
  if((n->v)) deleteAll(n->v);
  if((n->w)) deleteAll(n->w);
  if((n->x)) deleteAll(n->x);
  if((n->y)) deleteAll(n->y);
  if((n->z)) deleteAll(n->z);
  if((n->space)) deleteAll(n->space);
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