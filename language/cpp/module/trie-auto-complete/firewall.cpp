/** Test file for Bloomfilter.
 *
 *  Name  : Gyuseung Hwang
 *  Email : g5hwang@ucsd.edu
 */
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <unordered_set>
#include "BloomFilter.hpp"

using namespace std;

/** Given three file names, test whether the BloomFilter works correctly.
 *  It prints false positive rates and the compressed ratio.
 *  The lists of good urls from mixed will be overwritten in out_filename.
 *  NOTE: These files should be in the same directory
 *
 *  @param bad_filename : file name of the bad url
 *  @param mix_filename : file name of the mixed url
 *  @param out_filename : file name where the output of the program will be
 */
void testFiles(string bad_filename, string mix_filename, string out_filename) {
    // count the number of lines from bad url files
    ifstream bad(bad_filename), mix(mix_filename); 
    ofstream out(out_filename, std::ofstream::out | std::ofstream::trunc);

    // count number of lines from bad, mix, and out(will be calculated)
    bad.unsetf(ios_base::skipws);
    mix.unsetf(ios_base::skipws);

    int num_bad =
        count(istream_iterator<char>(bad), istream_iterator<char>(), '\n');
    int num_mix = 
        count(istream_iterator<char>(mix), istream_iterator<char>(), '\n');
    int num_safe = num_mix - num_bad;
    int num_out = 0;

    // go back to beginning of the file after iterating
    bad.clear();
    bad.seekg(0, ios::beg);
    mix.clear();
    mix.seekg(0, ios::beg);

    // size of the bad, out, and bloom filter
    int size_bad = 0;
    int size_out = 0;
    int size_bloom = num_bad * 3 / 2;

    // initialize bloom Filter
    BloomFilter bf(size_bloom);

    string url;
    while (getline(bad, url)) {
        bf.insert(url);
        // size of file is the number of character (+1 is for newline)
        size_bad += (url.size() + 1);
    }
    bad.close();


    while (getline(mix, url)) {
        num_mix++;
        if (!bf.find(url)) {
            out << url << "\n";
            // size of file is the number of character (+1 is for newline)
            size_out += (url.size() + 1);
            num_out++;
        }
    }
    mix.close();
    out.close();
    
    cout << "False positive rate:" << (num_safe - num_out) / (double)num_safe;
    cout << "\nSaved memory ratio:" << size_bad / (double)size_bloom << endl;
}

/** main driver function for firewall
 *
 *  arg1 - list of malicious urls/bad words filter out
 *  arg2 - list of mixed (good/bad) to only write good urls to
 *  arg3 - file to write only the good urls to (one on each line)
 */
int main(int argc, char** argv) {
    // exit when user doesn't enter 3 arguments
    if (argc != 4) {
        cout << "This program requires 3 arguments!" << endl;
        exit(-1);
    }
    testFiles(argv[1], argv[2], argv[3]);
}
