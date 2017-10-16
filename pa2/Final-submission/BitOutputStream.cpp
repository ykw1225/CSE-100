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
  
  // write buffer to output
  out.put(b);
  
  // call the flush function from ostream class
  out.flush();
  
  // reset class members
  b = n = 0;
  
}

void BitOutputStream::writeBit(int i){
  
  // if the argument larger than 1
  if(i > 1){
    writeInt(i);
    return;
  }
  
  // if buffer is empty
  if(n)
    b <<= 1;
  
  // if the bit is 1
  if(i)
    b |= 0X1;
  
  // increment for n
  n++;
  
  // if buffer is full
  if(n == BYTESIZE)
    flush();
  
}

void BitOutputStream::writeInt(int i){
  
  // stack for storing every bit of integer in binary form
  stack<int> s;
  
  // convert the integer to binary
  while(i){
    
    // if remainder is 1
    if( i % TWO )
      s.push(1);
    
    // if remainder is 0
    else
      s.push(0);
    
    // i = i/2
    i/= TWO;
    
  } // end of while

  // frequency for each symbol is less than 10million
  // only need 24 bits to save that integer
  
  // filling rest of bit with 0
  while(s.size() < RIGHT3BYTES )
    s.push(0);
  
  // write each bit to output
  while(s.size()){
    writeBit(s.top());
    s.pop();
  }
  
}

void BitOutputStream::writeByte(){
  
  // if buffer is full
  if(!n) return;
  
  // if buffer is not full
  while( n < BYTESIZE ){

    // fill the buffer with 0
    writeBit(0);

    // if buffer is empty
    if(!n) return;
    
  }
  
  flush();
  
}

