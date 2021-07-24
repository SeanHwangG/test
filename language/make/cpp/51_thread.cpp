#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <random>
#include <thread>
#include <vector>

#include "common/common.hpp"

using namespace std;
class thread_guard {
  thread &t;

 public:
  explicit thread_guard(thread &t_) : t(t_) {}
  ~thread_guard() {
    if (t.joinable()) t.join();
    cout << "\n\n";
  }
  thread_guard(thread_guard const &) = delete;
  thread_guard &operator=(thread_guard const &) = delete;
};
void RAII() {
  int local_state = 0;
  thread t([&]() {
    for (unsigned j = 0; j < 100; ++j) cout << local_state;
  });

  thread_guard g(t);
}

vector<int> res;
void func(int i) { res.push_back(i); }

void mult() {
  vector<thread> th;

  int nr_threads = 1000;
  for (int i = 0; i < nr_threads; ++i) {
    th.push_back(thread(func, i));
  }

  for (auto &t : th) {
    t.join();
  }
  cout << res;
}

void info() {
  cout << thread::hardware_concurrency() << "threads" << endl;
  cout << endl;
}

void matrix_multiplication() {
  auto sequential = [&](vector<vector<int>> A, vector<vector<int>> B, vector<vector<int>> &G, int start_row,
                        int end_row) {
    for (int i = start_row; i < end_row; i++)
      for (int j = 0; j < B[0].size(); j++) {
        G[i][j] = 0;
        for (int k = 0; k < A[0].size(); k++) G[i][j] += A[i][k] * B[k][j];
      }
  };
  auto parallel = [&](vector<vector<int>> A, vector<vector<int>> B, vector<vector<int>> &G, int start_row,
                      int end_row) {
    int num_workers = thread::hardware_concurrency();
    int chunk_size = ceil((float)A.size() / num_workers);

    thread workers[num_workers];
    for (int i = 0; i < num_workers; i++) {
      int start_row = min(i * chunk_size, (int)A.size());
      int end_row = min((i + 1) * chunk_size, (int)A.size());
      workers[i] = thread(sequential, A, B, ref(G), start_row, end_row);
    }
    for (auto &w : workers) w.join();
  };
  vector<vector<int>> A(800, vector<int>(500, 0));
  for_each(A.begin(), A.end(), [](vector<int> &v) { generate(v.begin(), v.end(), []() { return rand() % 5; }); });
  vector<vector<int>> B(500, vector<int>(300, 0));
  for_each(B.begin(), B.end(), [](vector<int> &v) { generate(v.begin(), v.end(), []() { return rand() % 5; }); });

  vector<vector<int>> G1(A.size(), vector<int>(B[0].size(), 0)), G2(A.size(), vector<int>(B[0].size(), 0));

  std::chrono::duration<double> sequential_time(0), parallel_time(0);
  auto startTime = std::chrono::high_resolution_clock::now();

  cout << "Starting Sequential" << endl;
  for (int eval = 0; eval < 10; eval++) {
    startTime = std::chrono::high_resolution_clock::now();
    sequential(A, B, G1, 0, G1.size());
    sequential_time += (std::chrono::high_resolution_clock::now() - startTime) / 10.0;
  }

  cout << "Starting Parallel" << endl;
  for (int eval = 0; eval < 10; eval++) {
    startTime = chrono::high_resolution_clock::now();
    parallel(A, B, G2, 0, G2.size());
    parallel_time += (chrono::high_resolution_clock::now() - startTime) / 10.0;
  }
  printf("Average Sequential Time: %.2f ms\n", sequential_time.count() * 1000);
  printf("Average Parallel Time: %.2f ms\n", parallel_time.count() * 1000);
  printf("Speedup: %.2f\n", sequential_time / parallel_time);
  printf("Efficiency %.2f%%\n", 100 * (sequential_time / parallel_time) / std::thread::hardware_concurrency());
}

void merge(int *array, int l, int m, int r) {
  int n_left = m - l + 1, n_right = r - m;
  int lefts[n_left], rights[n_right];

  copy(&array[l], &array[m + 1], lefts);
  copy(&array[m + 1], &array[r + 1], rights);

  int left_i = 0, right_i = 0, insert_i = l;

  while ((left_i < n_left) || (right_i < n_right)) {
    if (left_i < n_left && (right_i >= n_right || lefts[left_i] <= rights[right_i])) {
      array[insert_i] = lefts[left_i];
      left_i++;
    } else {
      array[insert_i] = rights[right_i];
      right_i++;
    }
    insert_i++;
  }
}
void sequential_merge_sort(int *array, int l, int r) {
  if (l < r) {
    int m = (l + r) / 2;
    sequential_merge_sort(array, l, m);
    sequential_merge_sort(array, m + 1, r);
    merge(array, l, m, r);
  }
}

void parallel_merge_sort(int *array, int l, int r, int depth = 0) {
  if (depth >= log(thread::hardware_concurrency()))
    sequential_merge_sort(array, l, r);
  else {
    int m = (l + r) / 2;
    thread left_thread = thread(parallel_merge_sort, array, l, m, depth + 1);
    parallel_merge_sort(array, m + 1, r, depth + 1);
    left_thread.join();
    merge(array, l, m, r);
  }
}

void merge_sort() {
  const int N = 10000;
  int original_array[N], sequential_result[N], parallel_result[N];
  for (int i = 0; i < N; i++) original_array[i] = rand();

  printf("Evaluating Sequential Implementation...\n");
  chrono::duration<double> sequential_time(0);
  for (int eval = 0; eval < 10; eval++) {
    copy(&original_array[0], &original_array[N - 1], sequential_result);
    auto start_time = chrono::high_resolution_clock::now();
    sequential_merge_sort(sequential_result, 0, N - 1);
    sequential_time += (chrono::high_resolution_clock::now() - start_time) / 10.0;
  }

  printf("Evaluating Parallel Implementation...\n");
  chrono::duration<double> parallel_time(0);
  for (int eval = 0; eval < 10; eval++) {
    copy(&original_array[0], &original_array[N - 1], parallel_result);
    auto start_time = chrono::high_resolution_clock::now();
    parallel_merge_sort(parallel_result, 0, N - 1);
    parallel_time += (chrono::high_resolution_clock::now() - start_time) / 10.0;
  }

  printf("Average Sequential Time: %.2f ms\n", sequential_time.count() * 1000);
  printf("Average Parallel Time: %.2f ms\n", parallel_time.count() * 1000);
  printf("Speedup: %.2f\n", sequential_time / parallel_time);
  printf("Efficiency %.2f%%\n", 100 * (sequential_time / parallel_time) / thread::hardware_concurrency());
}

int main() {
  // info();
  // RAII();
  mult();
  // matrix_multiplication();
  // merge_sort();
}