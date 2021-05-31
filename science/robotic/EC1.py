from collections import Counter
import numpy as np
import matplotlib.pyplot as plt


def next_pos(x, u):
  """ Using bayes rule, calculate next position, probability
  Args:
      x (int): position
      u (int): action space {-1: move_left, 1:move_right}
  Returns:
      [(next_x, prob)]
  """
  # move right
  if u == 1:
    if x == 19:
      return [(x, 1)]
    elif x == 18:
      return [(x, 0.25), (x + 1, 0.75)]
    else:
      return [(x, 0.25), (x + 1, 0.5), (x + 2, 0.25)]
  # move left
  else:
    if x == 0:
      return [(x, 1)]
    elif x == 1:
      return [(x, 0.25), (x - 1, 0.75)]
    else:
      return [(x, 0.25), (x - 1, 0.5), (x - 2, 0.25)]


def update_bel(bel, u):
  """
  """
  new_bel = np.zeros_like(bel)

  for i in range(20):
    for new_x, prob in next_pos(i, u):
      new_bel[new_x] += bel[i] * prob

  return new_bel


bel = np.hstack((np.zeros(10), 1, np.zeros(9)))
for u in [1, 1, 1, 1, 1, 1, 1, 1, 1, -1, -1, -1]:
  bel = update_bel(bel, u)

print(bel)
plt.plot(bel)
plt.show()
