/** Multi way tree implementation of Node for Dictionary Trie.
 *  The search only requires O(string_size).
 *
 *  Name  : Gyuseung Hwang
 *  Email : g5hwang@ucsd.edu
 */
#ifndef NODE_HPP
#define NODE_HPP
#include <string>
#include <unordered_map>

using namespace std;

/** The class contains parent pointer so that it can regenerate the string.
 *  Also, parent stores the maximum frequiency of child to optimize.
 */
class Node {
   public:
    // current character
    char ch;
    // frequency of current Node, 0 if the word is empty
    unsigned int freq;
    // maximum frequency of all children
    unsigned int max_child;
    Node* parent;
    unordered_map<char, Node*> child;

    /** Default constructor; set everything to 0
     *  This is only used for the root Node.
     */
    Node() : ch('*'), freq(0), max_child(0), parent(nullptr){};

    /** constructor that specifies current character
     *  set other to 0
     *
     *  @param ch : current character
     */
    Node(char ch) : ch(ch), freq(0), max_child(0), parent(nullptr){};

    /** regenerate the original string by traversing parent
     *
     *  @param cur : Node pointer that we want to regnerate words from
     */
    static string original(Node* cur) {
        string ret;

        // keep traverse to parent until it reaches root
        while (cur != nullptr) {
            // current node is root
            if (cur->ch == '*') {
                break;
            }
            // better performance than inserting in front of the string
            ret += cur->ch;
            cur = cur->parent;
        }

        // word is currently reversed.
        return string(ret.rbegin(), ret.rend());
    }
};

#endif