#include <iostream>
#include <vector>

#include "common/common.hpp"

using namespace std;

void new_delete_() {
  int *p = new int;
  *p = 10;

  cout << *p << "\n\n";

  delete p;  // only Heap memory

  int size = 3;
  int *nums = new int[size]{1, 2, 3};
  for (int i = 0; i < size; i++) cout << nums[i] << " ";

  delete[] nums;

  cout << "\n\n";
}

void try_catch_() {
  try {
    throw 'a';
  } catch (int param) {
    cout << "int exception\n";
  } catch (...) {
    cout << "default exception\n";
  }
}

int main() {
  new_delete_();
  try_catch_();
}