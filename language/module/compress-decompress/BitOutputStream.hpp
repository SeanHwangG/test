/** Header file of BitOutputStream
 *
 *  name  : Gyuseung Hwang
 *  email : g5hwang@ucsd.edu
 */
#ifndef BITOUTPUTSTREAM_HPP
#define BITOUTPUTSTREAM_HPP

#include <fstream>
#include <iostream>

typedef unsigned char byte;

using namespace std;

/** BitOutputStream class that can store bit effeciently as string
 */
class BitOutputStream {
   public:
    /** Constructor.
     *  @param os : ostream that will be used after buffer is filled
     */
    BitOutputStream(ostream& os);

    /** There is no more place to write in current buffer.
     *  put current buffer to ostream;
     */
    void flush();

    /** Store bit information to byte
     *
     *  @param i : 0 or 1
     */
    void writeBit(int i);

    /** Write current byte to stream.
     *
     *  @param b : character ranges from 0 ~ 255
     */
    void writeByte(byte b);

   private:
    char buf;
    int nbit;
    ostream& os;
};

#endif