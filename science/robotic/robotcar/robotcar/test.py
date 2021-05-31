import numpy as np
from math import pi
import math
import mathpl

Pf = [0] * 11
Pf[0] = 0.01
for i in range(1, 11):
    Pf[i] = Pf[i - 1] / (Pf[i - 1] + 0.333333 * (1-Pf[i - 1]))

print(Pf)
