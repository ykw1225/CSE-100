/*
* Name: Huang Chao, Yeung-Kit Wong
* Date: Aug 09, 2016
* File: HCNode.cpp
*/

#include "HCNode.hpp"

using namespace std;

// a operator < overload function for HCNode object
bool HCNode::operator<(const HCNode& other) {
	if (count == other.count)
		return symbol > other.symbol;
	else
		return count > other.count;
}

// a comparison function for HCNode object
bool comp(HCNode* one, HCNode* other) {
	return &one < &other;
}
