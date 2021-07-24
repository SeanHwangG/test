/** Implementation of HCTree
 *  It guarantees the best compression using redundancy of file.
 *
 *  name  : Gyuseung Hwang
 *  email : g5hwang@ucsd.edu
 */

#include "HCTree.hpp"

#include <algorithm>
#include <bitset>
#include <queue>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

#include "BitInputStream.hpp"
#include "BitOutputStream.hpp"
#include "HCNode.hpp"

using namespace std;

/** Default constructor.
 *  Initialize root, leaves and paths vector to 0,
 */
HCTree::HCTree() : root(0) {
  leaves = vector<HCNode*>(SIZE, nullptr);
  paths = vector<vector<int>>(SIZE);
}

/** Destructor.
 *  It frees root, HCNode pointer recursively.
 */
HCTree::~HCTree() { destructAll(root); }

void HCTree::destructAll(HCNode* root) {
  if (root) {
    destructAll(root->c0);
    destructAll(root->c1);
    delete root;
  }
}

/** Use the Huffman algorithm to build a Huffman coding trie.
 *  root points to the root of the trie, and leaves[i]
 *  points to the leaf node containing byte i.
 *
 *  @param freqs: vector of ints, such that freqs[i] is
 *                the frequency of occurrence of byte i in the message.
 */
void HCTree::build(const vector<int>& freqs) {
  priority_queue<HCNode*, vector<HCNode*>, HCNodePtrComp> pq;

  // put every character in priority queue that appears at least once
  for (int i = 0; i < freqs.size(); i++) {
    if (freqs[i] != 0) {
      HCNode* put = new HCNode(freqs[i], (byte)i);
      pq.push(put);
      leaves[i] = put;
      nChar++;
    }
  }

  // keep combine two least frequent Node
  while (pq.size() > 1) {
    HCNode* l = pq.top();
    pq.pop();
    HCNode* r = pq.top();
    pq.pop();
    HCNode* cur = new HCNode(l->count + r->count, l->symbol, l, r);
    l->p = r->p = cur;
    pq.push(cur);
  }

  // find path for each character
  for (int i = 0; i < SIZE; i++) {
    HCNode* cur = leaves[i];
    if (cur != nullptr) {
      // if there is one character, use 1 to decode
      if (nChar == 1) {
        paths[i] = {1};
        break;
      }
      while (cur && cur->p) {
        paths[i].push_back(cur->p->c0 == cur ? 0 : 1);
        cur = cur->p;
      }
      reverse(paths[i].begin(), paths[i].end());
    }
  }

  root = (pq.size() ? pq.top() : nullptr);
}

/** Decode BitInputStream containing serialized tree.
 *
 *  @param ret : where the deserialized tree information is stored
 *         bin : BitInputStream that contains the serialized tree
 *        path : Store path that can be used when encoding
 */
void HCTree::deserialize(HCNode*& root, BitInputStream& bin, vector<int>& path) {
  int b = bin.readBit();
  if (b == -1) {
    return;
  }

  // a leaf node
  if (b == 0) {
    byte cur = bin.readByte();
    root = new HCNode(0, cur);
    // count is not important because path is stored
    paths[cur] = path;
    nChar++;
  } else {
    root = new HCNode(0, 0);
    // calculate current path and pop after recursion
    path.push_back(0);
    deserialize(root->c0, bin, path);
    path.pop_back();
    path.push_back(1);
    deserialize(root->c1, bin, path);
    path.pop_back();
  }
}

/** Write to the given BitOutputStream
 *  the sequence of bits coding the given symbol.
 *
 *  @param symbol : symbol to encode
 *            out : BitOutputStream that will store encoded symbol
 */
void HCTree::encode(byte symbol, BitOutputStream& out) const {
  vector<int> path = paths[symbol];

  for (int i = 0; i < path.size(); i++) {
    out.writeBit(path[i]);
  }
}

/** Return symbol coded in the next sequence of bits from the stream.
 *  PRECONDITION: build() has been called, to create the coding
 *                tree, and initialize root pointer and leaves vector.
 *
 *  @param bin : BinaryInputStream that contains encoded string.
 *  @return    : decoded value
 */
int HCTree::decode(BitInputStream& bin) const {
  HCNode* cur = root;
  int nextBit;

  while ((nextBit = bin.readBit()) != -1) {
    if (nextBit == 0) {
      cur = cur->c0;
    } else if (nextBit == 1) {
      cur = cur->c1;
    }
    // reached root
    if (!cur->c0 && !cur->c1) {
      return cur->symbol;
    }
  }

  return -1;
}

/** Helper method for serialize
 *
 *  @param root : root of the tree that will be serialized
 *           ss : stringstream that the result will be stored
 */
void HCTree::serialize(HCNode* root, BitOutputStream& bout) {
  if (!root) {
    cout << "it is not valid HCTree\n"
         << "HCTree must be full tree.";
    exit(-1);
  }

  // a leaf
  if (!root->c0 && !root->c1) {
    bout.writeBit(0);
    bout.writeByte(root->symbol);
  } else {
    bout.writeBit(1);

    serialize(root->c0, bout);
    serialize(root->c1, bout);
  }
}
