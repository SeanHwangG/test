/** Header of bloom filter that uses three different hash function
 *
 *  Name  : Gyuseung Hwang
 *  Email : g5hwang@ucsd.edu
 */

#ifndef BLOOM_FILTER_HPP
#define BLOOM_FILTER_HPP

#include <string>
#include <vector>

using namespace std;

/** The class for bloom filter that provides memory efficient check
 *  of whether an item has been inserted before. Small amount of
 *  false positives is possible but there will be no false negatives.
 */
class BloomFilter {
 public:
  BloomFilter(size_t numBytes);
  void insert(std::string item);
  bool find(std::string item);

  /** return three hashcodes of given key
   */
  static vector<unsigned int> hashcodes(const string& key);
  ~BloomFilter();

  // the number of slots (character of one byte)
  unsigned int numSlots;

 private:
  const unsigned int CH_SIZE = 8;
  // The char array as the hash table
  unsigned char* table;
};
#endif  // BLOOM_FILTER
