/** Huffman Tree node.
 *  Huffman Tree compresses each character based on its frequency
 *
 *  name  : Gyuseung Hwang
 *  email : g5hwang@ucsd.edu
 */

#ifndef HCNODE_HPP
#define HCNODE_HPP

#include <iostream>

typedef unsigned char byte;

using namespace std;

/** A class, instances of which are nodes in an HCTree.
 */
class HCNode {
   public:
    int count;
    byte symbol;  // byte in the file we're keeping track of
    HCNode* c0;   // pointer to '0' child
    HCNode* c1;   // pointer to '1' child
    HCNode* p;    // pointer to parent

    /** Constructor.
     *
     *  @param count : the number of occurence within the file
     *        symbol : the character
     */
    HCNode(int count, byte symbol, HCNode* c0 = 0, HCNode* c1 = 0,
           HCNode* p = 0)
        : count(count), symbol(symbol), c0(c0), c1(c1), p(p) {}

    /** Less-than comparison, so HCNodes will work in std::priority_queue
     *  We want small counts to have high priority.
     *  If same, smaller digit have high priority
     *
     *  @param other : The other HCNode to compare with.
     *  @return      : Result of comparison
     */
    bool operator<(const HCNode& other);
};

/** For printing an HCNode to an ostream
 *  Possibly useful for debugging.
 *
 *  @return : ostream containing the information of Node
 */
ostream& operator<<(ostream&, const HCNode&) __attribute__((weak));

/** For printing an HCNode to an ostream
 *  Possibly useful for debugging.
 *
 *  @param stm : ostream that store information of Node
 *           n : Node that will be printed on the stream
 *  @return    : ostream containing the information of Node
 */
ostream& operator<<(ostream& stm, const HCNode& n) {
    stm << "[" << n.count << "," << (int)(n.symbol) << "]";
    return stm;
}

#endif  // HCNODE_HPP
