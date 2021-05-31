import numpy as np
import cv2


class Pallete:
    def __init__(self, height, width):
        self.ix = -1
        self.iy = -1
        self.height = height
        self.width = width
        self.img = np.ones((height, width, 3), np.uint8) * 255
        self.mode = "RECTANGLE"
        self.rectangles = []
        self.drawing = False

    def draw_shape(self, event, x, y, flags, param):
        if event == cv2.EVENT_LBUTTONDOWN:
            self.drawing = True
            (self.ix, self.iy) = x, y
        elif event == cv2.EVENT_LBUTTONUP:
            self.drawing = False
            cv2.rectangle(self.img, (self.ix, self.iy), (x, y), (0, 0, 0), -1)
            self.rectangles.append([self.ix, self.iy, x, y])
        elif self.drawing:
            cv2.rectangle(self.img, (self.ix, self.iy), (x, y), (0, 0, 0), -1)

    def print(self):
        print(fr"""
config = {{
    "name": "[title]",
    "width": {self.width},
    "height": {self.height},
    "goal_x": [goal_x],
    "goal_y": [goal_y],
    "robot": {{
        "type": "[robot_type]",
        "x": "[start_x]",
        "y": "[start_y]",
        "width": 10,
        "height": 10
    }},
    "sensor": {{
        "type": "[sensor_type]"
    }},
    "obstacles": 
    """)
        print("[")
        for rect in self.rectangles:
            x = (rect[0] + rect[2]) // 2
            y = (rect[1] + rect[3]) // 2
            width = abs(rect[2] - rect[0])
            height = abs(rect[3] - rect[1])

            print(fr"""
            {
                "type": "RECTANGLE", 
                "x": {x}, 
                "y": {y}, 
                "width": {width}, 
                "height": {height}, 
            }, """)
        print("]")

    def start(self):
        windowName = 'Drawing Demo'
        cv2.namedWindow(windowName)
        cv2.setMouseCallback(windowName, self.draw_shape)
        while(True):
            cv2.imshow(windowName, self.img)

            k = cv2.waitKey(1)
            if k == 27:
                self.print()
                break

        cv2.destroyAllWindows()


p = Pallete(500, 500)
p.start()
