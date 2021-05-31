#include <algorithm>
#include <iostream>
#include <vector>

#include "common/common.hpp"
using namespace std;

void matrix_multiply() {
  vector<int> foo;
  vector<int> bar;

  for (int i = 1; i < 6; i++) foo.push_back(i * 10);
  cout << "foo \t" << foo << endl;

  std::transform(foo.begin(), foo.end(), back_inserter(bar), [](int &n) { return ++n; });
  cout << "bar \t" << foo << endl;
  transform(foo.begin(), foo.end(), bar.begin(), foo.begin(), std::plus<int>());
  cout << "foobar \t" << foo << "\n\n";

  vector<vector<int>> in_v{{1, 2, 3, 4}, {5, 6, 7, 8}};
  vector<vector<int>> out_v;
  transform(in_v.begin(), in_v.end(), back_inserter(out_v), [](const vector<int> &v) {
    return transform(v.begin(), v.end(), v.begin(), [](const int &n) { return n * 2; });
  });
  cout << out_v << "\n\n";
}

void generate_even_odd() {
  vector<int> nums(10, 0);
  generate(nums.begin(), nums.end(), []() { return rand() % 100; });

  vector<int> evens, odds;
  copy_if(nums.begin(), nums.end(), back_inserter(evens), [](int &value) { return value % 2 == 0; });
  copy_if(nums.begin(), nums.end(), back_inserter(odds), [](int &value) { return value % 2 != 0; });
  cout << "Evens \t" << evens << endl;
  cout << "Odds \t" << odds << endl;
}

int main() {
  matrix_multiply();
  generate_even_odd();

  return 0;
}