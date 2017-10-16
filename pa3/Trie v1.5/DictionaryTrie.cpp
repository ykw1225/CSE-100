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
  auto curr = createPath(word, freq);

  if(!curr) return false;

  // if the word is not exist
  if(!(curr->word.length())){
    curr->word = word;
    curr->freq = curr->max = freq;
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
  if(num_completions < 1 || !prefix.length()) return word;

  // temporary pointer to track current node
  auto curr = findPath(prefix);

  // if the dictionary does not have this prefix
  if(!curr) return word;

  set<Node> s;

  // find all words have prefix and store into set
  findWords(curr, s, num_completions);

  // store num_completions number of words into vector
  for(unsigned int i = 0; i < num_completions; i++){
    if(s.size()){
      set<Node>::iterator itr = s.end();
      itr--;
      word.push_back((*itr).word);
      s.erase(itr);
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

Node* DictionaryTrie::createPath(string word, unsigned int freq)const{
  // check empty string
  if(!word.length()) return nullptr;
  // temporary pointer to track current node
  auto curr = root;
  // start finding the location for new node
  for(unsigned int i=0; i < word.length(); i++){
    char c = word[i];
    switch(c){
      case 'a': if(!curr->a) curr->a = addNode(freq);
                else if(curr->a->max < freq) curr->a->max = freq;
                curr = curr->a;
                break;
      case 'b': if(!curr->b) curr->b = addNode(freq);
                else if(curr->b->max < freq) curr->b->max = freq;
                curr = curr->b;
                break;
      case 'c': if(!curr->c) curr->c = addNode(freq);
                else if(curr->c->max < freq) curr->c->max = freq;
                curr = curr->c;
                break;
      case 'd': if(!curr->d) curr->d = addNode(freq);
                else if(curr->d->max < freq) curr->d->max = freq;
                curr = curr->d;
                break;
      case 'e': if(!curr->e) curr->e = addNode(freq);
                else if(curr->e->max < freq) curr->e->max = freq;
                curr = curr->e;
                break;
      case 'f': if(!curr->f) curr->f = addNode(freq);
                else if(curr->f->max < freq) curr->f->max = freq;
                curr = curr->f;
                break;
      case 'g': if(!curr->g) curr->g = addNode(freq);
                else if(curr->g->max < freq) curr->g->max = freq;
                curr = curr->g;
                break;
      case 'h': if(!curr->h) curr->h = addNode(freq);
                else if(curr->h->max < freq) curr->h->max = freq;
                curr = curr->h;
                break;
      case 'i': if(!curr->i) curr->i = addNode(freq);
                else if(curr->i->max < freq) curr->i->max = freq;
                curr = curr->i;
                break;
      case 'j': if(!curr->j) curr->j = addNode(freq);
                else if(curr->j->max < freq) curr->j->max = freq;
                curr = curr->j;
                break;
      case 'k': if(!curr->k) curr->k = addNode(freq);
                else if(curr->k->max < freq) curr->k->max = freq;
                curr = curr->k;
                break;
      case 'l': if(!curr->l) curr->l = addNode(freq);
                else if(curr->l->max < freq) curr->l->max = freq;
                curr = curr->l;
                break;
      case 'm': if(!curr->m) curr->m = addNode(freq);
                else if(curr->m->max < freq) curr->m->max = freq;
                curr = curr->m;
                break;
      case 'n': if(!curr->n) curr->n = addNode(freq);
                else if(curr->n->max < freq) curr->n->max = freq;
                curr = curr->n;
                break;
      case 'o': if(!curr->o) curr->o = addNode(freq);
                else if(curr->o->max < freq) curr->o->max = freq;
                curr = curr->o;
                break;
      case 'p': if(!curr->p) curr->p = addNode(freq);
                else if(curr->p->max < freq) curr->p->max = freq;
                curr = curr->p;
                break;
      case 'q': if(!curr->q) curr->q = addNode(freq);
                else if(curr->q->max < freq) curr->q->max = freq;
                curr = curr->q;
                break;
      case 'r': if(!curr->r) curr->r = addNode(freq);
                else if(curr->r->max < freq) curr->r->max = freq;
                curr = curr->r;
                break;
      case 's': if(!curr->s) curr->s = addNode(freq);
                else if(curr->s->max < freq) curr->s->max = freq;
                curr = curr->s;
                break;
      case 't': if(!curr->t) curr->t = addNode(freq);
                else if(curr->t->max < freq) curr->t->max = freq;
                curr = curr->t;
                break;
      case 'u': if(!curr->u) curr->u = addNode(freq);
                else if(curr->u->max < freq) curr->u->max = freq;
                curr = curr->u;
                break;
      case 'v': if(!curr->v) curr->v = addNode(freq);
                else if(curr->v->max < freq) curr->v->max = freq;
                curr = curr->v;
                break;
      case 'w': if(!curr->w) curr->w = addNode(freq);
                else if(curr->w->max < freq) curr->w->max = freq;
                curr = curr->w;
                break;
      case 'x': if(!curr->x) curr->x = addNode(freq);
                else if(curr->x->max < freq) curr->x->max = freq;
                curr = curr->x;
                break;
      case 'y': if(!curr->y) curr->y = addNode(freq);
                else if(curr->y->max < freq) curr->y->max = freq;
                curr = curr->y;
                break;
      case 'z': if(!curr->z) curr->z = addNode(freq);
                else if(curr->z->max < freq) curr->z->max = freq;
                curr = curr->z;
                break;
      case ' ': if(!curr->space) curr->space = addNode(freq);
                else if(curr->space->max < freq) curr->space->max = freq;
                curr = curr->space;
                break;
      default:  return nullptr;
    } // end of switch
  } // end of for loop
  return curr;
} // end of createPath

Node* DictionaryTrie::findPath(string word)const{
  // check empty string
  if(!word.length()) return nullptr;
  // temporary pointer to track current node
  auto curr = root;
  // start finding the location for new node
  for(unsigned int i=0; i < word.length(); i++){
    char c = word[i];
    switch(c){
      case 'a': if(!curr->a) return nullptr;
                curr = curr->a;
                break;
      case 'b': if(!curr->b) return nullptr;
                curr = curr->b;
                break;
      case 'c': if(!curr->c) return nullptr;
                curr = curr->c;
                break;
      case 'd': if(!curr->d) return nullptr;
                curr = curr->d;
                break;
      case 'e': if(!curr->e) return nullptr;
                curr = curr->e;
                break;
      case 'f': if(!curr->f) return nullptr;
                curr = curr->f;
                break;
      case 'g': if(!curr->g) return nullptr;
                curr = curr->g;
                break;
      case 'h': if(!curr->h) return nullptr;
                curr = curr->h;
                break;
      case 'i': if(!curr->i) return nullptr;
                curr = curr->i;
                break;
      case 'j': if(!curr->j) return nullptr;
                curr = curr->j;
                break;
      case 'k': if(!curr->k) return nullptr;
                curr = curr->k;
                break;
      case 'l': if(!curr->l) return nullptr;
                curr = curr->l;
                break;
      case 'm': if(!curr->m) return nullptr;
                curr = curr->m;
                break;
      case 'n': if(!curr->n) return nullptr;
                curr = curr->n;
                break;
      case 'o': if(!curr->o) return nullptr;
                curr = curr->o;
                break;
      case 'p': if(!curr->p) return nullptr;
                curr = curr->p;
                break;
      case 'q': if(!curr->q) return nullptr;
                curr = curr->q;
                break;
      case 'r': if(!curr->r) return nullptr;
                curr = curr->r;
                break;
      case 's': if(!curr->s) return nullptr;
                curr = curr->s;
                break;
      case 't': if(!curr->t) return nullptr;
                curr = curr->t;
                break;
      case 'u': if(!curr->u) return nullptr;
                curr = curr->u;
                break;
      case 'v': if(!curr->v) return nullptr;
                curr = curr->v;
                break;
      case 'w': if(!curr->w) return nullptr;
                curr = curr->w;
                break;
      case 'x': if(!curr->x) return nullptr;
                curr = curr->x;
                break;
      case 'y': if(!curr->y) return nullptr;
                curr = curr->y;
                break;
      case 'z': if(!curr->z) return nullptr;
                curr = curr->z;
                break;
      case ' ': if(!curr->space) return nullptr;
                curr = curr->space;
                break;
      default: return nullptr;
    } // end of switch
  } // end of for loop
  return curr;
} // end of createPath

void DictionaryTrie::findWords(Node* n, vector<string>* v)const{
  if(!n || !v) return;
  if(n->word.length())v->push_back(n->word);
  if(n->a) findWords(n->a, v);
  if(n->b) findWords(n->b, v);
  if(n->c) findWords(n->c, v);
  if(n->d) findWords(n->d, v);
  if(n->e) findWords(n->e, v);
  if(n->f) findWords(n->f, v);
  if(n->g) findWords(n->g, v);
  if(n->h) findWords(n->h, v);
  if(n->i) findWords(n->i, v);
  if(n->j) findWords(n->j, v);
  if(n->k) findWords(n->k, v);
  if(n->l) findWords(n->l, v);
  if(n->m) findWords(n->m, v);
  if(n->n) findWords(n->n, v);
  if(n->o) findWords(n->o, v);
  if(n->p) findWords(n->p, v);
  if(n->q) findWords(n->q, v);
  if(n->r) findWords(n->r, v);
  if(n->s) findWords(n->s, v);
  if(n->t) findWords(n->t, v);
  if(n->u) findWords(n->u, v);
  if(n->v) findWords(n->v, v);
  if(n->w) findWords(n->w, v);
  if(n->x) findWords(n->x, v);
  if(n->y) findWords(n->y, v);
  if(n->z) findWords(n->z, v);
  if(n->space) findWords(n->space, v);
} // end of findWords

void DictionaryTrie::checkWords(Node* n, set<Node> &s, unsigned int num)const{
  // check null pointer for n
  if(!n) return;
  // check if word exist in this node
  if(n->word.length()){
    // check if already found num words
    if(s.size() < num)
      s.insert(*n);
    else{
      // replace the lowest freq word if new word has higher freq
      if((*s.begin()).freq < n->freq){
        s.erase(s.begin());
        s.insert(*n);
      }
    }
  }
}


void DictionaryTrie::findWords(Node* n, set<Node> &s, unsigned int num_completion )const{

  if(!n) return;

  // if this node represent a exist word
  if(n->word.length()){

    // if the number of found words less than num_completion
    if(s.size() < num_completion)
      s.insert(*n);

    // already found num_completion words
    else{
      // replace the lowest freq element if new word has higher freq
      if( (*s.begin()).freq < n->freq) {
        s.erase(s.begin());
        s.insert(*n);
      }
    }
  }

  // already found num_completion words
  // compare the max freq in subtree to the lowest freq word in found words
  if(s.size() >= num_completion){
    if(n->a && n->a->max > (*s.begin()).freq) findWords(n->a, s, num_completion);
    if(n->b && n->b->max > (*s.begin()).freq) findWords(n->b, s, num_completion);
    if(n->c && n->c->max > (*s.begin()).freq) findWords(n->c, s, num_completion);
    if(n->d && n->d->max > (*s.begin()).freq) findWords(n->d, s, num_completion);
    if(n->e && n->e->max > (*s.begin()).freq) findWords(n->e, s, num_completion);
    if(n->f && n->f->max > (*s.begin()).freq) findWords(n->f, s, num_completion);
    if(n->g && n->g->max > (*s.begin()).freq) findWords(n->g, s, num_completion);
    if(n->h && n->h->max > (*s.begin()).freq) findWords(n->h, s, num_completion);
    if(n->i && n->i->max > (*s.begin()).freq) findWords(n->i, s, num_completion);
    if(n->j && n->j->max > (*s.begin()).freq) findWords(n->j, s, num_completion);
    if(n->k && n->k->max > (*s.begin()).freq) findWords(n->k, s, num_completion);
    if(n->l && n->l->max > (*s.begin()).freq) findWords(n->l, s, num_completion);
    if(n->m && n->m->max > (*s.begin()).freq) findWords(n->m, s, num_completion);
    if(n->n && n->n->max > (*s.begin()).freq) findWords(n->n, s, num_completion);
    if(n->o && n->o->max > (*s.begin()).freq) findWords(n->o, s, num_completion);
    if(n->p && n->p->max > (*s.begin()).freq) findWords(n->p, s, num_completion);
    if(n->q && n->q->max > (*s.begin()).freq) findWords(n->q, s, num_completion);
    if(n->r && n->r->max > (*s.begin()).freq) findWords(n->r, s, num_completion);
    if(n->s && n->s->max > (*s.begin()).freq) findWords(n->s, s, num_completion);
    if(n->t && n->t->max > (*s.begin()).freq) findWords(n->t, s, num_completion);
    if(n->u && n->u->max > (*s.begin()).freq) findWords(n->u, s, num_completion);
    if(n->v && n->v->max > (*s.begin()).freq) findWords(n->v, s, num_completion);
    if(n->w && n->w->max > (*s.begin()).freq) findWords(n->w, s, num_completion);
    if(n->x && n->x->max > (*s.begin()).freq) findWords(n->x, s, num_completion);
    if(n->y && n->y->max > (*s.begin()).freq) findWords(n->y, s, num_completion);
    if(n->z && n->z->max > (*s.begin()).freq) findWords(n->z, s, num_completion);
    if(n->space && n->space->max > (*s.begin()).freq) findWords(n->space, s, num_completion);
  }
  // if the number of found words less than num_completion
  else{
    if(n->a) findWords(n->a, s, num_completion);
    if(n->b) findWords(n->b, s, num_completion);
    if(n->c) findWords(n->c, s, num_completion);
    if(n->d) findWords(n->d, s, num_completion);
    if(n->e) findWords(n->e, s, num_completion);
    if(n->f) findWords(n->f, s, num_completion);
    if(n->g) findWords(n->g, s, num_completion);
    if(n->h) findWords(n->h, s, num_completion);
    if(n->i) findWords(n->i, s, num_completion);
    if(n->j) findWords(n->j, s, num_completion);
    if(n->k) findWords(n->k, s, num_completion);
    if(n->l) findWords(n->l, s, num_completion);
    if(n->m) findWords(n->m, s, num_completion);
    if(n->n) findWords(n->n, s, num_completion);
    if(n->o) findWords(n->o, s, num_completion);
    if(n->p) findWords(n->p, s, num_completion);
    if(n->q) findWords(n->q, s, num_completion);
    if(n->r) findWords(n->r, s, num_completion);
    if(n->s) findWords(n->s, s, num_completion);
    if(n->t) findWords(n->t, s, num_completion);
    if(n->u) findWords(n->u, s, num_completion);
    if(n->v) findWords(n->v, s, num_completion);
    if(n->w) findWords(n->w, s, num_completion);
    if(n->x) findWords(n->x, s, num_completion);
    if(n->y) findWords(n->y, s, num_completion);
    if(n->z) findWords(n->z, s, num_completion);
    if(n->space) findWords(n->space, s, num_completion);
  }
} // end of findWords


void DictionaryTrie::deleteAll(Node* n){
  if(!n) return;
  if(n->a) deleteAll(n->a);
  if(n->b) deleteAll(n->b);
  if(n->c) deleteAll(n->c);
  if(n->d) deleteAll(n->d);
  if(n->e) deleteAll(n->e);
  if(n->f) deleteAll(n->f);
  if(n->g) deleteAll(n->g);
  if(n->h) deleteAll(n->h);
  if(n->i) deleteAll(n->i);
  if(n->j) deleteAll(n->j);
  if(n->k) deleteAll(n->k);
  if(n->l) deleteAll(n->l);
  if(n->m) deleteAll(n->m);
  if(n->n) deleteAll(n->n);
  if(n->o) deleteAll(n->o);
  if(n->p) deleteAll(n->p);
  if(n->q) deleteAll(n->q);
  if(n->r) deleteAll(n->r);
  if(n->s) deleteAll(n->s);
  if(n->t) deleteAll(n->t);
  if(n->u) deleteAll(n->u);
  if(n->v) deleteAll(n->v);
  if(n->w) deleteAll(n->w);
  if(n->x) deleteAll(n->x);
  if(n->y) deleteAll(n->y);
  if(n->z) deleteAll(n->z);
  if(n->space) deleteAll(n->space);
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