import sys
import numpy as np
import pygame
import vtkplotter as vtk
import cv2
import time
import math
import matplotlib.pyplot as plt
from geometry import create_geometry, Geometry, RISE
from collisionCheck import CollisionCheck
from robot import create_robot
from sensor import create_sensor


class Simulator:
    SIMPLE = 0
    RENDER = 1
    VERBOSE = 2

    def __init__(self, config, debug=1):
        pygame.init()
        self.random_start = config["robot"].get("random", False)
        self.debug = debug
        self.max_step = config.get("max_step", 5000)
        self.delay = config.get("delay", 0)

        self.width = config["width"]
        self.height = config["height"]

        self.start_x = config["robot"]["start_x"]
        self.start_y = config["robot"]["start_y"]
        self.start_angle = config.get("start_angle", 0)

        # for occupancy grid mapping
        self.grid_size = config.get("grid_size", -1)
        self.n_grid = math.ceil(self.width / self.grid_size) * \
            math.ceil(self.height / self.grid_size)
        self.confidence = config.get("confidence", 1)

        # adding boundary
        self.obstacles = [
            # LEFT
            create_geometry({
                "type": "RECTANGLE",
                "x": 5,
                "y": self.height / 2,
                "width": 10,
                "height": self.height
            }),
            # RIGHT
            create_geometry({
                "type": "RECTANGLE",
                "x": self.width - 5,
                "y": self.height / 2,
                "width": 10,
                "height": self.height
            }),
            # TOP
            create_geometry({
                "type": "RECTANGLE",
                "x": self.width / 2,
                "y": 5,
                "width": self.width,
                "height": 10
            }),
            # BOTTOM
            create_geometry({
                "type": "RECTANGLE",
                "x": self.width / 2,
                "y": self.height - 5,
                "width": self.width,
                "height": 10
            })
        ]

        for obs in config.get("obstacles", []):
            self.obstacles.append(create_geometry(obs))

        self.goal = create_geometry(
            {"type": "CIRCLE", "x": config["goal_x"], "y": config["goal_y"], "radius": 5})

        self.collision_check = CollisionCheck(self.width, self.height, self.obstacles,
                                              self.goal.x, self.goal.y, self.grid_size)

        self.robot = create_robot(config["robot"], self.collision_check,
                                  create_sensor(config["sensor"], self.collision_check))

    def reset(self):
        self.robot.x = self.start_x
        self.robot.y = self.start_y
        self.robot.angle = self.start_angle
        self.total_step = 0

        if self.random_start:
            self.robot.x = int(np.random.random() * self.width)
            self.robot.y = int(np.random.random() * self.height)
            while self.collision_check.is_collide(self.robot):
                self.robot.x = int(np.random.random() * self.width)
                self.robot.y = int(np.random.random() * self.height)

        self.vtk_grid = ()
        self.vtk_hit = ()
        self.vtk_path = ()
        self.vtk_sample = ()

        if self.grid_size != -1:
            # log(occupied / free)
            self.log_odd = np.zeros(self.n_grid)

            self.grid_width = math.ceil(self.width / self.grid_size)
            self.grid_height = math.ceil(self.height / self.grid_size)

            self.n_grid = self.grid_width * self.grid_height
            self.grid_map = np.empty(self.n_grid).astype(object)

            for index in range(self.n_grid):
                grid_r = index // self.grid_width
                grid_c = index % self.grid_width

                self.grid_map[index] = create_geometry({
                    "type": "RECTANGLE",
                    "x": self.grid_size * grid_c + self.grid_size / 2,
                    "y": self.grid_size * grid_r + self.grid_size / 2,
                    "width": self.grid_size,
                    "height": self.grid_size
                })
                self.vtk_grid += self.grid_map[index].vtk_render(
                    'black', alpha=0.5, z_index=2),
        self.paths = [(self.robot.x, self.robot.y)]

        return self.robot.sense()

    def step(self, action_type):
        self.total_step += 1

        if self.debug == self.VERBOSE:
            print("robot is at", self.robot.x, self.robot.y)
            print("took action", action_type)

        self.robot.step(action_type)
        self.paths.append((self.robot.x, self.robot.y))

        return self.robot.sense()

    def is_done(self):
        if self.robot.x == self.goal.x and self.robot.y == self.goal.y or\
                self.max_step <= self.total_step:
            self.over_message(True)
            return True

        return False

    def plot_samples(self, points):
        """ add samples to visualize them on the map

        Args:
            points (ndarray): (n, 2) numpy array
        """
        for point in points:
            dot = create_geometry({
                "type": "CIRCLE",
                "radius": 1,
                "x": point[0],
                "y": point[1]
            })
            self.vtk_sample += (dot.vtk_render('blue'),)

    def over_message(self, done):
        if self.debug != self.SIMPLE:
            if done:
                print("Reached goal with ", self.total_step, "step")
                print(self.paths)
            else:
                print("Couldn't reach goal after", self.max_step, "step")
        else:
            if done:
                print("Reached goal with ", self.total_step, "step")
                print(self.paths)
            else:
                print("Couldn't reach goal after", self.max_step, "step")

    def render(self):
        # do not render
        if self.debug == self.SIMPLE:
            return

        if self.total_step <= 1:
            world = vtk.Box([self.width / 2, self.height/2, RISE/2],
                            self.width, self.height, RISE).wireframe()
            vtk.show(world, axes=1, bg="white", viewup="y", interactive=0)
            self.vtk_map = (self.goal.vtk_render('blue'), )

            for obs in self.obstacles:
                self.vtk_map += (obs.vtk_render('black'), )
        if len(self.paths) > 1:
            self.vtk_path += (vtk.Line((self.paths[-2] + (0,)),
                                       (self.paths[-1] + (0,)), c='black', lw=2), )

        # Occupancy grid map
        if self.grid_size != -1 and len(self.paths) % 10 == 0:
            sense = self.robot.sense()
            occupied = sense['occupied']
            free = sense['free']
            dists = sense['dist']
            max_range = sense['max_range']
            angles = sense['angles']
            x = sense['x']
            y = sense['y']
            robot_angle = sense['robot_angle']

            for i in range(len(dists)):
                dist = dists[i]
                angle = angles[i]
                if dists[i] != max_range:
                    self.vtk_hit += (vtk.Circle(pos=(x + dist * math.cos((angle + robot_angle) / 180 * math.pi),
                                                     y + dist * math.sin((angle + robot_angle) / 180 * math.pi), RISE + 1), r=2, fill=True, c='red'),)
            for i in occupied:
                self.log_odd[i] -= self.confidence
            for i in free:
                self.log_odd[i] += self.confidence

            for index in range(self.n_grid):
                self.vtk_grid[index].alpha(
                    1/(math.e ** self.log_odd[index] + 1))
        # Log odd map
        if self.grid_size != -1:
            vtk.show(self.robot.vtk_render('red', alpha=1), self.vtk_grid,
                     self.vtk_hit, self.robot.sensor.vtk_render(), self.vtk_sample, self.vtk_path)
        # Regular map
        else:
            vtk.show(self.robot.vtk_render('red', alpha=1), self.robot.sensor.vtk_render(),
                     self.vtk_sample, self.vtk_map, self.vtk_path)
