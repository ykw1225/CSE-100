/*
 * Name: Chao Huang, Yeung-Kit Wong
 * Date: Aug 13, 2016
 * File: BitInputStream.cpp
 */

#include <iostream>
#include <sstream>
#include <bitset>
#include "BitInputStream.hpp"

using namespace std;

const int BYTESIZE = 8;
const int RIGHT3BYTES = 24;
const int RIGHT23BITS = 23;

void BitInputStream::fill(){
  in.get(b);
  n = 0;
}


int BitInputStream::readBit(){
  if( n== BYTESIZE )
    fill();

  int rv = (b >> (BYTESIZE - n - 1) ) & 0x1;

  b &= (0x1 << (BYTESIZE - n - 1) ^ 0xFF );

  n++;

  return rv;
}

int BitInputStream::readInt(){
  int rv = 0;
  for( int i = 0; i < RIGHT3BYTES; i++, rv<<=1 ){
    int temp = readBit();

    if(temp)
      rv |= 0x0001;
    if( i == RIGHT23BITS ) break;
  }
  return rv;
}
