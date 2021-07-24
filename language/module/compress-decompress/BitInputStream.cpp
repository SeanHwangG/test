/** BitInputStream class that can store bit information file
 *
 *  name  : Gyuseung Hwang
 *  email : g5hwang@ucsd.edu
 */

#include "BitInputStream.hpp"

/** Constructor
 *  nbits is 8 because the BitInputStream needs to be filled right away
 *
 *  @param is : input stream that the class will store
 */
BitInputStream::BitInputStream(istream& is) : is(is), buf(0), nbits(8) {}

void BitInputStream::fill() {
  buf = is.get();
  nbits = 0;
}

int BitInputStream::readBit() {
  // if there is no more bits to read
  if (nbits == 8) {
    // [1] Current byte is last
    if (is.peek() == EOF) {
      return -1;
    }
    fill();
    // [2] Next byte is last -> check marker 1 and throw garbage
    if (is.peek() == EOF) {
      int lastOne = -1;
      for (int i = 0; i < 8; i++) {
        if (buf & (1 << (7 - i))) lastOne = i;
      }

      if (lastOne == 0) return -1;

      nbits = (8 - lastOne);
      buf >>= (8 - lastOne);
    }
    // [3] Reading in the middle of the file
    else {
      nbits = 0;
    }
  }

  // check if nbits position is set
  return (bool)(buf & (1 << (7 - nbits++)));
}

int BitInputStream::readByte() {
  int ret = 0;

  for (int i = 0; i < 8; i++) {
    int b = readBit();
    if (b == -1) return -1;
    ret = (ret << 1) + b;
  }

  return ret;
}
