/** Interactive test file for DictionaryTrie
 *
 *  Name  : Gyuseung Hwang
 *  Email : g5hwang@ucsd.edu
 */
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "DictionaryTrie.hpp"
#include "util.hpp"

using namespace std;

/** Create dictionaryTrie from file and allow user to search data from it.
 *
 *  @param dict_filename : dictionary file that we want to test
 */
void testFile(string dict_filename) {
  ifstream in;
  in.open(dict_filename, ios::binary);

  cout << "Reading file: " << dict_filename << endl;
  DictionaryTrie* dict_trie = new DictionaryTrie();

  // create dictionary from ifstream
  Utils::load_dict(*dict_trie, in);

  string pattern;
  int most;
  char again = 'y';

  // loop this process until user press key other than 'y'
  do {
    cout << "Enter a prefix/pattern to search for:" << endl;
    cin >> pattern;
    cout << "Enter a number of completions:" << endl;
    cin >> most;

    // if query string contains _, use predictCompletions
    if (pattern.find('_') == string::npos) {
      for (string str : dict_trie->predictCompletions(pattern, most)) {
        cout << str << "\n";
      }
    }
    // if query string doesn't contain _, use predictUnderscore
    else {
      for (string str : dict_trie->predictUnderscore(pattern, most)) {
        cout << str << "\n";
      }
    }

    cout << "Continue? (y/n)" << endl;
    cin >> again;
  } while (again == 'y');

  delete dict_trie;
}

/**
 * The main function counts the number of argument and test file
 * only when the number of argumnet is equal to 1.
 *
 * @param argc - the number of argument + 1 (include executable name)
 * @param argv - pointer to string that contains input of the main
 */
int main(int argc, char** argv) {
  // user should only input one dictionary file
  if (argc != 2) {
    cout << "This program requires 1 argument!" << endl;
    exit(-1);
  }
  testFile(argv[1]);
}
