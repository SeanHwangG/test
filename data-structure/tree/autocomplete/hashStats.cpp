#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "BloomFilter.hpp"

using namespace std;

const unsigned int DEFAULT_SIZE = 5;
const unsigned int RESIZE_FACTOR = 2;
const double MAX_LOAD_FACTOR = 0.67;

// stores number of inserted items in each slot
vector<unsigned int> table(DEFAULT_SIZE);

vector<unsigned int> inserted;

unsigned int tableLen = DEFAULT_SIZE;
unsigned int numElem = 0;

/** The hash function that we are testing for collisions */
unsigned int hashFunc(const string& item) {
    return BloomFilter::hashcodes(item)[2];
}

/** Returns the number of collisions in the hash table */
unsigned int countCollision() {
    unsigned int ret = 0;
    for (size_t i = 0; i < tableLen; i++) {
        if (table[i] > 1) {
            ret += table[i];
        }
    }

    return ret;
}

/** When load factor is high, rehash all the inserted items */
void rehash() {
    // print out the stats before each rehash
    std::cout << "#insertions: " << numElem << "; hash table size: " << tableLen
              << "; #collisions: " << countCollision() << std::endl;

    tableLen = tableLen * RESIZE_FACTOR;
    table.clear();
    table.resize(tableLen);
    // rehash all the inserted items
    for (unsigned int hashVal : inserted) {
        table[hashVal % tableLen]++;
    }
}

/** "Insert" a given item to hash table. This function does not
 *  actually insert the item, it only increases the count of number
 *  of items inserted in the hashed slot.
 */
void insert(const std::string& item) {
    // rehash if load factor is high
    if ((double)numElem / tableLen >= MAX_LOAD_FACTOR) {
        rehash();
    }
    unsigned int hashVal = hashFunc(item);
    table[hashVal % tableLen]++;
    numElem++;
    inserted.push_back(hashVal);
}

int main(int argc, const char* argv[]) {
    // reads the file line by line and insert each line to hash
    // table to output stats about the hash function
    ifstream items(argv[1]);
    string line;

    while (true) {
        getline(items, line);
        if (items.eof()) break;
        insert(line);
    }
}
