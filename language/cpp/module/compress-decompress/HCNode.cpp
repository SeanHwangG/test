/** Implementaion of Huffman Tree node.
 *  Huffman Tree compresses each character based on its frequency
 *
 *  name  : Gyuseung Hwang
 *  email : g5hwang@ucsd.edu
 */

#include "HCNode.hpp"

bool HCNode::operator<(const HCNode& other) {
  if (this->count != other.count) {
    return this->count > other.count;
  }
  // counts are equal. use symbol value to break tie.
  return this->symbol > other.symbol;
}