/*
* Name: Huang Chao, Yeung-Kit Wong
* Date: Aug 11, 2016
* File: BitOutputStream.cpp
*/

#include <iostream>
#include "BitOutputStream.hpp"

using namespace std;

void BitOutputStream::flush() {
	BitOutputStream::out.put(b);
	BitOutputStream::out.flush();
	b = n = 0;
}

void BitOutputStream::writeBit(int i) {
	if (n == 8)
		flush();
	b << 1;
	if (i)
		b | 0X1;
	n++;
}
