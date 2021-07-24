import random
import time
import numpy as np
import threading
from concurrent.futures import ThreadPoolExecutor, ProcessPoolExecutor


def io_heavy(sec):
    time.sleep(sec)
    return sec


def python_heavy(mat_size):
    mat = [[1] * mat_size for _ in range(mat_size)]
    return [[2 * n for n in li] for li in mat]


def c_heavy(mat_size):
    mat = np.random.random((mat_size, mat_size))
    return mat * mat


def io_heavy_performance(n_thread, n_repeat, sleep_for):
    print(f"io_heavy_Parallel {n_thread} {n_repeat} {sleep_for}")
    start = time.perf_counter()
    for _ in range(n_repeat):
        io_heavy(sleep_for)
    single_time = time.perf_counter() - start
    print(f"Single-thread \t {single_time:.2f}s")

    print()
    start = time.perf_counter()
    with ThreadPoolExecutor(n_thread) as ex:
        futures = [ex.submit(io_heavy, sleep_for) for _ in range(n_repeat)]
        for future in futures:
            future.result()
    multithreading_time = time.perf_counter() - start
    print(f"Multi-thread \t {multithreading_time:.2f}s")
    print(f'Speedup (x) \t {single_time / multithreading_time:.2f}')
    print(
        f'Efficiency \t {(single_time / multithreading_time) / n_thread:.2%}\n'
    )


def python_heavy_performance(n_thread, n_repeat, mat_size):
    print(f"cpu_heavy_Parallel {n_thread} {n_repeat} {mat_size}")
    start = time.perf_counter()
    for _ in range(n_repeat):
        python_heavy(mat_size)
    single_time = time.perf_counter() - start
    print(f"Single-thread \t {single_time:.2f}s")

    print()
    start = time.perf_counter()
    with ThreadPoolExecutor(max_workers=n_thread) as ex:
        futures = [ex.submit(python_heavy, mat_size) for i in range(n_repeat)]
        for f in futures:
            f.result()
    multithreading_time = time.perf_counter() - start
    print(f"Multi-thread \t {multithreading_time:.2f}s")
    print(f'Speedup \t {single_time / multithreading_time:.2f}')
    print(
        f'Efficiency \t {(single_time / multithreading_time) / n_thread:.2%}\n'
    )


def c_heavy_performance(n_thread, n_repeat, mat_size):
    print(f"c_heavy_Parallel {n_thread} {n_repeat} {mat_size}")
    start = time.perf_counter()
    for _ in range(n_repeat):
        c_heavy(mat_size)
    single_time = time.perf_counter() - start
    print(f"Single-thread \t {single_time:.2f}s")

    print()
    start = time.perf_counter()
    with ThreadPoolExecutor(max_workers=n_thread) as ex:
        futures = [ex.submit(c_heavy, mat_size) for i in range(n_repeat)]
        for f in futures:
            f.result()
    multithreading_time = time.perf_counter() - start
    print(f"Multi-thread \t {multithreading_time:.2f}s")
    print(f'Speedup \t {single_time / multithreading_time:.2f}')
    print(
        f'Efficiency \t {(single_time / multithreading_time) / n_thread:.2%}\n'
    )


if __name__ == "__main__":
    io_heavy_performance(2, 16, 1)
    io_heavy_performance(4, 16, 1)
    io_heavy_performance(8, 16, 1)
    io_heavy_performance(16, 16, 1)
    print("___________")
    python_heavy_performance(2, 72, 500)
    python_heavy_performance(4, 72, 500)
    python_heavy_performance(8, 72, 500)
    python_heavy_performance(16, 72, 500)
    print("___________")
    c_heavy_performance(2, 72, 5000)
    c_heavy_performance(4, 72, 5000)
    c_heavy_performance(8, 72, 5000)
    c_heavy_performance(16, 72, 5000)
