/*
* Name: Huang Chao, Yeung-Kit Wong
* Date: Aug 11, 2016
* File: BitOutputStream.hpp
*/

#ifndef BITOUTPUTSTREAM_HPP
#define BITOUTPUTSTREAM_HPP

#include <iostream>

using namespace std;

class BitOutputStream {
private:
	// buffer
	char b;
	// number of bits in buffer
	int n;
	ostream& out;
public:
	// constructor
	BitOutputStream(ostream& os) : out(os), b(0), n(0) {}
	// send buffer to output and clear it
	void flush();
	void writeBit(int i);
};

#endif // BITOUTPUTSTREAM_HPP