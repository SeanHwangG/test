#include "DictionaryTrie.hpp"

#include <algorithm>
#include <iostream>
#include <stack>

using namespace std;

auto maxcomp = [](Node* a, Node* b) {
  if (a->freq == b->freq) return Node::original(a) > Node::original(b);
  return a->freq < b->freq;
};

auto mincomp = [](Node* a, Node* b) {
  if (a->freq == b->freq) return Node::original(a) < Node::original(b);

  return a->freq > b->freq;
};

void DictionaryTrie::destructAll(Node* cur) {
  for (auto it : cur->child) destructAll(it.second);
  delete cur;
}

/** Default constructore creating an empty root.
 */
DictionaryTrie::DictionaryTrie() { root = new Node(); }

bool DictionaryTrie::insert(string word, unsigned int freq) {
  // return false when the given word is empty
  if (word == "") return false;

  Node* cur = root;

  // iterate word and go down the tree
  for (char ch : word) {
    // create a new node if the node doesn't have child
    if (cur->child.count(ch) == 0) {
      cur->child[ch] = new Node(ch);
      cur->child[ch]->parent = cur;
    }

    cur = cur->child[ch];
  }

  // the same word has been inserted
  if (cur->freq != 0) return false;
  cur->freq = freq;

  // go up the tree and update parents maximum frequency
  while (cur != nullptr) {
    cur->max_child = max(cur->max_child, freq);
    cur = cur->parent;
  }

  return true;
}

bool DictionaryTrie::find(string word) const {
  Node* cur = root;

  // itreate each character of the string and go down the tree
  for (char ch : word) {
    // if the node doesn't have that character, return false
    if (cur->child.count(ch) == 0)
      return false;
    else
      cur = (cur->child)[ch];
  }

  // if the frequency is 0, return false
  return cur->freq != 0;
}

vector<string> DictionaryTrie::predictCompletions(string prefix, unsigned int most) {
  if (most <= 0) return {};

  Node* cur = root;

  // iterate the character of the string and go doewn the tree
  for (char ch : prefix) {
    // return empty vector if the word isn't in trie
    if (cur->child.count(ch) == 0) return {};
    cur = (cur->child)[ch];
  }

  // perform depth frist search in a trie from node mathching prefix
  stack<Node*> dfs;
  dfs.push(cur);

  // min heap that keep track of most frequent element with given prefix
  priority_queue<Node*, vector<Node*>, decltype(mincomp)> poss(mincomp);

  // iterative way of DFS
  while (dfs.size()) {
    Node* cur = dfs.top();

    if (cur->freq != 0) {
      // push if the priority queue is not filled up
      if (poss.size() < most) {
        poss.push(cur);
      } else {
        // only push if frequency is not smaller than current minimum
        if (poss.top()->freq <= cur->freq) {
          poss.push(cur);
          poss.pop();
        }
      }
    }

    dfs.pop();
    for (auto it : cur->child) {
      // push child of current node
      // when the priority queue is not filled up
      // or the maximum child is greater than the current top of pq
      if (poss.size() < most || poss.top()->freq <= it.second->max_child) {
        dfs.push(it.second);
      }
    }
  }

  vector<string> ret;
  // get original string of nodes in priority queue
  while (poss.size() && most--) {
    ret.push_back(Node::original(poss.top()));
    poss.pop();
  }

  // priority queue was min heap, so reverse it
  return vector<string>(ret.rbegin(), ret.rend());
}

vector<string> DictionaryTrie::predictUnderscore(string pattern, unsigned int most) {
  if (most == 0) return {};
  Node* cur = root;
  unsigned int index = 0;

  // First : Before the underscore, search word with given prefix
  while (pattern[index] != '_') {
    // return empty vector if the word isn't in trie
    if (cur->child.count(pattern[index]) == 0) return {};

    cur = (cur->child)[pattern[index]];
    index++;
  }

  // Second : Add all child of current prefix
  queue<Node*> q;

  for (auto it : cur->child) {
    q.push(it.second);
  }

  // Third : Loop through the children of prefix
  while (++index < pattern.size()) {
    for (int i = q.size(); i != 0; i--) {
      // only go down the tree if the Node has certain character
      if (q.front()->child.count(pattern[index]) != 0) {
        q.push(q.front()->child[pattern[index]]);
      }
      q.pop();
    }
  }

  priority_queue<Node*, vector<Node*>, decltype(maxcomp)> poss(maxcomp);

  // Foruth : push in priority queue only if it is the word
  while (q.size()) {
    if (q.front()->freq != 0) {
      poss.push(q.front());
    }
    q.pop();
  }

  vector<string> ret;

  // get original string of nodes in priority queue
  while (poss.size() && most--) {
    ret.push_back(Node::original(poss.top()));
    poss.pop();
  }

  return ret;
}

DictionaryTrie::~DictionaryTrie() { destructAll(root); }
