/*
* Name: Huang Chao, Yeung-Kit Wong
* Date: Aug 09, 2016
* File: HCTree.hpp
*/

#ifndef HCTREE_HPP
#define HCTREE_HPP

#include <queue>
#include <vector>
#include <fstream>
#include "HCNode.hpp"
#include "BitInputStream.hpp"
#include "BitOutputStream.hpp"

using namespace std;

/** A 'function class' for use as the Compare class in a
*  priority_queue<HCNode*>.
*  For this to work, operator< must be defined to
*  do the right thing on HCNodes.
*/
class HCNodePtrComp {
public:
	bool operator()(HCNode*& lhs, HCNode*& rhs) const {
		return *lhs < *rhs;
	}
};

/** A Huffman Code Tree class.
*  Not very generic:  Use only if alphabet consists
*  of unsigned chars.
*/
class HCTree {
private:
	HCNode* root;
	vector<HCNode*> leaves;

	// helper function for recursivly printing HC tree
	void printNode(HCNode*);

public:
	explicit HCTree() : root(0) {
		leaves = vector<HCNode*>(256, (HCNode*)0);
	}

	~HCTree();

	/** Use the Huffman algorithm to build a Huffman coding trie.
	*  PRECONDITION: freqs is a vector of ints, such that freqs[i] is
	*  the frequency of occurrence of byte i in the message.
	*  POSTCONDITION:  root points to the root of the trie,
	*  and leaves[i] points to the leaf node containing byte i.
	*/
	void build(const vector<int>& freqs);

	/** Write to the given BitOutputStream
	*  the sequence of bits coding the given symbol.
	*  PRECONDITION: build() has been called, to create the coding
	*  tree, and initialize root pointer and leaves vector.
	*/
	void encode(byte symbol, BitOutputStream& out) const;

	/** Write to the given ofstream
	*  the sequence of bits (as ASCII) coding the given symbol.
	*  PRECONDITION: build() has been called, to create the coding
	*  tree, and initialize root pointer and leaves vector.
	*  THIS METHOD IS USEFUL FOR THE CHECKPOINT BUT SHOULD NOT
	*  BE USED IN THE FINAL SUBMISSION.
	*/
	void encode(byte symbol, ofstream& out) const;


	/** Return symbol coded in the next sequence of bits from the stream.
	*  PRECONDITION: build() has been called, to create the coding
	*  tree, and initialize root pointer and leaves vector.
	*/
	int decode(BitInputStream& in) const;

	/** Return the symbol coded in the next sequence of bits (represented as
	*  ASCII text) from the ifstream.
	*  PRECONDITION: build() has been called, to create the coding
	*  tree, and initialize root pointer and leaves vector.
	*  THIS METHOD IS USEFUL FOR THE CHECKPOINT BUT SHOULD NOT BE USED
	*  IN THE FINAL SUBMISSION.
	*/
	int decode(ifstream& in) const;

	// Helper function for printing out the whole HC tree.
	void printAll();

	void HCTree::deleteNode(HCNode* node);

};

#endif // HCTREE_HPP
