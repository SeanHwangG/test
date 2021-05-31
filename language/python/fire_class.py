from concurrent.futures import ProcessPoolExecutor, ThreadPoolExecutor
import time


if __name__ == "__main__":
  N_THREADS = 3
  sum_to = 10**4
  sleep_for = 1
  io_vs_cpu(N_THREADS, sum_to, sleep_for)
