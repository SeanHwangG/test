/** BitInputStream header file that can store bit information file
 *
 *  name  : Gyuseung Hwang
 *  email : g5hwang@ucsd.edu
 */

#ifndef BITINPUTSTREAM_HPP
#define BITINPUTSTREAM_HPP

#include <fstream>
#include <iostream>

typedef unsigned char byte;

using namespace std;

/** Regular ifstream cannot store bit information. BitInputStream allows efficient bitwise encoding using byte buffer
 */
class BitInputStream {
 public:
  /** nbits is 8 because the BitInputStream needs to be filled right away
   *
   *  @param is : input stream that the class will store
   */
  BitInputStream(istream& is);

  /** Read bit from the inputstream, use buffer(unsigned char) because bit itself cannot be written as file
   *
   *  @return -1 if EOF
   */
  int readBit();

  /** Read byte from the inputstream, use buffer(unsigned char) because bit itself cannot be written as file
   *
   *  @return -1 if EOF
   */
  int readByte();

  /** There is no more bit to read, so read new byte and set nbits to 0*/
  void fill();

 private:
  char buf;
  int nbits;
  istream& is;
};

#endif
