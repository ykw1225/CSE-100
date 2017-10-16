/*
 * Name: Chao Huang, Yeung-Kit Wong
 * Date: Aug 13, 2016
 * File: BitOutputStream.cpp
 */

#include <iostream>
#include <stack>
#include <bitset>
#include "BitOutputStream.hpp"

using namespace std;

const int BYTESIZE = 8;
const int TWO = 2;
const int RIGHT3BYTES = 24;

void BitOutputStream::flush(){
  out.put(b);
  out.flush();
  b = n = 0;
}

void BitOutputStream::writeBit(int i){
  if(i > 1){
    writeInt(i);
    return;
  }
  if(n)
    b <<= 1;
  if(i)
    b |= 0X1;
  n++;
  if(n == BYTESIZE)
    flush();
}

void BitOutputStream::writeInt(int i){
  stack<int> s;
  while(i){
    if( i % TWO )
      s.push(1);
    else
      s.push(0);
    i/= TWO;
  }

  // frequency for each symbol is less than 10million
  // only need 24 bits to save that integer
  while(s.size() < RIGHT3BYTES )
    s.push(0);
  while(s.size()){
    writeBit(s.top());
    s.pop();
  }
}

void BitOutputStream::writeByte(){
  if(!n) return;
  while( n < BYTESIZE ){

    writeBit(0);

    if(!n) return;
  }
  flush();
}

