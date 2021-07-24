import numpy as np


def softmax(x):
  """
  Args :
    input value [N, dimension]
  Returns :
    softmax [N, dimension]
  """
  m = np.amax(x, axis=(0, 1))
  ret = np.exp(x - m) / np.sum(np.exp(x - m), axis=1, keepdims=True)
  return ret
