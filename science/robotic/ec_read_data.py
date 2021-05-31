def read_world(filename: str):
  """ Reads the world definition

  Returns:
    landmakrs (dict): {id, (x, y)}
  """
  landmarks = dict()

  f = open(filename)

  for line in f:
    line_s = line.split('\n')
    line_spl = line_s[0].split(' ')
    landmarks[int(line_spl[0])] = [float(line_spl[1]), float(line_spl[2])]

  return landmarks


def read_sensor_data(filename):
  """ Reads the odometry and sensor readings.

  Args:
    filename (str)

  Returns:
    sensor_readings (dict)

    where
      sensor_readings[timestep, 'odometry']: {r1, r2, t}
      sensor_readings[timestep, 'sensor']: {id, range, bearing}

  """
  sensor_readings = dict()

  lm_ids = []
  ranges = []
  bearings = []

  first_time = True
  timestamp = 0
  f = open(filename)

  for line in f:

    line_s = line.split('\n')  # remove the new line character
    line_spl = line_s[0].split(' ')  # split the line

    if (line_spl[0] == 'ODOMETRY'):

      sensor_readings[timestamp, 'odometry'] = {
        'r1': float(line_spl[1]),
        't': float(line_spl[2]),
        'r2': float(line_spl[3])
      }

      if first_time:
        first_time = False

      else:
        sensor_readings[timestamp, 'sensor'] = {
          'id': lm_ids,
          'range': ranges,
          'bearing': bearings
        }
        lm_ids = []
        ranges = []
        bearings = []

      timestamp = timestamp + 1

    if (line_spl[0] == 'SENSOR'):

      lm_ids.append(int(line_spl[1]))
      ranges.append(float(line_spl[2]))
      bearings.append(float(line_spl[3]))

    sensor_readings[timestamp - 1, 'sensor'] = {
      'id': lm_ids,
      'range': ranges,
      'bearing': bearings
    }

  return sensor_readings
