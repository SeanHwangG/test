/** Implementation of generic binary search Tree
 *  The BST stores the size and height of the tree
 *
 *  name  : Gyuseung Hwang
 *  email : g5hwang@ucsd.edu
 */

#ifndef BST_HPP
#define BST_HPP

#include <iostream>

#include "BSTIterator.hpp"
#include "BSTNode.hpp"

using namespace std;

/** Implementation of generic Binary Search Tree
 *  It stores the size and height of the tree.
 */
template <typename Data>
class BST {
 protected:
  /** Pointer to the root of this BST, or 0 if the BST is empty */
  BSTNode<Data> *root;

  unsigned int isize;  // Number of Data items stored in this BST.
  unsigned int iheight;

 public:
  typedef BSTIterator<Data> iterator;
  BST() : root(0), isize(0), iheight(0) {}
  virtual ~BST() { deleteAll(root); }

  /** Given a reference to a Data item, insert a copy of it in this BST.
   *
   *  @param item : item to insert
   *  @return     : true if item was successfully inserted
   *                false if duplicate item was found
   */
  virtual bool insert(const Data &item) {
    if (!root) {
      root = new BSTNode<Data>(item);
      isize = 1;
      iheight = 0;
      return true;
    }

    BSTNode<Data> *cur = root, *toInsert = new BSTNode<Data>(item);
    unsigned int depth = 0;

    // compare with possible parent and move down tree
    while (true) {
      if (cur->data < item) {
        // update potential parent
        if (cur->right) {
          cur = cur->right;
          depth++;
        }
        // cannot go down, so insert node and break
        else {
          cur->right = toInsert;
          toInsert->parent = cur;
          break;
        }
      } else if (item < cur->data) {
        if (cur->left) {
          cur = cur->left;
          depth++;
        } else {
          cur->left = toInsert;
          toInsert->parent = cur;
          break;
        }
      } else {  // found duplicate, cannot insert
        return false;
      }
    }
    isize++;
    iheight = max(depth + 1, iheight);

    return true;
  }

  /** Find a Data item in the BST.
   *  Return an iterator pointing to the item, or pointing past the last node in the BST if not found.
   *
   *  @param item : data to search on BST
   *  @return     : if data found, return an iterator pointing to found Node otherwise, past to the last node
   */
  virtual iterator find(const Data &item) const {
    BSTNode<Data> *cur = root;

    // keep move down the treet
    while (cur) {
      if (cur->data < item) {
        cur = cur->right;
      } else if (item < cur->data) {
        cur = cur->left;
      }
      // found the tree, return iterator
      else {
        return BSTIterator<Data>(cur);
      }
    }

    return end();
  }

  unsigned int size() const { return isize; }
  unsigned int height() const { return iheight; }
  bool empty() const { return isize == 0; }

  iterator begin() const { return BST::iterator(first(root)); }
  iterator end() const { return typename BST<Data>::iterator(0); }

  void inorder() const {
    cout << "Printing inorder BST" << endl;
    for (iterator it = begin(); it != end(); ++it) {
      cout << *it << endl;
    }
    cout << endl;
  }

 private:
  /** Find the first element of the BST
   *  @root   : BST Node that we want to find the first element
   *  @return : the first element of the BST
   */
  static BSTNode<Data> *first(BSTNode<Data> *root) {
    // find the smallest element
    while (root && root->left) {
      root = root->left;
    }

    return root;
  }

  static void deleteAll(BSTNode<Data> *cur) {
    if (cur != nullptr) {
      deleteAll(cur->left);
      deleteAll(cur->right);
      delete (cur);
    }
  }
};

#endif  // BST_HPP
