/** CSE 100 PA2 C++ Autocomplete
 *  Name  : Jor-el Briones, Christine Alvarado, Gyuseung Hwang
 *  Email : g5hwang@ucsd.edu
 */
#ifndef DICTIONARY_TRIE_HPP
#define DICTIONARY_TRIE_HPP

#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>

#include "Node.cpp"

using namespace std;
/** The class for a dictionary ADT, implemented as a trie
 *  You may implement this class as either a mulit-way trie or a ternary search trie, but you must use one or the other.
 */
class DictionaryTrie {
 public:
  /* Create a new Dictionary that uses a Trie back end */
  DictionaryTrie();

  /** Insert a word with its frequency into the dictionary.
   *  It doesn't insert when the string is empty or already in dictionary.
   *
   *  @param word : the string to insert in the trie
   *  @param freq : the frequency of the input string
   *  @return     : true if the word was inserted, and false otherwise
   */
  bool insert(std::string word, unsigned int freq);

  /** Find a word in a dictionary trie
   *
   *  @param word : the word to search in the dictionary trie
   *  @return     : true if the word is in the dictionary, false otherwise
   */
  bool find(std::string word) const;

  /** Return up to 'most' frequent words with gviven prefix.
   *  These completions are listend from most frequent to least, and when there is a tie, it prints alphabetically.
   *
   *  @param prefix : the prefix that we want to search in the tree
   *  @param most   : the maximum number of element we want to search
   *  @return       : top 'most' frequent string with given prefix in a vector
   */
  vector<std::string> predictCompletions(std::string prefix, unsigned int num_completions);

  /** Return up to 'most' frequent with given pattern.
   *  These completions are listend from most frequent to least, and when there is a tie, it prints alphabetically.
   *
   *  @param pattern : pattern we want to search in the trie
   *  @param most    : number of maximum element that we want to search
   *  @return        : vector of top most elements with given pattern
   */
  vector<std::string> predictUnderscore(string pattern, unsigned int num_completions);
  ~DictionaryTrie();

  Node* root;

 private:
  void destructAll(Node* cur);
};

#endif  // DICTIONARY_TRIE_H
