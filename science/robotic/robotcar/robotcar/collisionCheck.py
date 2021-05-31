from cv2 import cv2
from geometry import Vector
import numpy as np
import math


def dist(x1, y1, x2, y2):
    return np.sqrt((y2 - y1) ** 2 + (x2 - x1) ** 2)


class CollisionCheck:
    FREE = 0
    OCCUPIED = 1

    def __init__(self, width, height, obstacles, goal_x, goal_y, grid_size=0):
        self.obstacles = obstacles
        self.goal_x = goal_x
        self.goal_y = goal_y

        if grid_size != 0:
            self.grid_size = grid_size
            self.grid_width = math.ceil(width / grid_size)
            self.grid_height = math.ceil(height / grid_size)

        # y, x
        self.pixel = np.zeros((height, width))
        for obstacle in obstacles:
            self.pixel = obstacle.numpy_render(self.pixel)

    def is_goal(self, x, y):
        return x == self.goal_x and y == self.goal_y

    def is_collide(self, obj):
        for corner in obj.corners():
            try:
                if self.pixel[corner[1], corner[0]] == self.OCCUPIED:
                    return True
            except:
                return True  # Out of bound
        return False

    def length_collide(self, vector):
        for corner in vector.corners():
            row = corner[1]
            col = corner[0]
            if self.pixel[row, col] == self.OCCUPIED:
                return dist(vector.from_x, vector.from_y, col, row)
        return dist(vector.from_x, vector.from_y, vector.to_x, vector.to_y)

    def hitting_grids(self, vector):
        """ checks whether vector is in occupancy grid 

        Arguments:
            vector (Vector): vector to check

        Returns:
            occupied, free (set((int, int))): set of (row, col)
        """
        occupied = set()
        free = set()
        for corner in vector.corners():
            row = corner[1]
            col = corner[0]
            grid_row = math.floor(row / self.grid_size)
            grid_col = math.floor(col / self.grid_size)
            index = self.grid_width * grid_row + grid_col

            if self.pixel[row, col] == self.FREE:
                free.add(index)
            elif self.pixel[row, col] == self.OCCUPIED:
                if (grid_row, grid_col) in free:
                    free.remove(index)
                occupied.add(index)
                break
        return (occupied, free)
