/** uncompress a file with Huffman Algorithm
 *
 *  name  : Gyuseung Hwang
 *  email : g5hwang@ucsd.edu
 */
#include "HCTree.hpp"
#include "BitOutputStream.hpp"
#include "BitInputStream.hpp"
#include <fstream>
#include <iostream>

using namespace std;

/** uncompress a file that contains
 *  HC encoded string and serialized tree as header
 *
 *  @param infile : file to uncompress
 *        outfile : file contains original text
 */
void uncompress(string infile, string outfile) {
    // [1] open file and deserialize HCTree in header
    ifstream in(infile);
    BitInputStream bin(in);

    if (!in.is_open()) {
        cout << "Invalid input file. No file was opened. Please try again.\n";
        return; 
    }

    vector<int> path;
    HCTree tree;
    tree.deserialize(tree.root, bin, path);

    ofstream out(outfile);

    // [2-1] if it is a file that only contains single char
    if (tree.nChar == 1) {
        int count = 0;
        for (int i = 0; i < 32; i++) {
            count = (count << 1) + bin.readBit();
        }
        while (count--) {
            out << tree.root->symbol;
        }
        return;
    }

    // [2-2] compress letter bit by bit using deserialized HCtree 
    int decoded;

    // read and decode until it reaches EOF
    while ((decoded = tree.decode(bin)) != -1) {
        out << (byte)decoded;
    }

    out.close();
}

/** Main driver function for testing uncompress.
 *
 *  @param argc : number of argument + 1 (include run command)
 *  @param argv : pointer to char pointer that stores argument
 *  @return     : -1 if number of argument is not 2, 0 otherwise
 */
int main(int argc, char** argv) {
    // output error if user didn't Input arguments'
    if (argc != 3) {
        cout << "Invalid number of arguments.\n"
             << "Usage: ./uncompress <infile outfile>." << endl;
        exit(-1);
    }
    uncompress(argv[1], argv[2]);

    return 0;
}
