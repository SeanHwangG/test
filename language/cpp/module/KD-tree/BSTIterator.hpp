/** Iterator for binary search tree
 *
 * name  : Gyuseung Hwang
 * email : g5hwang@ucsd.edu
 */

#ifndef BSTITERATOR_HPP
#define BSTITERATOR_HPP

#include <iterator>
#include <list>

#include "BSTNode.hpp"

using namespace std;

/** Implementation of generic Binary Search Tree Iterator
 *  It overloads preorder and dereference operator
 */
template <typename Data>
class BSTIterator : public iterator<input_iterator_tag, Data> {
 private:
  BSTNode<Data> *curr;

 public:
  BSTIterator(BSTNode<Data> *curr) : curr(curr) {}

  Data operator*() const { return curr->data; }

  BSTIterator<Data> &operator++() {
    curr = curr->successor();
    return *this;
  }

  BSTIterator<Data> operator++(int) {
    BSTIterator before = BSTIterator(curr);
    ++(*this);
    return before;
  }

  bool operator==(BSTIterator<Data> const &other) const {
    if (!curr || !(other.curr)) return !(curr || other.curr);
    return !(curr->data < other || curr->data > *other);
  }

  bool operator!=(BSTIterator<Data> const &other) const {
    if (!curr || !(other.curr)) return (curr || other.curr);
    return (curr->data < *other || *other < curr->data);
  }
};

#endif  // BSTITERATOR_HPP
