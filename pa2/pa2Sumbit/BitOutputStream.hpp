/*
 * Name: Chao Huang, Yeung-Kit Wong
 * Date: Aug 13, 2016
 * File: BitOutputStream.hpp
 */

#ifndef BITOUTPUTSTREAM_HPP
#define BITOUTPUTSTREAM_HPP

#include <iostream>

using namespace std;

class BitOutputStream{
private:
  // buffer
  char b;
  // number of bits in buffer
  int n;
  ostream& out;
public:
  // constructor
  BitOutputStream(ostream& os): out(os), b(0), n(0){}
  // send buffer to output and clear it
  void flush();
  void writeBit(int i);
  void writeInt(int i);
  void writeByte();
};

#endif // BITOUTPUTSTREAM_HPP
