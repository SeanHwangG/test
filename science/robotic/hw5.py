from math import sqrt
import matplotlib.pyplot as plt
import numpy as np


def computeGridSukharev(n):
    """
    Arguments:
        n : square number

    Returns:
        samples: list of samples
    """
    samples = []
    k = int(sqrt(n))
    for i in range(1, k + 1):
        for j in range(1, k + 1):
            samples.append([i / (k + 1), j / (k + 1)])

    return np.array(samples)


def computeGridRandom(n):
    return np.array([np.random.sample(n), np.random.sample(n)]).T


def computeGridHalton(n, p1, p2):
    """
    Argument:
        n: # of samples
        p1, p2: prime # for Halton sequence

    Returns:
        samples
    Halton_sequence:
        for each i from 1 to N:
            initialize itmp = i, and f = 1 / p
            while itmp > 0:
                compute the quotient q and the remainder r of the division itmp/p
                S(i) = S(i) + f · r
                itmp = f / p
    """
    samples = np.zeros((n, 2))

    for i in range(n):
        j = i
        f = 1 / p1
        while j > 0:
            r = j % p1
            j = j // p1
            samples[i, 0] += f * r
            f = f / p1

    for i in range(n):
        j = i
        f = 1 / p2
        while j > 0:
            r = j % p2
            j = j // p2
            samples[i, 1] += f * r
            f = f / p2

    return samples


pair = computeGridRandom(10)
plt.title("10 random")
plt.scatter(pair[:, 0], pair[:, 1])
plt.xlim([0, 1])
plt.ylim([0, 1])
plt.show()


pair = computeGridHalton(10, 2, 3)
plt.title("10 grid with prime 2, 3")
plt.scatter(pair[:, 0], pair[:, 1])
plt.xlim([0, 1])
plt.ylim([0, 1])
plt.show()
