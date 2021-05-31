/** compress a file with Huffman Algorithm
 *  output will be overriden in a given file.
 *
 *  name  : Gyuseung Hwang
 *  email : g5hwang@ucsd.edu
 */

#include "HCTree.hpp"
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

/** compress a file that contains serialized HCTree as a header
 * 
 *  @param infile : file to compress
 *        outfile : file contains compressed information
 */
void compress(string infile, string outfile) {
    // [1] Open infile and calculate frequency
    ifstream in(infile, ios::binary);

    if (!in.is_open()) {
        cout << "Invalid input file. No file was opened. Please try again.\n";
        return; 
    }

    vector<int> freqs(HCTree::SIZE, 0);
    int nextByte;
    int count = 0;

    while ((nextByte = in.get()) != EOF) {
        freqs[nextByte]++;
        count++;
    }

    // [2] Build Tree with Frequncy infomration
    HCTree tree;
    tree.build(freqs);
    ofstream out(outfile, ofstream::out | ofstream::trunc);

    // [3-1] don't need frequency table if empty
    if (tree.nChar == 0) {
        out.close();
        return;
    }

    // [3-2] store frequency table 
    BitOutputStream bout(out);
    tree.serialize(tree.root, bout);

    // [4-1] if there is only one char, store frequency
    if (tree.nChar == 1) {
        for (int i = 31; i > -1; i--) {
            bout.writeBit((bool)(count & (1 << i)));
        }
        bout.writeBit(1);
        bout.flush();
        return;
    }

    // [4-2] read file again and decode

    // go back to the beginning of the file
    in.clear();
    in.seekg(0, ios::beg); 

    // decode BitOuputStream
    while ((nextByte = in.get()) != EOF) {
        tree.encode((byte)nextByte, bout);
    }

    // mark end so that we wrtie all garbage values
    bout.writeBit(1);
    bout.flush();

    out.close();
}

/** Main driver function for testing compress.
 *
 *  @param argc : number of argument + 1 (include run command)
 *  @param argv : pointer to char pointer that stores argument
 *  @return     : -1 if number of argument is not 2, 0 otherwise
 */
int main(int argc, char** argv) {
    // output error if user didn't Input arguments'
    if (argc != 3) {
        cout << "Invalid number of arguments.\n"
             << "Usage: ./compress <infile outfile>." << endl;
        exit(-1);
    }

    compress(argv[1], argv[2]);

    return 0;
}
