/*
 * Name:  Chao Huang & Yeung Kit Wong
 * Date:  AUG 5, 2016
 * File:  BSTIterator.hpp
 */

#ifndef BSTITERATOR_HPP
#define BSTITERATOR_HPP
#include "BSTNode.hpp"
#include <list>
#include <iterator>

/*
 * 
 * For more on iterators, refer to Paul Kube's
 * 3rd Lecture, starting on Slide 14.
 */

template<typename Data>
class BSTIterator : public std::iterator<std::input_iterator_tag,Data> {

private:

  BSTNode<Data>* curr;

public:

  /** Constructor.  Use the argument to initialize the current BSTNode
   *  in this BSTIterator.
   */
  BSTIterator(BSTNode<Data>* curr) {
    this->curr = curr;
  }

  /** Dereference operator. */
  Data operator*() const {
    return curr->data;
  }

  /** Pre-increment operator. */
  BSTIterator<Data>& operator++() {
    curr = curr->successor();
    return *this;
  }

  /** Post-increment operator. */
  BSTIterator<Data> operator++(int) {
    BSTIterator before = BSTIterator(curr);
    ++(*this);
    return before;
  }

  /** Equality test operator. */
  bool operator==(BSTIterator<Data> const & other) const {

    // if two iterator are pointing to the same location
    if( curr == other.curr )
      return true;

    // if they are not
    return false;
  }

  /** Inequality test operator. */
  bool operator!=(BSTIterator<Data> const & other) const {
    if( curr != other.curr )
      return true;
    return false;
  }
};

#endif //BSTITERATOR_HPP
