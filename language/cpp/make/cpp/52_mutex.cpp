#include <iostream>
#include <mutex>
#include <queue>
#include <thread>
using namespace std;

void count_n_million(bool with_lock) {
  mutex count_lock;
  once_flag flag;
  int counts = 0;
  thread threads[3];

  for (int i = 0; i < 3; i++) {
    threads[i] = thread([&]() {
      call_once(flag, []() { cout << "Starting count \n"; });
      if (with_lock) count_lock.lock();
      for (int i = 0; i < 1000000; i++) counts += 1;

      if (with_lock) count_lock.unlock();
    });
  }
  for (int i = 0; i < 3; i++) threads[i].join();

  cout << "total counts \t" << counts << "\n\n";
}

void count_sec() {
  mutex cout_lock;
  bool running = true;

  auto yell = [&](const char *name) {
    unsigned int count = 0;
    cout_lock.lock();
    cout << "yell thread \t" << this_thread::get_id() << "\n";
    cout_lock.unlock();
    while (running) {
      count++;
    }
    cout_lock.lock();
    cout << "Total Counting \t" << count << "\n";
    cout_lock.unlock();
  };

  auto counter = [&]() {
    cout_lock.lock();
    cout << "counter thread \t" << this_thread::get_id() << "\n";
    cout_lock.unlock();
    this_thread::sleep_for(chrono::seconds(1));
    running = false;
  };
  thread watch(counter);
  thread person(yell, "sean");
  watch.detach();
  person.join();
  cout << endl;
}

int main() {
  count_n_million(false);
  count_n_million(true);
  count_sec();

  return 0;
}