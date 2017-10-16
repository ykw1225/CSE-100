/*
* Name: Huang Chao, Yeung-Kit Wong
* Date: Aug 09, 2016
* File: HCTree.cpp
*/

#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include "HCTree.hpp"
#include "HCNode.hpp"

using namespace std;

// a function that building a HC tree
void HCTree::build(const vector<int>& freqs) {

	// check if the vector is empty
	if (!freqs.size()) return;

	// a priority queue for storing all symbols appear in file
	priority_queue<HCNode*, vector<HCNode*>, HCNodePtrComp> q;

	// start to find the symbols appear in file
	for (int i = 0; i < freqs.size(); i++) {
		if (freqs[i]) {
			// make a HC node for the new appeared symbol
			leaves[i] = new HCNode(freqs.at(i), i);
			// put the new node into the queue
			q.push(leaves[i]);
		}
	} // end of for loop

	  // if there is only one node, make a dummy node
	if (q.size() == 1) q.push(new HCNode(0, 0));

	// start to linking all nodes in queue to build a tree
	while (q.size() > 1) {
		// make a dummy node as the parent of two lowest frequece nodes
		auto temp = new HCNode(0, 0);
		// linking the dummy node to the first lowest node as child 0
		temp->c0 = q.top(); q.pop();
		// linking the first lowest node to the dummy node as parent
		temp->c0->p = temp;
		// linking the dummy node to the second lowest node as child 1
		temp->c1 = q.top(); q.pop();
		// linking the second lowest node to the dummy node as parent
		temp->c1->p = temp;
		// update the count of dummy node by adding sum of count of two childnode
		temp->count = temp->c0->count + temp->c1->count;
		// push back the dummy node into the queue
		q.push(temp);
	} // end of while loop

	  // set the last dummy node as the root of the HC tree
	root = q.top(); q.pop();
} // end of build

void HCTree::encode(byte symbol, BitOutputStream& out)const {
	// check if the HC tree is empty
	if (!root) return;

	// temporary variable for storing each bit of code
	vector<int> v;

	// temporary variable
	HCNode* currNode = leaves[symbol];

	// check if the node is NULL or the node appear in file
	if (!currNode || currNode->count == 0)
		return;

	// start to traverse from leaf node to root
	while (currNode != root) {
		// check if the current node is a leftchild
		if (currNode->p->c0 == currNode)
			v.push_back(0);
		// check if the current node is a rightchild
		else if (currNode->p->c1 == currNode)
			v.push_back(1);
		// update current node to the parent
		currNode = currNode->p;
	} // end of while

	  // start to write the code into file
	while (!v.empty()) {
		// check if the last element of vector is 1 or 0
		if (v.back()) {
			out.writeBit(v.back());
		}
		else {
			out.writeBit(v.back());
		}
		// pulling out the last element in the vector
		v.pop_back();
	} // end of while
} // end of encode

  // a function that encoding the symbol into binary code
void HCTree::encode(byte symbol, ofstream& out)const {

	// check if the HC tree is empty
	if (!root) return;

	// temporary variable for storing each bit of code
	vector<int> v;

	// temporary variable
	HCNode* currNode = leaves[symbol];

	// check if the node is NULL or the node appear in file
	if (!currNode || currNode->count == 0)
		return;

	// start to traverse from leaf node to root
	while (currNode != root) {
		// check if the current node is a leftchild
		if (currNode->p->c0 == currNode)
			v.push_back(0);
		// check if the current node is a rightchild
		else if (currNode->p->c1 == currNode)
			v.push_back(1);
		// update current node to the parent
		currNode = currNode->p;
	} // end of while

	  // start to write the code into file
	while (!v.empty()) {
		// check if the last element of vector is 1 or 0
		if (v.back()) {
			out.put('1');
		}
		else {
			out.put('0');
		}
		// pulling out the last element in the vector
		v.pop_back();
	} // end of while
} // end of encode


int HCTree::decode(BitInputStream& in)const {

	// check if empty tree
	if (!root) return EXIT_FAILURE;

	// temporary variable for tracking current node
	auto currNode = root;

	// start to find the symbol
	// check if the node has no child
	while (currNode->c0 || currNode->c1) {
		// temporary char var for a bit of code
		char c = in.readBit();
		// check what number is this bit
		if (c == '0')
			currNode = currNode->c0;
		else if (c == '1')
			currNode = currNode->c1;
		// if this bit is neither 1 nor 0
		else {
			cout << "Unexpected number found!" << endl;
			return -1;
		}
	} // end of while

	return currNode->symbol;

}

// a function that decoding the binary code into symbol
int HCTree::decode(ifstream& in)const {

	// check if empty tree
	if (!root) return EXIT_FAILURE;

	// temporary variable for tracking current node
	auto currNode = root;

	// start to find the symbol
	// check if the node has no child
	while (currNode->c0 || currNode->c1) {
		// temporary char var for a bit of code
		char c = in.get();
		// check what number is this bit
		if (c == '0')
			currNode = currNode->c0;
		else if (c == '1')
			currNode = currNode->c1;
		// if this bit is neither 1 nor 0
		else {
			cout << "Unexpected number found!" << endl;
			return -1;
		}
	} // end of while

	return currNode->symbol;
} // end of decode

  // helper function for destructor to delete all nodes recursively
void HCTree::deleteNode(HCNode* node) {
	if (!node) return;
	deleteNode(node->c0);
	deleteNode(node->c1);
	delete node;
}

// destructor for HCTree object
HCTree::~HCTree() {
	deleteNode(root);
	for (int i = 0; i < leaves.size(); i++)
		delete leaves[i];
}

void HCTree::printNode(HCNode* node) {
	if (!node) return;
	cout << "\nSymbol: " << node->symbol << " Count: " << node->count;
	if (node->c0)
		cout << " Child0: " << node->c0->symbol;
	if (node->c1)
		cout << " Child1: " << node->c1->symbol;
	if (node->p)
		cout << " Parent: " << node->p->symbol;
	if (node->c0)
		printNode(node->c0);
	if (node->c1)
		printNode(node->c1);
} // end of printNode


void HCTree::printAll() {
	printNode(root);
	cout << endl;
	// printing all leaves
	for (int i = 0; i<leaves.size(); i++) {
		if (leaves[i]) {
			cout << "Leave " << i << ": ";
			cout << "Symbol: " << leaves[i]->symbol
				<< " Count: " << leaves[i]->count
				<< " Parent: " << leaves[i]->p->count
				<< endl;
		}
	}
	cout << "Finished printing HCTree!" << endl;
} // end of printAll