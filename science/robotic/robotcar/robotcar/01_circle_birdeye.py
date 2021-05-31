from simulator import Simulator
import random
import time
import math
import numpy as np
from collections import deque

config = {
    "name": "[title]",
    "width": 200,
    "height": 200,
    "goal_x": 150,
    "goal_y": 150,
    "robot": {
        "type": "CIRCLEBOT",
        "start_x": 30,
        "start_y": 30,
        "radius": 5,
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


class Agent:
    def __init__(self, sensor_data, sample_type, n_sample, dist_neighbor):
        self.start = (sensor_data["x"], sensor_data["y"])
        self.goal = (sensor_data["goal_x"], sensor_data["goal_y"])
        self.pixel = sensor_data["pixel"]
        self.width = self.pixel.shape[1]
        self.height = self.pixel.shape[0]

        if sample_type == "grid":
            self.samples = self.grid_sample(n_sample, self.start, self.goal)
        elif sample_type == "halton":
            self.samples = self.halton_sample(n_sample, self.start, self.goal)

        self.neighbors = self.radius_neighbor(self.samples, dist_neighbor)

        self.parent = self.bfs(self.start, self.goal, self.neighbors)

        self.next = {}
        cur = self.goal
        while cur != self.start:
            if cur not in self.parent:
                print("path is not possible")
                exit()

            self.next[self.parent[cur]] = cur
            cur = self.parent[cur]

    def grid_sample(self, n, start, goal):
        samples = [start, goal]
        for i in range(n):
            for j in range(n):
                point = (self.height * i // n, self.width * j // n)
                if self.pixel[point] != 1:
                    samples.append((point[1], point[0]))
        return samples

    def halton_sample(self, n, start, goal):
        points = np.zeros((n, 2))
        p1 = 2
        p2 = 3

        for i in range(n):
            j = i
            f = 1 / p1
            while j > 0:
                r = j % p1
                j = j // p1
                points[i, 0] += f * r
                f = f / p1

        for i in range(n):
            j = i
            f = 1 / p2
            while j > 0:
                r = j % p2
                j = j // p2
                points[i, 1] += f * r
                f = f / p2

        samples = [start, goal]
        for point in points:
            row = int(point[0] * self.width)
            col = int(point[1] * self.height)
            if self.pixel[row, col] != 1:
                samples.append((col, row))

        return samples

    def distance(self, p1, p2):
        return np.sqrt((p1[0] - p2[0]) ** 2 + (p1[1] - p2[1]) ** 2)

    def radius_neighbor(self, samples, radius):
        """ connect vertices with given radius

        Args:
            samples ([(x, y)]): list of vertices
            radius (int): neighbor threshold

        Returns:
            (dict): {node: [connected_nodes]}
        """
        neighbors = {}
        for sample1 in samples:
            for sample2 in samples:
                if sample1 == sample2:
                    continue
                if self.distance(sample1, sample2) < radius and not self.is_collide(sample1, sample2):
                    if sample1 not in neighbors:
                        neighbors[sample1] = set([sample2])
                    else:
                        neighbors[sample1].add(sample2)
                    if sample2 not in neighbors:
                        neighbors[sample2] = set([sample1])
                    else:
                        neighbors[sample2].add(sample1)
        return neighbors

    def bfs(self, start, goal, neighbors):
        parent = {}
        q = deque([start])
        while len(q) != 0:
            cur = q.popleft()
            if cur not in neighbors:
                print("Choose bigger radius")
                exit()
            for nei in self.neighbors[cur]:
                if nei not in parent:
                    parent[nei] = cur
                    q.append(nei)
        return parent

    def pick_action(self, sensor_data):
        cur = (sensor_data["x"], sensor_data["y"])
        return self.next[cur]

    def is_collide(self, p1, p2):
        for i in range(10):
            row = int(p1[1] * i / 10 + p2[1] * (10 - i) / 10)
            col = int(p1[0] * i / 10 + p2[0] * (10 - i) / 10)
            if self.pixel[row][col] == 1:
                return True
        return False


def example0():
    """ Introduce new robot
    """
    sim = Simulator(config, debug=2)
    sensor_data = sim.reset()

    actions = [(150, 30), (150, 150)]
    count = 0
    while True:
        sim.step(actions[count])
        count += 1
        sim.render()
        if sim.is_done():
            break


def example1():
    """ Grid sample + BFS
    """
    sim = Simulator(config, debug=Simulator.VERBOSE)

    sensor_data = sim.reset()

    agent = Agent(sensor_data, "grid", 15, 15)
    sim.plot_samples(agent.samples)

    while True:
        action = agent.pick_action(sensor_data)
        sensor_data = sim.step(action)
        sim.render()
        if sim.is_done():
            time.sleep(100)


def example2():
    """ Halton Sample + BFS
    """
    sim = Simulator(config, debug=Simulator.VERBOSE)

    sensor_data = sim.reset()

    agent = Agent(sensor_data, "halton", 100, 30)
    sim.plot_samples(agent.samples)

    while True:
        action = agent.pick_action(sensor_data)
        print(action)
        sensor_data = sim.step(action)
        sim.render()
        if sim.is_done():
            time.sleep(100)
            break


example2()
