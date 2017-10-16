/*
* Name: Huang Chao, Yeung-Kit Wong
* Date: Aug 11, 2016
* File: BitInputStream.cpp
*/

#include <iostream>
#include "BitInputStream.hpp"

using namespace std;

void BitInputStream::fill() {
	in.get(b);
	n = 0;
}


int BitInputStream::readBit() {
	if (n == 8)
		fill();
	int rv = b & 0X1;
	b = b >> 1;
	n++;
	return rv;
}
