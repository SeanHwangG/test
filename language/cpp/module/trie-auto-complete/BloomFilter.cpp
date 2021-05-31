#include "BloomFilter.hpp"

/** Convert a string into three different hased value.
 *
 *  @param key : the string we ant to convert
 *  @return    : the vector of three unsigned int hash values
 */
vector<unsigned int> BloomFilter::hashcodes(const string& key) {
  /** 1st Hash Function
   *  Hash a string using an algorithm taken from Aho, Sethi, and Ullman,
   *  Compilers: Principles, Techniques, and Tools,&quot; Addison-Wesley,
   *  1985, p. 436. PJW stands for Peter J. Weinberger, who apparently
   *  originally suggested the function.
   */
  unsigned int PJW_HASH_SHIFT = 4;
  unsigned int PJW_HASH_RIGHT_SHIFT = 24;
  unsigned int PJW_HASH_MASK = 0xf0000000;
  unsigned int hash1 = 0;
  for (char ch : key) {
    hash1 = (hash1 << PJW_HASH_SHIFT) + (unsigned)ch;
    unsigned int rotate_bits = hash1 & PJW_HASH_MASK;
    hash1 ^= rotate_bits | (rotate_bits >> PJW_HASH_RIGHT_SHIFT);
  }

  /** 2nd Hash Function
   *  Hash a string using the method given in Bruno Preiss, &quot;Data
   *  Structures and Algorithms with Object-Oriented Design Patterns in
   *  C++;, Wiley, 1999, p. 213.
   */
  static const unsigned int PREISS_HASH_SHIFT = 6;
  static const unsigned int PREISS_HASH_MASK = ~0U << (key.size() - PREISS_HASH_SHIFT);

  unsigned int hash2 = 0;
  for (char ch : key) {
    hash2 = (hash2 & PREISS_HASH_MASK) ^ (hash2 << PREISS_HASH_SHIFT) ^ (unsigned)ch;
  }

  /** 3rd Hash Function
   *  Hash a string using the modified CRC method. The basic idea of
   *  this function is that the hash value is rotated left by 5 bits and
   *  then the next character is exclusive hashed in to the hash value.
   *  The implementation is complicated by the lack of a rotate operation
   *  in C++.
   */
  unsigned int CRC_HASH_SHIFT = 5;
  unsigned int hash3 = 0;
  for (char ch : key) {
    unsigned int leftShiftedValue = hash3 << CRC_HASH_SHIFT;
    unsigned int rightShiftedValue = hash3 >> (key.size() - CRC_HASH_SHIFT);
    hash3 = (leftShiftedValue | rightShiftedValue) ^ (unsigned)ch;
  }

  return {hash1, hash2, hash3};
}

/** The hashfunction works better when the hash size is prime number.
 *  So, try to pick the largest prime number(plus 1) as a good Table size.
 *
 *  @param num : the size that we want to check if it is prime or 1
 *  @return    : true if the num is prime or one, false otherwise
 */
bool goodTableSize(int num) {
  // base case
  if (num <= 3) return true;

  // check if there is divisor other than 1 and the number itself
  if (num % 2 == 0) return false;
  for (int n = 3; n * n <= num; n += 2)
    if (num % n == 0) return false;
  return true;
}

/** Constructor; Create a new bloom filter with the size in bytes
 *
 *  @param numBytes : the maximum numBytes allowed
 */
BloomFilter::BloomFilter(size_t numBytes) {
  // decrease tableSize until it becomes a prime or 1
  while (!goodTableSize(numBytes)) numBytes--;

  numSlots = numBytes;
  table = new unsigned char[numBytes];
}

void BloomFilter::insert(string item) {
  for (unsigned int hash : hashcodes(item)) {
    hash %= (numSlots * CH_SIZE);
    // set (1 << (hash % CH_SIZE))th bit in a (hash / CH_SIZE)th bucket
    // because one bucket can contains CH_SIZE of bits
    table[hash / CH_SIZE] |= (1 << (hash % CH_SIZE));
  }
}

bool BloomFilter::find(string item) {
  unsigned int count = 0;

  for (unsigned int hash : hashcodes(item)) {
    hash %= (numSlots * CH_SIZE);
    // check if (1 << (hash % CH_SIZE))th bit in a (hash / CH_SIZE)th bucket is marked
    if (table[hash / CH_SIZE] & (1 << (hash % CH_SIZE))) {
      count++;
    }
  }

  // if any of three bit is not set, the item was not inserted
  return count == 3;
}

/* Destrctor for the bloom filter */
BloomFilter::~BloomFilter() { delete[] table; }