#include <array>
#include <iostream>

#include "common/common.hpp"

using namespace std;

void copy_() {
  array<int, 3> a = {1, 2, 3};

  for (int i : a) cout << i;
  cout << endl;
  array<int, 3> b = a;

  b = a;
  a[0] = 0;

  cout << b.front() << endl;

  try {
    b.at(3) = 666;
  } catch (out_of_range const &exc) {
    cout << "Exception: " << exc.what() << '\n';
  }
}

int main() { copy_(); }