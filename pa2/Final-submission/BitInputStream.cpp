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
  
  // fill the buffer from input stream
  in.get(b);
  
  // reset n
  n = 0;
  
}


int BitInputStream::readBit(){
  
  // check if buffer is full
  if( n== BYTESIZE )
    fill();

  // get the most significant bit of buffer
  int rv = (b >> (BYTESIZE - n - 1) ) & 0x1;

  // delete the most significant bit of buffer
  b &= (0x1 << (BYTESIZE - n - 1) ^ 0xFF );

  // increment of n
  n++;

  return rv;
  
}


// function for read an integer
int BitInputStream::readInt(){
  
  // return value
  int rv = 0;
  
  // loop each bit of integer
  for( int i = 0; i < RIGHT3BYTES; i++, rv<<=1 ){
    
    // temporary variable for a bit
    int temp = readBit();

    // check if temp is 0 or 1
    if(temp)
      rv |= 0x0001;
    
    // check if alreay read 4 byte
    if( i == RIGHT23BITS ) break;
    
  } // end of for loop
  
  return rv;
  
}
