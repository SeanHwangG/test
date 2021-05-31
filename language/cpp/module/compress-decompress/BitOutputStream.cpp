/** BitOutputStream class that can output bits
 *
 *  name  : Gyuseung Hwang
 *  email : g5hwang@ucsd.edu
 */
#include "BitOutputStream.hpp"
#include <fstream>
#include <iostream>

using namespace std;

const int MAX_BYTE = 8;

/** Constructor.
 *  @param os : ostream that will be used after buffer is filled
 */
BitOutputStream::BitOutputStream(ostream& os) : os(os), buf(0), nbit(0) {}

/** There is no more place to write in current buffer.
 *  put current buffer to ostream;
 */
void BitOutputStream::flush() {
    os.put(buf);
    os.flush();
    buf = nbit = 0;
}

/** Store bit information to byte
 *
 *  @param i : 0 or 1
 */
void BitOutputStream::writeBit(int i) {
    if (nbit == MAX_BYTE) {
        flush();
        nbit = 0;
    }

    if (i == 1) buf |= (1 << (MAX_BYTE - 1 - nbit));

    nbit++;
}

/** Write current byte to stream.
 *
 *  @param b : character ranges from 0 ~ 255
 */
void BitOutputStream::writeByte(byte b) {
    for (int i = MAX_BYTE - 1; i > -1; i--) {
        writeBit((bool)(b & (1 << i)));
    }
}