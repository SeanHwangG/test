import numpy as np
import scipy.stats
import matplotlib.pyplot as plt
import math
from read_data import read_world, read_sensor_data

# add random seed for generating comparable pseudo random numbers
np.random.seed(123)

# plot preferences, interactive plotting mode
plt.axis([-1, 12, 0, 10])
plt.ion()
plt.show()


def plot_state(particles, landmarks, map_limits):
  xs = []
  ys = []

  for particle in particles:
    xs.append(particle['x'])
    ys.append(particle['y'])

  lx = []
  ly = []

  for i in range(len(landmarks)):
    lx.append(landmarks[i+1][0])
    ly.append(landmarks[i+1][1])

  estimated_pose = mean_pose(particles)

  plt.clf()
  plt.plot(xs, ys, 'r.')
  plt.plot(lx, ly, 'bo', markersize=10)
  plt.quiver(estimated_pose[0], estimated_pose[1], np.cos(
      estimated_pose[2]), np.sin(estimated_pose[2]), angles='xy', scale_units='xy')
  plt.axis(map_limits)

  plt.pause(0.01)


def initialize_particles(num_particles, map_limits):
  """
  Args:
      num_particles (int)
      map_limits ([int]): [x_min, x_max, y_min, y_max]

  Returns:
      particles ([dict]): {x, y, theta}
  """

  particles = []

  for i in range(num_particles):
    particle = dict()

    particle['x'] = np.random.uniform(map_limits[0], map_limits[1])
    particle['y'] = np.random.uniform(map_limits[2], map_limits[3])
    particle['theta'] = np.random.uniform(-np.pi, np.pi)

    particles.append(particle)

  return particles


def mean_pose(particles):
  """ 
  Args:
      particles ([dict]): {x, y, theta}

  Returns:
      [mean_x, mean_y, mean_theta]
  """

  xs = []
  ys = []

  vxs_theta = []
  vys_theta = []

  for particle in particles:
    xs.append(particle['x'])
    ys.append(particle['y'])

    # we cannot simply average the angles because of the wraparound (jump from -pi to pi)
    vxs_theta.append(np.cos(particle['theta']))
    vys_theta.append(np.sin(particle['theta']))

  return [np.mean(xs), np.mean(ys), np.arctan2(np.mean(vys_theta), np.mean(vxs_theta))]


def sample_motion_model(odometry, particles):
  u = [odometry['r1'], odometry['r2'], odometry['t']]
  alpha = [0.1, 0.1, 0.05, 0.05]

  new_particles = []

  for particle in particles:
    x = [particle['x'], particle['y'], particle['theta']]
    d_hat_r1 = u[0] + np.random.normal(0, alpha[0]*u[0] + alpha[1]*u[2])
    d_hat_r2 = u[1] + np.random.normal(0, alpha[0]*u[1] + alpha[1]*u[2])
    d_hat_theta = u[2] + \
        np.random.normal(0, alpha[2]*u[2] + alpha[3] * (u[0]+u[1]))
    new_x = x[0] + d_hat_theta * math.cos(x[2] + d_hat_r1)
    new_y = x[1] + d_hat_theta * math.sin(x[2] + d_hat_r1)
    new_theta = x[2] + d_hat_r1 + d_hat_r2
    new_particles.append({'x': new_x, 'y': new_y, 'theta': new_theta})

  return new_particles


def eval_sensor_model(sensor_data, particles, landmarks):
  """[summary]

  Args:
      sensor_data ([type]): [description]
      particles ([dict]): {x, y, theta}
      landmakrs (dict): {id, (x, y)}

  Returns:
      [bels]
  """
  sigma = 0.2

  # {id:range}
  ranges = {}
  for i in range(len(sensor_data['id'])):
    ranges[sensor_data['id'][i]] = sensor_data['range'][i]

  weights = []
  for p in particles:
    x, y = p['x'], p['y']
    bel = 1
    for id in landmarks:
      l_x, l_y = landmarks[id]
      dist = ((x - l_x) ** 2 + (y - l_y) ** 2) ** 0.5
      try:
        bel *= np.exp(-(ranges[id] - dist) ** 2 /
                      (2*sigma)) / np.sqrt(2 * np.pi * sigma)
      except:
        pass
    weights.append(bel)

  if sum(weights) != 0:
    weights = weights / sum(weights)
  else:
    print(weights)

  return weights


def resample_particles(particles, beliefs):
  """ resample particles using stochastic universal sampling

  Args:
      particles ([dict]): {x, y, theta}
      beliefs ([int])

  Returns:
      particles ([dict]): {x, y, theta}
  """
  new_particles = []
  max_bel = max(beliefs)

  for pos in particles:
    m = 0
    index = np.random.randint(len(beliefs))
    while m < beliefs[index]:
      index = np.random.randint(len(beliefs))
      m = np.random.uniform(0, max_bel)
    new_particles.append(particles[index])

  return new_particles


def main():
  # implementation of a particle filter for robot pose estimation
  print("Reading landmark positions")
  landmarks = read_world("./data/world.dat")

  print("Reading sensor data")
  sensor_readings = read_sensor_data("./data/sensor_data.dat")

  # initialize the particles
  map_limits = [-1, 12, 0, 10]
  particles = initialize_particles(1000, map_limits)

  for timestep in range(len(sensor_readings)//2):
    plot_state(particles, landmarks, map_limits)
    new_particles = sample_motion_model(
        sensor_readings[timestep, 'odometry'], particles)
    weights = eval_sensor_model(
        sensor_readings[timestep, 'sensor'], new_particles, landmarks)
    particles = resample_particles(new_particles, weights)

  plt.show('hold')


if __name__ == "__main__":
  main()
