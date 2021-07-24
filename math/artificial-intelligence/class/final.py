import numpy as np


def action_model(x, u):
    """

    Args:
        x (int): initial position of the robot [A, B, C, D]
        u ([int]): list of updates either 1 or 0
    """
    if u == 1:
        if x == 0:
            return [(0, 0.25), (1, 0.75)]
        elif x == 1:
            return [(0, 0.25), (1, 0.25), (2, 0.5)]
        elif x == 2:
            return [(2, 0.5), (3, 0.5)]
        elif x == 3:
            return [(1, 1)]
    elif u == 0:
        return [(x, 1)]


def cntr_belief_update(bel, updates):
    """

    Args:
        bel ([float]): initial beliefs
        updates ([int]): list of updates either 1 or 0
    """
    for update in updates:
        new_bel = [0, 0, 0, 0]
        for x in range(4):
            for new_x, prob in action_model(x, update):
                new_bel[new_x] += bel[x] * prob
        bel = new_bel

    return bel


def sensor_model(x, z):
    if x == 0:
        if z == 0:
            return 0.25
        elif z == 1:
            return 0.25
        elif z == 2:
            return 0.5
        elif z == 3:
            return 0
    elif x == 1:
        if z == 0:
            return 0.35
        elif z == 1:
            return 0.5
        elif z == 2:
            return 0
        elif z == 3:
            return 0.15
    elif x == 2:
        if z == 0:
            return 0
        elif z == 1:
            return 0.25
        elif z == 2:
            return 0.5
        elif z == 3:
            return 0.25
    elif x == 3:
        if z == 0:
            return 0.1
        elif z == 1:
            return 0.15
        elif z == 2:
            return 0.4
        elif z == 3:
            return 0.35


def mes_belief_update(bel, measures):
    """

    Args:
        bel ([float]): intial beliefs
        measures (int): [description]
    """
    if len(measures) == 0:
        return bel

    for measure in measures:
        for x in range(4):
            bel[x] *= sensor_model(x, measure)
        n = 1 / sum(bel)
        bel = [b * n for b in bel]
    return bel


def belief_update(bel, measures, updates):
    for i in range(len(measures)):
        measure = measures[i]
        update = updates[i]

        new_bel = [0, 0, 0, 0]
        for x in range(4):
            for new_x, prob in action_model(x, update):
                new_bel[new_x] += bel[x] * prob
        bel = new_bel

        if measure != -1:
            for x in range(4):
                bel[x] *= sensor_model(x, measure)

                n = 1 / sum(bel)
            bel = [b * n for b in bel]

    return bel


# print(mes_belief_update([0.25, 0.25, 0.25, 0.25], [0, 0, 0, 0, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3]))  # outputs [0.0, 0.0, 0.0, 1.0]

# output: [0.11111111111111112, 0.8711111111111112, 0.0, 0.01777777777777778]
print(belief_update([0.25, 0.25, 0.25, 0.25], [0], [1,0 ]))

# here -1 is no measurement, 0 is A, 1 is B, 2 is C, 3 is D)
# output: [0.0, 0.29239611388995773, 0.339373316660254, 0.36823056944978844]
print(belief_update([0.25, 0.25, 0.25, 0.25], [-1] * 20 + [0] *
                    5 + [1] * 5 + [2] * 15 + [3] * 5, [0] * 20 + [1, 0] * 17 + [1]))
