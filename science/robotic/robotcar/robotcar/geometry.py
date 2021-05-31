import vtkplotter as vtk
import numpy as np


def create_geometry(config):
    if config["type"] == "RECTANGLE":
        return Rectangle(config["x"], config["y"], config["width"], config["height"])
    if config["type"] == "CIRCLE":
        return Circle(config["x"], config["y"], config["radius"])
    if config["type"] == "VECTOR":
        return Vector(config["from_x"], config["from_y"], config["to_x"], config["to_y"])


RISE = 5


class Geometry:

    def __init__(self):
        raise NotImplementedError

    def corners(self):
        """ 
        Returns:
            corners (ndarray): (n, 2) corners to check collisions for
        """
        raise NotImplementedError

    def vtk_render(self, color, dotted, alpha, z_index):
        """ return drawable VTK object

        Arguments:
            color (string): 'black', 'blue', 'red
            dotted (bool): [description]
            alpha (int): visibility. (0: invisible / 1: visible)
            z_index (int)

        Returns:
            [type] -- [description]
        """
        return None

    def numpy_render(self, grid):
        return grid


class Rectangle(Geometry):
    def __init__(self, x, y, width, height):
        self.x = x
        self.y = y
        self.width = width
        self.height = height

    def corners(self):
        corners = [(self.x - self.width, self.y - self.height / 2),
                   (self.x + self.width, self.y - self.height / 2),
                   (self.x - self.width, self.y + self.height / 2),
                   (self.x + self.width, self.y + self.height / 2)]
        return np.array(corners).astype(int)

    def vtk_render(self, color, dotted=False, alpha=1, z_index=0):
        return vtk.Box((self.x, self.y, 0), self.width, self.height, RISE+z_index, size=(), c=color, alpha=alpha)

    def numpy_render(self, grid):
        for y in range(int(self.y - self.height / 2), int(self.y + self.height / 2 + 1)):
            for x in range(int(self.x - self.width / 2), int(self.x + self.width / 2 + 1)):
                try:
                    grid[y, x] = 1
                except:
                    pass  # out of screen
        return grid


class Circle(Geometry):
    def __init__(self, x, y, radius):
        self.x = x
        self.y = y
        self.radius = radius

    def corners(self):
        corners = []

        for angle in range(0, 360, 10):
            corners.append((self.x + np.cos(angle * np.pi / 180),
                            self.y + np.sin(angle * np.pi / 180)))

        return np.array(corners).astype(int)

    def vtk_render(self, color, dotted=False, alpha=1, z_index=0):
        return vtk.Cylinder((self.x, self.y, 0), self.radius, RISE+z_index, axis=(0, 0, 1), c=color, alpha=alpha)

    def numpy_render(self, grid):
        for y in range(int(self.y - self.radius), int(self.y + self.radius + 1)):
            for x in range(int(self.y - self.radius), int(self.y + self.radius + 1)):
                if np.sqrt((x - self.x) ** 2 + (y - self.y) ** 2) <= self.radius:
                    try:
                        grid[y, x] = 1
                    except:
                        pass
        return grid


class Vector(Geometry):
    def __init__(self, from_x, from_y, to_x, to_y):
        self.from_x = from_x
        self.from_y = from_y
        self.to_x = to_x
        self.to_y = to_y

    def corners(self):
        corners = []
        acc = 100
        for i in range(acc):
            corners.append((self.from_x * (acc - i) / acc + self.to_x * i / acc,
                            self.from_y * (acc - i) / acc + self.to_y * i / acc))
        return np.array(corners).astype(int)

    def get_length(self):
        return np.sqrt((self.from_y - self.to_y) ** 2 + (self.from_x - self.to_x) ** 2)

    def update_length(self, length):
        ratio = length / self.get_length()
        self.to_x = (self.from_x * (1 - ratio) + self.to_x * ratio)
        self.to_y = (self.from_y * (1 - ratio) + self.to_y * ratio)

    def vtk_render(self, color, dotted=False, alpha=1, z_index=0):
        return vtk.Line((self.from_x, self.from_y, RISE + z_index), (self.to_x, self.to_y, RISE + z_index), c=color, dotted=dotted)
