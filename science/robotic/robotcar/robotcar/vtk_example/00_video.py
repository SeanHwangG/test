import vtk
from vtkplotter import Box, show, Line
from cv2 import cv2
import pygame
import numpy as np
import os
import sys


def moving_square():
    pygame.init()

    # [center_x, center_y, center_z], size_x, size_y, size_z
    world = Box([0, 0, 0], 200, 300, 50).wireframe()
    #rect = Box([0, 0, 0], 50, 50, 50, size=(), c='g', alpha=1)
    rect = Line((0, 0, 0), (200, 200, 200), dotted=False, res=2)
    print(dir(rect))
    # print(rect.alpha(0.5))

    running = True
    while running:
        rect.pos(rect.x()+1, rect.y(), rect.z())
        show(world, rect, interactive=0, viewup='z', title="FSD")
        event = pygame.event.get()
        key = pygame.key.get_pressed()

        # Press Q to close window
        if key[pygame.K_q]:
            return


moving_square()
