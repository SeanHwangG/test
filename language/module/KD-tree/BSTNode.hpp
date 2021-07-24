/** Implemenation of generic binary search tree node
 *  The node can access its parent and next greater element
 *
 *  name  : Gyuseung Hwang
 *  email : g5hwang@ucsd.edu
 */

#ifndef BSTNODE_HPP
#define BSTNODE_HPP

#include <iomanip>
#include <iostream>

using namespace std;

/** Implementation of generic binary search tree node
 *  The node can access its parent and next greater element
 */
template <typename Data>
class BSTNode {
 public:
  BSTNode() { data = left = right = parent = nullptr; }
  BSTNode(const Data &d) : data(d) { left = right = parent = nullptr; }
  BSTNode<Data> *left, *right, *parent;

  Data const data;  // the const Data in this node.

  /** Return the successor of this BSTNode in a BST, or 0 if none.
   *  @return : successor node of this node	  0 if there is none
   */
  BSTNode<Data> *successor() {
    // case 1 : right child's left most child
    if (right) {
      BSTNode<Data> *ret = right;
      while (ret->left) ret = ret->left;

      return ret;
    } else {
      if (parent) {
        // case 2 : current node is left child
        if (parent->left == this) return parent;
        // case 3 : current node is right child    go up until current node is left
        else {
          BSTNode<Data> *ret = this;
          while (ret->parent) {
            // if current node if left child, return
            if (ret->parent->left == ret) return ret->parent;
            ret = ret->parent;
          }
          return nullptr;
        }
      } else {
        return nullptr;
      }
    }
  }
};

/** Overload operator<< to print a BSTNode's fields to an ostream.
 *  @param stm : where we output the information
 * 		   n   : BST node we wants to access info
 *  @return    : outstream containing address info of the nodes
 */
template <typename Data>
ostream &operator<<(ostream &stm, const BSTNode<Data> &n) {
  stm << '[';
  stm << setw(10) << &n;                  // address of the BSTNode
  stm << "; p:" << setw(10) << n.parent;  // address of its parent
  stm << "; l:" << setw(10) << n.left;    // address of its left child
  stm << "; r:" << setw(10) << n.right;   // address of its right child
  stm << "; d:" << n.data;                // its data field
  stm << ']';
  return stm;
}

#endif  // BSTNODE_HPP
