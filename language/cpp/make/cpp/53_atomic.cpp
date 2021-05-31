#include <atomic>
#include <iostream>
#include <thread>

using namespace std;

void count_n_million() {
  atomic<float> n = atomic<float>(1.0);
  n = n + 1;
}
int main() { count_n_million(); }