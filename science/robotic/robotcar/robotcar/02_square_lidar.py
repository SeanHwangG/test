from simulator import Simulator
from collections import deque
import random
import time
import math

config = {
    "name": "[2]square_lidar",
    "width": 500,
    "height": 300,
    "goal_x": 450,
    "goal_y": 250,
    "robot": {
        "type": "SQUAREBOT",
        "start_x": 50,
        "start_y": 50,
        "side": 10
    },
    "sensor": {
        "type": "LIDAR",
        "angles": [0, 90, 180, 270],
        "max_range": 100
    },
    "obstacles": [
        {
            "type": "RECTANGLE",
            "x": 100,
            "y": 200,
            "width": 150,
            "height": 150,
        },
        {
            "type": "RECTANGLE",
            "x": 400,
            "y": 100,
            "width": 150,
            "height": 150,
        },
    ]
}


def example0():
    """ Simple Solution
    """
    config["grid_size"] = 10
    sim = Simulator(config)
    sim.reset()

    right = 150
    up = 150

    while True:
        if right > 0:
            sim.step("RIGHT")
            right -= 1
        elif up > 0:
            up -= 1
            sim.step("UP")
        else:
            sim.step("RIGHT")
        sim.render()
        if sim.is_done():
            break


example0()
