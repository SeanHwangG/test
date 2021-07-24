#include <cprint_list.hpp>
#include <iostream>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t lock; /* <----------------- HERE IS OUR LOCK! */

void cprint_list(const std::vector<std::string> &strings) {
  sleep(1);
  pthread_mutex_lock(&lock); /* <-------- HERE WE ACQUIRE THE LOCK */
  for (const auto &str : strings)
    std::cout << str << " ";
  std::cout << "\n";
  pthread_mutex_unlock(&lock); /* <------ HERE WE RELEASE THE LOCK */
}
