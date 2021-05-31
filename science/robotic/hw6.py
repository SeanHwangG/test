import numpy as np
import matplotlib.pyplot as plt


def generate_samples(mean, variance, N=1):
    return np.random.normal(mean, variance, N)


def robot_position(x0, U):
    positions = []
    cur = x0
    for u in U:
        positions.append(u + float(generate_samples(0, 1, 1)))
    return positions


lists = generate_samples(10, 10, 10000)
plt.hist(lists)
plt.show()

U = np.array([1, -1, 2, -2, 1, 0, 1, 2, -2, 1])
print(robot_position(0, U))
