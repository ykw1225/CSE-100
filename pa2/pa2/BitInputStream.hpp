/*
* Name: Huang Chao, Yeung-Kit Wong
* Date: Aug 11, 2016
* File: BitInputStream.hpp
*/

#ifndef BITINPUTSTREAM_HPP
#define BITINPUTSTREAM_HPP

#include <iostream>

using namespace std;

class BitInputStream {
private:
	// one byte buffer
	char b;
	// number of bits write in b
	int n;
	istream& in;
public:
	// constructor
	BitInputStream(istream& is) : in(is), b(0), n(8) {}
	// fill the buffer from input
	void fill();
	int readBit();
};

#endif // BITINPUTSTREAM_HPP