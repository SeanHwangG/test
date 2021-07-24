/** Header file of HCTree
 *  It guarantees the best compression using redundancy of text.
 *
 *  name  : Gyuseung Hwang
 *  email : g5hwang@ucsd.edu
 */
#ifndef HCTREE_HPP
#define HCTREE_HPP

#include <fstream>
#include <queue>
#include <vector>

#include "BitInputStream.hpp"
#include "BitOutputStream.hpp"
#include "HCNode.hpp"

using namespace std;

/** A 'function class' for use as the Compare class in a
 *  priority_queue<HCNode*>. It compares element that points to
 */
class HCNodePtrComp {
 public:
  bool operator()(HCNode*& lhs, HCNode*& rhs) const { return *lhs < *rhs; }
};

/** If there is one leaf in tree, use 1.
 *  More frequent element pops out
 *  If same, higher symbol pops out first.
 */
class HCTree {
 private:
  vector<HCNode*> leaves;

 public:
  HCNode* root;
  vector<vector<int>> paths;  // paths for each leaves; only contains 0 1
  int nChar = 0;
  static const int SIZE = 256;

  /** Default constructor.
   *  Initialize root, leaves and paths vector to 0,
   */
  HCTree();

  /** Destructor.
   *  It frees root, HCNode pointer recursively.
   */
  ~HCTree();

  /** Helper function for destructor of HCTree. It recursively free all children of root.
   *
   *  @param root : root of the tree that will be destruct
   */
  void destructAll(HCNode* root);

  /** Use the Huffman algorithm to build a Huffman coding trie.
   *  root points to the root of the trie, and leaves[i] points to the leaf node containing byte i.
   *
   *  @param freqs: vector of ints, such that freqs[i] is the frequency of occurrence of byte i in the message.
   */
  void build(const vector<int>& freqs);

  /** Write to the given BitOutputStream the sequence of bits coding the given symbol.
   *
   *  @param symbol : symbol to encode
   *            out : BitOutputStream that will store encoded symbol
   */
  void encode(byte symbol, BitOutputStream& out) const;

  /** Return symbol coded in the next sequence of bits from the stream.
   *  PRECONDITION: build() has been called, to create the coding
   *  tree, and initialize root pointer and leaves vector.
   *
   *  @param bin : BinaryInputStream that contains encoded string.
   *  @return    : decoded value
   */
  int decode(BitInputStream& bin) const;

  /** Encode a tree and store in BitOutputStream.
   *
   * @param root : root of the tree that will be encoded
   *        bout : BitOutputStream that will store the encoded tree
   */
  void serialize(HCNode* root, BitOutputStream& bout);

  /** Decode BitInputStream containing serialized tree.
   *
   *  @param ret : where the deserialized tree information is stored
   *         bin : BitInputStream that contains the serialized tree
   *        path : Store path that can be used when encoding
   */
  void deserialize(HCNode*& ret, BitInputStream& bin, vector<int>& path);
};

#endif  // HCTREE_H
