/*
 * Name: Chao Huang, Yeung-Kit Wong
 * Date: Aug 11, 2016
 * File: BitInputStream.hpp
 */

#ifndef BITINPUTSTREAM_HPP
#define BITINPUTSTREAM_HPP

#include <iostream>

using namespace std;

const int BYTEBUFFSIZE = 8;

class BitInputStream {
private:

  // one byte buffer
  char b;

  // number of bits write in b
  int n;

  // input stream
  istream& in;

public:

  // constructor
  BitInputStream(istream& is): in(is), b(0), n(BYTEBUFFSIZE){}

  // fill the buffer from input
  void fill();

  // read a bit from input
  int readBit();

  // read an interger from input
  int readInt();

};

#endif // BITINPUTSTREAM_HPP
