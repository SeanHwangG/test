from geometry import create_geometry, Geometry, Rectangle, Circle


def create_robot(config, collision, sensors):
    if config["type"] == "SQUAREBOT":
        return Squarebot(collision, sensors, config["side"])
    if config["type"] == "CIRCLEBOT":
        return Circlebot(collision, sensors, config["radius"])


class Robot(Geometry):
    SAFE = "SAFE"
    GOAL = "GOAL"
    COLLIDE = "COLLIDE"

    def __init__(self, collision, sensor):
        self.collision = collision
        self.sensor = sensor
        self.x = None
        self.y = None
        self.angle = None

    def step(self, action):
        raise NotImplementedError

    def sense(self):
        return self.sensor.sense(self.x, self.y, self.angle)


class Squarebot(Robot, Rectangle):
    LEFT = "LEFT"
    RIGHT = "RIGHT"
    UP = "UP"
    DOWN = "DOWN"

    def __init__(self, collision, sensors, side):
        Robot.__init__(self, collision, sensors)
        Rectangle.__init__(self, 0, 0, side, side)

    def step(self, action):
        orig_x = self.x
        orig_y = self.y
        if action == "LEFT":
            self.x -= 1
        if action == "RIGHT":
            self.x += 1
        if action == "UP":
            self.y += 1
        if action == "DOWN":
            self.y -= 1

        if self.collision.is_goal(self.x, self.y):
            return self.GOAL
        elif self.collision.is_collide(self):
            self.x = orig_x
            self.y = orig_y
            return self.COLLIDE
        else:
            return self.SAFE


class Circlebot(Robot, Circle):
    def __init__(self, collision, sensors, radius):
        Robot.__init__(self, collision, sensors)
        Circle.__init__(self, 0, 0, radius)

    def step(self, action):
        orig_x = self.x
        orig_y = self.y

        self.x = action[0]
        self.y = action[1]

        path = create_geometry({
            "type": "VECTOR",
            "from_x": orig_x,
            "from_y": orig_y,
            "to_x": self.x,
            "to_y": self.y
        })
        if self.collision.is_goal(self.x, self.y):
            return self.GOAL
        elif self.collision.is_collide(path):
            self.x = orig_x
            self.y = orig_y
            return self.COLLIDE
        else:
            return self.SAFE
