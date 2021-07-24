import random
import threading
import psutil
import cProfile
import time

_ = list(psutil.process_iter())
time.sleep(5)

process = list()

for proc in psutil.process_iter(attrs=None, ad_value=None):
  procInfo = proc.as_dict(attrs=['name', 'cpu_percent'])
  if "type_" in procInfo['name']:
    process.append(procInfo)
print(process)


def fn_timer(func):
  def wrapper(*args, **kwargs):
    global running
    t0 = time.time()
    t1 = threading.Thread(target=calc_cpu)
    t1.start()
    result = func(*args, **kwargs)
    running = False

    print(f"Total running {func.__name__}: {time.time() - t0} seconds")
    return result
  return wrapper


# python -m cProfile
# python -m memory_profiler 66_psutil.py
@fn_timer
def i_hate_this():
  tab = []
  for _ in range(10000000):
    tab.append(random.randint(1, 10000))
  tab.sort()
  return tab[:10]
