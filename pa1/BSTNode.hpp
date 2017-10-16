/*
 * Name:  Chao Huang & Yeung Kit Wong
 * Date:  AUG 5, 2016
 * File:  BSTNode.hpp
 */

#ifndef BSTNODE_HPP
#define BSTNODE_HPP
#include <iostream>
#include <iomanip>

template<typename Data>
class BSTNode {

public:

  /** Constructor.  Initialize a BSTNode with the given Data item,
   *  no parent, and no children.
   */
  BSTNode(const Data & d) : data(d) {
    left = right = parent = 0;
  }

  BSTNode<Data>* left;
  BSTNode<Data>* right;
  BSTNode<Data>* parent;
  Data const data;   // the const Data in this node.

  /** Return the successor of this BSTNode in a BST, or 0 if none.
   ** PRECONDITION: this BSTNode is a node in a BST.
   ** POSTCONDITION:  the BST is unchanged.
   ** RETURNS: the BSTNode that is the successor of this BSTNode,
   ** or 0 if there is none.
   */
  BSTNode<Data>* successor() {

    // check if this node is null
    if( this == nullptr ) return 0;

    // return left most node of rightchild if there is a rightchild
    if (this->right) {

      // temporary variable for tracking
      BSTNode<Data>* temp = this->right;

      // keep going left subtree untill reach a null node
      while (temp->left != nullptr)
        temp = temp->left;

      return temp;

    } // end of right subtree

    // return the parent whose leftsubtree contain the this node if no rightchild
    if (this->right == nullptr){

      // tracking variable for current node
      BSTNode<Data>*curr = this;

      // tracking variable for the parent of current node
      BSTNode<Data>*parent = this->parent;

      // tracking up until found the parent whose leftsubtree contain the this node
      while (parent != nullptr && curr == parent-> right) {
          curr = parent;
          parent = curr->parent;
      }

      return parent;

    } // end of parent

    return 0;

  } // end of successor

};

/** Overload operator<< to print a BSTNode's fields to an ostream. */
template <typename Data>
std::ostream & operator<<(std::ostream& stm, const BSTNode<Data> & n) {
  stm << '[';
  stm << std::setw(10) << &n;                 // address of the BSTNode
  stm << "; p:" << std::setw(10) << n.parent; // address of its parent
  stm << "; l:" << std::setw(10) << n.left;   // address of its left child
  stm << "; r:" << std::setw(10) << n.right;  // address of its right child
  stm << "; d:" << n.data;                    // its data field
  stm << ']';
  return stm;
}

#endif // BSTNODE_HPP
