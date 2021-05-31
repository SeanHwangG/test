from simulator import Simulator
import random
import time
import math
from collections import deque

config = {
    "name": "[0]square_birdeye",
    "width": 200,
    "height": 200,
    "goal_x": 150,
    "goal_y": 150,
    "robot": {
        "type": "SQUAREBOT",
        "start_x": 30,
        "start_y": 30,
        "side": 5
    },
    "sensor": {
        "type": "BIRDEYE"
    },
    "obstacles": [
        {
            "type": "RECTANGLE",
            "x": 100,
            "y": 100,
            "width": 30,
            "height": 100,
        },
    ]
}

""" Example 0: Simple Brute-Force Solution

Pros:
    Shortest Path
    Fastest Computationa
Cons:
    Fails if start / goal position changes
"""


def example0():
    sim = Simulator(config, debug=1)
    sim.reset()

    right = 120
    up = 120

    while True:
        if right > 0:
            sim.step("RIGHT")
            right -= 1
        elif up > 0:
            up -= 1
            sim.step("UP")
        sim.render()
        if sim.is_done():
            break


""" Example 1: Greedy Agent (+ randomize start)
Pros:
    Shortest Path
    Fastest Computation
Cons:
    Fails if obstacle is in the path
"""


class GreedyAgent:
    def __init__(self, sensor_data):
        self.goal_x = sensor_data["goal_x"]
        self.goal_y = sensor_data["goal_y"]

    def pick_action(self, sensor_data):
        if sensor_data["x"] < self.goal_x:
            return "RIGHT"
        if sensor_data["x"] > self.goal_x:
            return "LEFT"
        if sensor_data["y"] < self.goal_y:
            return "UP"
        if sensor_data["y"] > self.goal_y:
            return "DOWN"


def example1():
    config["robot"]["random"] = True
    sim = Simulator(config, debug=Simulator.RENDER)

    sensor_data = sim.reset()

    agent = GreedyAgent(sensor_data)

    while True:
        action = agent.pick_action(sensor_data)
        sensor_data = sim.step(action)
        sim.render()
        if sim.is_done():
            break


""" Example 2: BFS Agent

Pros:
    Shortest Path
    
Cons:
    Slow Computation
"""


class BFSAgent:
    def __init__(self, sensor_data):
        self.start = (sensor_data["x"], sensor_data["y"])
        self.goal = (sensor_data["goal_x"], sensor_data["goal_y"])
        self.pixel = sensor_data["pixel"]
        self.parent = self.bfs(self.start, self.goal)

        self.next = {}
        cur = self.goal
        while cur != self.start:
            self.next[self.parent[cur]] = cur
            cur = self.parent[cur]

    def bfs(self, start, goal):
        """ Build bfs tree 

        Args:
            start ([type]): [description]
            goal ([type]): [description]

        Returns:
            [type]: [description]
        """
        parent = {}
        q = deque([start])
        while len(q) != 0:
            cur = q.popleft()
            for dir in [(1, 0), (-1, 0), (0, 1), (0, -1)]:
                next = (cur[0] + dir[0], cur[1] + dir[1])
                if self.pixel[next] == 0 and next not in parent:
                    parent[next] = cur
                    q.append(next)
                if next == goal:
                    return parent
        return parent

    def pick_action(self, sensor_data):
        cur = (sensor_data["x"], sensor_data["y"])
        if cur == self.goal:
            return ""
        next = self.next[cur]
        if cur[0] + 1 == next[0]:
            return "RIGHT"
        if cur[0] - 1 == next[0]:
            return "LEFT"
        if cur[1] + 1 == next[1]:
            return "UP"
        if cur[1] - 1 == next[1]:
            return "DOWN"


def example2():
    """ BFS
    """
    config["robot"]["random"] = True

    sim = Simulator(config, debug=1)
    sensor_data = sim.reset()

    agent = BFSAgent(sensor_data)

    while True:
        action = agent.pick_action(sensor_data)
        sensor_data = sim.step(action)
        sim.render()
        if sim.is_done():
            break


example0()
example1()
example2()
