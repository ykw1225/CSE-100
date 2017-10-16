/*
 * Name:  Chao Huang & Yeung Kit Wong
 * Date:  AUG 5, 2016
 * File:  BST.hpp
 */

#ifndef BST_HPP
#define BST_HPP
#include "BSTNode.hpp"
#include "BSTIterator.hpp"
#include <iostream>

template<typename Data>
class BST {

protected:

  /** Pointer to the root of this BST, or 0 if the BST is empty */
  BSTNode<Data>* root;

  /** Number of Data items stored in this BST. */
  unsigned int isize;

  /** Height of this BST. */
  unsigned int iheight;

public:

  /** define iterator as an aliased typename for BSTIterator<Data>. */
  typedef BSTIterator<Data> iterator;

  /** Default constructor.
      Initialize an empty BST.
   */
  BST() : root(0), isize(0), iheight(0) {  }


  /** Default destructor.
      Delete every node in this BST.
   */
  virtual ~BST() {
    deleteAll(root);
    root = nullptr;
    isize = 0;
    return;
  }

  /** Given a reference to a Data item, insert a copy of it in this BST.
   *  Return  true if the item was added to this BST
   *  as a result of this call to insert,
   *  false if an item equal to this one was already in this BST.
   *  Note: This function should use only the '<' operator when comparing
   *  Data items. (should not use ==, >, <=, >=)  For the reasoning
   *  behind this, see the assignment writeup.
   */
  virtual bool insert(const Data& item) {
    // For helpful pseudocode, refer to Paul Kube's
    // 3rd Lecture, 7th slide.

    // check if the BST is empty
    if (empty()) {
      root = new BSTNode<Data>(item);
      ++isize;
      return true;
    }

    // BST is not empty

    // temporary variable for keep tracking current node
    auto currNode = root;

    // temporary variable for keep tracking what level is the new node in BST
    unsigned int countHeight = 0;

    // start finding the new location for the new node
    while(!empty()) {

      // if item < current, in left
      if(item < currNode->data) {

        // increament for the level tracker
        countHeight++;

        // check a leftchild exist already
        if (currNode->left == nullptr) {

          // no leftchilde then make the new node as the leftchild
          currNode->left = new BSTNode<Data>(item);

          // make current node as the parent of new node
          currNode->left->parent = currNode;

          // increament for the size of the BST
          ++isize;

          // check if the new node make a new height of the BST
          if (countHeight > iheight)
            iheight = countHeight;

          return true;
        }

        // leftchild doesn't exist then go deeper on left subtree
        else
          currNode = currNode->left;

      } // end of if item < current

      //else if item > current, in right
      else if (currNode->data < item) {

        // increament for the level tracker
        countHeight++;

        // check a rightchild exist already
        if (currNode->right == nullptr) {

          // no rightchild then make the new node as the rightchild
          currNode->right = new BSTNode<Data>(item);

          // make current node as the parent of new node
          currNode->right->parent = currNode;

          // increament for the size of the BST
          ++isize;

          // check if the new node make a new height of the BST
          if (countHeight > iheight)
            iheight = countHeight;

          return true;
        }

        // rightchild doesn't exist then go deeper on right subtree
        else
            currNode = currNode->right;

      } // end of if item > current

      // 3rd case item == current
      else
        // found key in BST
        return false;

    } // end of while

    return true;

  } // end of insert


  /** Find a Data item in the BST.
   *  Return an iterator pointing to the item, or pointing past
   *  the last node in the BST if not found.
   *  Note: This function should use only the '<' operator when comparing
   *  Data items. (should not use ==, >, <=, >=).  For the reasoning
   *  behind this, see the assignment writeup.
   */
  iterator find(const Data& item) const {
    // For helpful pseudocode, refer to Paul Kube's
    // 3rd Lecture, 6th Slide.

    // tree empty, return last node
    if( empty() )
      return end();

    // set currNode = root
    auto currNode = root;

    // start finding the node
    while( currNode != nullptr ) {

      // item < current.key , in left
      if( item < currNode->data )
        currNode = currNode->left;

      // else if item > current.key , in right
      else if (currNode->data < item)
        currNode = currNode->right;

      // else found key in currNode
      else
        return typename BST<Data>::iterator(currNode);

    } // end of while

    // return last node if not found
    return end();

  } // end of find


  /** Return the number of items currently in the BST.
   */
  unsigned int size() const {
    return isize;
  }

  /** Return the height of the BST.
   */
  unsigned int height() const {
    return iheight;
  }


  /** Return true if the BST is empty, else false.
   */
  bool empty() const {
    if (root == nullptr)
      return true;
    return false;
  }

  /** Return an iterator pointing to the first item in the BST (not the root).
   */
  iterator begin() const {
    return typename BST<Data>::iterator(first(root));
  }

  /** Return an iterator pointing past the last item in the BST.
   */
  iterator end() const {
    return typename BST<Data>::iterator(0);
  }

  /** Perform an inorder traversal of this BST.
   */
  void inorder() const {
    inorder(root);
  }


private:

  /** Recursive inorder traversal 'helper' function */

  /** Inorder traverse BST, print out the data of each node in ascending order.
      Implementing inorder and deleteAll base on the pseudo code is an easy way to get started.
   */
  void inorder(BSTNode<Data>* n) const {
    /* Pseudo Code:
       if current node is null: return;
       recursively traverse left sub-tree
       print current node data
       recursively traverse right sub-tree
     */

    // if BST is an empty tree just return
    if (empty()) return;

    // if n is null just return
    if (!n) return;

    // recursively run function at leftsubtree
    inorder(n->left);

    // print out the data
    std::cout << n->data;

    // recursively run function at rightsubtree
    inorder(n->right);
  }


  /** Find the first element of the BST
   */
  static BSTNode<Data>* first(BSTNode<Data>* root) {
    if(root == 0) return 0;
    while(root->left != 0) root = root->left;
    return root;
  }

  /** postorder traversal, deleting nodes
   */
  static void deleteAll(BSTNode<Data>* n) {
    /* Pseudo Code:
      if current node is null: return;
      recursively delete left sub-tree
      recursively delete right sub-tree
      delete current node
    */

    if(n == nullptr) return;
    deleteAll(n->left);
    deleteAll(n->right);
    delete n;
    n = 0;
  }

};


#endif //BST_HPP
