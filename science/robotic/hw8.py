from collections import Counter
import numpy as np
import matplotlib.pyplot as plt


def rejection_sample():
    sample = (np.random.normal(0, 0.5))
    while 1 < abs(sample):
        sample = (np.random.normal(0, 0.5))
    return sample


def action_model(x, u):
    """ return next position given update u

    Args:
        x (int): position
        u (int): next position from {-1, 0, 1}
    """
    if abs(x + u) > 50:
        return x
    else:
        return x + u + rejection_sample()


def sensor_model(x, z):
    """ 
    Args:
        x (int): position
        z (int): measurement (1 if door, 0 if not)
    """
    if 0.5 <= x <= 1 or 2 <= x <= 2.5 or 22.5 <= x <= 23:
        if z == 0:
            return 0.7
        else:
            return 0.3
    else:
        if z == 0:
            return 0.15
        else:
            return 0.85


def particle_filter(P, U, Z):
    """ Given particles P, for T times

    Args:
        P (M, ): starting positions
        U (T, ): action
        Z (T, ): measurement
    Returns:
        updated (N, ):
    """

    # position, belief
    beliefs = []
    for init_pos in P:
        pos = init_pos
        bel = 1
        for i in range(len(U)):
            pos = action_model(pos, U[i])
            bel *= sensor_model(pos, Z[i])
        beliefs.append((init_pos, bel))
    max_bel = max(n for _, n in beliefs)

    new_P = []
    for pos in P:
        # rejection sample
        m = 0
        index = np.random.randint(len(beliefs))
        while m < beliefs[index][1]:
            index = np.random.randint(len(beliefs))
            m = np.random.uniform(0, max_bel)
        new_P.append(beliefs[index][0])
    return new_P


def test_particle(size, iteration):
    U = [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, -1, -1, -1, -1, -1, -1,
         -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1]
    Z = [0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1,
         0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0]
    P = np.arange(-50, 50, 100/size)
    for _ in range(iteration):
        P = particle_filter(P, U, Z)
    plt.hist(P)
    plt.show()


test_particle(1000, 100)
