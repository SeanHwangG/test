import sys
import math
import random
import functools
import multiprocessing as mp
import time
import fire


a = 0


def pprint(st): return print(st.expandtabs(32))


def mp_sleep(sec):
  time.sleep(sec)
  return f"{sec} {mp.current_process().name}"

# 1


def sleeps():
  global mp_sleep

  start = time.perf_counter()

  time.sleep(0.5)
  time.sleep(0.5)

  pprint(f'W/o multiprocess \t {time.perf_counter() - start:.2f}s')   # 2

  start = time.perf_counter()

  p1 = mp.Process(target=time.sleep, args=[0.5])
  p2 = mp.Process(target=time.sleep, args=[0.5])

  p1.start()
  p2.start()

  pprint(f'Before join \t {time.perf_counter() - start:.2f}s')  # 1

  p1.join()
  p2.join()

  pprint(f'With multiprocess \t {time.perf_counter() - start:.2f}s')  # 1

  start = time.perf_counter()

  with mp.Pool() as pool:
    results = pool.map(mp_sleep, [0.5, 0.5, 1.0, 1.0])

  pprint(f'Multiple sleeps \t {time.perf_counter() - start:.2f}s \n {results} ')  # 1


# 2
def class_():
  class MyProcess(mp.Process):
    def __init__(self, name):
      self.name = name

    def run(self):
      pprint(f'Before execution \t {self} {p.is_alive()}')
      p.start()
      pprint(f'Running \t {p} {p.is_alive()}')
      p.terminate()
      pprint(f'Terminated \t {p} {p.is_alive()}')
      p.join()
      pprint(f'Joined \t {p} {p.is_alive()} {p.exitcode}')    # 0 : NOERROR | >0 error with exitcode | <0 kill with existcode

  for n in ["Tom", "Sam"]:
    p = MyProcess(n)
    p.start()
    p.join()


# 3
def mp_add(n):
  global a
  a += n
  return a


def inc(x):
  return x + 1


def dec(x):
  return x - 1


def add(x, y):
  return x + y


def map_(f): return f()


def functions_():
  f_inc = functools.partial(inc, 4)
  f_dec = functools.partial(dec, 2)
  f_add = functools.partial(add, 3, 4)

  with mp.Pool() as pool:
    res = pool.map(map_, [f_inc, f_dec, f_add])

  print(res)


# 3
def adds():
  global a
  pprint(f'Before add \t {a} ')
  with mp.Pool(10) as pool:
    result = pool.map(mp_add, [1] * 100)
  print(result)
  pprint(f'After add \t {a} ')


# 4
def merge(*args):
  left, right = args
  l, r = 0, 0
  merged = []
  while l < len(left) and r < len(right):
    if left[l] <= right[r]:
      merged.append(left[l])
      l += 1
    else:
      merged.append(right[r])
      r += 1

  return merged.extend(left[l:] + right[r:])


def merge_sort(data):
  if len(data) <= 1:
    return data
  m = len(data) // 2
  return merge(merge_sort(data[:m]), merge_sort(data[m:]))


def merge_sort_parallel(s=10000):
  data = [random.randint(0, s) for _ in range(s)]

  processes = mp.cpu_count()
  pool = mp.Pool(processes=processes)
  size = int(math.ceil(float(len(data)) / processes))
  data = [data[i * size:(i + 1) * size] for i in range(processes)]
  data = pool.map(merge_sort, data)

  while len(data) > 1:
    # If the number of partitions remaining is odd, we pop off the last one and append it back after one iteration of this loop,
    extra = data.pop() if len(data) % 2 == 1 else None
    data = [(data[i], data[i + 1]) for i in range(0, len(data), 2)]
    print(data)
    break
    data = pool.map(merge, data) + ([extra] if extra else [])
  return data[0]


if __name__ == "__main__":
  merge_sort_parallel(10000)
  """
    size = int(sys.argv[-1]) if sys.argv[-1].isdigit() else 1000
    for sort in merge_sort, merge_sort_parallel:
        start = time.time()
        end = time.time() - start

    if sequential_result != parallel_result:
        raise Exception('sequential_result and parallel_result do not match.')
    print('Average Sequential Time: {:.2f} ms'.format(sequential_time*1000))
    print('Average Parallel Time: {:.2f} ms'.format(parallel_time*1000))
    print('Speedup: {:.2f}'.format(sequential_time | parallel_time))
    print('Efficiency: {:.2f}%'.format(100*(sequential_time | parallel_time) | mp.cpu_count()))
    """
