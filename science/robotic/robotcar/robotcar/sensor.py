import math
import numpy as np
from geometry import create_geometry, Vector


def create_sensor(config, collision):
    if config["type"] == "BIRDEYE":
        return Birdeye(collision)
    if config["type"] == "LIDAR":
        return Lidar(collision, config["max_range"], config["angles"])


class Sensor:
    BIRDEYE = "BIRDEYE"
    RADAR = "RADAR"

    def __init__(self, collision):
        self.collision = collision

    def sense(self, x, y, robot_angle):
        raise NotImplementedError

    def vtk_render(self):
        return None


class Birdeye(Sensor):
    def __init__(self, collision):
        super().__init__(collision)

    def sense(self, x, y, robot_angle):
        data = {
            "x": x,
            "y": y,
            "goal_x": self.collision.goal_x,
            "goal_y": self.collision.goal_y,
            "pixel": self.collision.pixel
        }
        return data


class Lidar(Sensor):
    def __init__(self, collision, max_range, angles):
        super().__init__(collision)
        self.max_range = max_range
        self.angles = angles
        self.n_rays = len(angles)

    def sense(self, x, y, robot_angle):
        data = {
            "x": x,
            "y": y,
            "robot_angle": robot_angle,
            "angles": self.angles,
            "max_range": self.max_range,
            "goal_x": self.collision.goal_x,
            "goal_y": self.collision.goal_y,
            "dist": [self.max_range] * self.n_rays,
            "occupied": set(),
            "free": set()
        }
        self.vtk_objects = ()
        for i in range(self.n_rays):
            angle = self.angles[i]
            vector = create_geometry({
                "type": "VECTOR",
                "from_x": x,
                "from_y": y,
                "to_x": int(x + self.max_range * math.cos((angle + robot_angle) * math.pi / 180)),
                "to_y": int(y + self.max_range * math.sin((angle + robot_angle) * math.pi / 180))
            })
            occupied = self.collision.hitting_grids(vector)
            data["occupied"].update(occupied[0])
            data["free"].update(occupied[1])
            data["dist"][i] = self.collision.length_collide(vector)
            vector.update_length(data["dist"][i])
            self.vtk_objects += (vector.vtk_render('b', dotted=True),)

        for occ in data["occupied"]:
            if occ in data["free"]:
                data["free"].remove(occ)

        return data

    def vtk_render(self):
        return self.vtk_objects
