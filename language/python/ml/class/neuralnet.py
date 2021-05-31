"""
Class:
  Activation
  Layer
  Neuralnetwork

Autor:
  Gyuseung Hwang
  Simon Kaufmann
"""

import copy
import matplotlib.pyplot as plt
import numpy as np
import pickle

def softmax(x):
  """
  Args :
    input value [N, dim]
  Returns :
    softmax [N, dim]
  """
  m = np.amax(x, axis=(0,1))
  ret = np.exp(x - m) / np.sum(np.exp(x - m), axis=1, keepdims=True)
  return ret

def load_data(fname):
  """Read MNIST data from filname

  Args:
    minimum: file name

  Returns:
    images : [N, dimI]
    labels : one encoded [N, dimO]
  """
  f = open("data/" + fname,'rb')
  data = pickle.load(f)
  images = []
  labels = []
  for d in data:
    images.append(np.array(d[:-1]))
    encoded = np.zeros(10)
    encoded[int(d[-1]) - 1] = 1
    labels.append(encoded)

  images = np.asarray(images)
  labels = np.asarray(labels)
  return images, labels

class Activation:
  """
  Attributes:
    x : [dim]
    activation_type : sigmoid, tanh, ReLU
  """
  def __init__(self, activation_type = "sigmoid"):
    self.activation_type = activation_type
    self.x = None
  
  def forward_pass(self, a):
    """
    Args:
      a: input as np array [dim]
    Returns:
      output as np array   [dim]
    """
    if self.activation_type == "sigmoid":
      return self.sigmoid(a)

    elif self.activation_type == "tanh":
      return self.tanh(a)

    elif self.activation_type == "ReLU":
      return self.ReLU(a)
  
  def backward_pass(self, d_a):
    """
    Args:
      d_a : np array [dim]
    Returns:
      np array with gradient
    """
    if self.activation_type == "sigmoid":
      grad = self.grad_sigmoid()
    elif self.activation_type == "tanh":
      grad = self.grad_tanh()
    elif self.activation_type == "ReLU":
      grad = self.grad_ReLU()
    
    return d_a * grad

  def sigmoid(self, x):
    """ save input and return sigmoid np array
    """
    self.x = x
    return 1/(1+np.exp(-x))

  def tanh(self, x):
    """ save input and return tanh np array
    """
    self.x = x
    return np.tanh(x)

  def ReLU(self, x):
    """ save input and return relu np array
    """
    self.x = x

    return np.maximum(x, 0)

  def grad_sigmoid(self):
    """ return gradient for sigmoid
    """
    f = 1 /(1 + np.exp(-self.x))

    return f * (1 - f)

  def grad_tanh(self):
    """ return gradient for tanh
    """ 
    return 1 - np.power(np.tanh(self.x), 2)

  def grad_ReLU(self):
    """ return gradient for ReLu
    """
    return np.greater(self.x, 0).astype(int)


class Layer():
  """
  Attributes
    x     : forward in  [N, dimI]
    d_x   : gradient x  [N, dimI]
    a     : forward out [N, dimO]
    w     : weight      [dimI, dimO]
    d_w   : gradient w  [dimI, dimO]
    b     : bias        [N, dimO]
    d_b   : gradient b  [N, dimO]
    alpha : learning rate
    gamma : momentum gamma
    L2    : L2 penalty

    v_dw  : gradient w with momentum
    v_db  : gradient b with momentum
  """
  def __init__(self, dimI, dimO, config):
    np.random.seed(42)
    self.w = np.random.randn(dimI, dimO)
    if config.get('scale_weight', False):
      self.w /= (dimI + dimO)
    self.b = np.zeros((1, dimO)).astype(np.float32)
    self.x = None
    self.a = None
    self.d_x = None
    self.d_w = None
    self.d_b = None
    self.gamma = config.get('momentum_gamma', 0.9)
    self.L2 = config.get('L2_penalty', 0)

    self.vd_w = np.zeros((dimI, dimO))
    self.vd_b = np.zeros((1, dimO)).astype(np.float32)

  def forward_pass(self, x):
    """
    Args:
      x : input [N, dimI]
    Returns:
      output [N, dimO]
    """
    self.x = x
    self.a = np.matmul(x, self.w) + self.b
    return self.a
  
  def backward_pass(self, d_a):
    """
    Args:
      d_a : gradient from next layer (N, dimO)
    Returns:
      computes gradient for its weights and the d_a to pass to its previous layers.
    """
    m = d_a.shape[0]
    self.d_w = self.x.T @ d_a
    self.d_x = (d_a @ self.w.T)
    self.d_b = np.sum(d_a, axis=0)
    self.vd_w = self.vd_w * self.gamma + self.d_w
    self.vd_b = self.vd_b * self.gamma + self.d_b
    
    return self.d_x

class Neuralnetwork():
  """
  Attributes
    layers : [Layer -> (Activation -> Layer)]
    x      : input  [N, dimI]
    y      : ouput  [N, dimO]
    t      : target [N, dimO]
    alpha  : learning reate
  """
  def __init__(self, config):
    self.layers = []
    self.x = None
    self.y = None
    self.t = None
    self.alpha = config.get('learning_rate', 1)
    for i in range(len(config['layer_specs']) - 1):
      self.layers.append( Layer(config['layer_specs'][i], config['layer_specs'][i+1], config))
      if i < len(config['layer_specs']) - 2:
        self.layers.append(Activation(config['activation']))  
    
  def forward_pass(self, x, targets=None):
    """
    Args:
      x : Inputs         [N, dimI]
      t : Correct label  [N, dimO]
    Returns:
      y     : predicted label [N, dimO]
      loss  :
      error :
    """

    self.x = x
    i = 0
    for l in self.layers:
      i += 1
      x = l.forward_pass(x)
    self.y = softmax(x)

    loss = None
    if targets is None:
      return self.y
    self.t = targets
    loss, error = self.loss_func(self.y, targets)

    return self.y, loss, error

  def loss_func(self, y, t):
    '''
    Args:
      y : predicted label [N, dimO]
      t : actual label    [N, dimO]
    Returns:
      Cross Entropy Loss
    '''
    eps = 1e-15
    N = y.shape[0]
    correct = 0

    for i in range(N):
      if np.argmax(y[i]) == np.argmax(t[i]):
        correct += 1

    loss = -np.sum(t * np.log(y + eps)) / self.x.shape[0]
    error = correct * 100 / N
    return loss, error

  def backward_pass(self):
    """ backward pass for the whole network. 
    """
    d_a = self.t - self.y
    for l in reversed(self.layers):
      d_a = l.backward_pass(d_a)

  def update(self):
    """ update layers using calculated gradient
    """
    for l in self.layers:
        if isinstance(l, Layer):
          l.x += l.d_x * self.alpha
          l.w += l.vd_w * self.alpha - l.w * l.L2
          l.b += l.vd_b * self.alpha

def trainer(model, x_train, y_train, x_valid, y_valid, x_test, y_test, config):
  """ Train the network, using config to set parameters
  Args:
    x_train : [N, dimI]
    y_train : [N, dimO]
  Returns:
    Accuracy for test set when the validation loss is minimum
  """
  batch = config['batch_size']
  epochs = config['epochs']
  earlyStop = config.get('early_stop', False)
  stopEpoch = config.get('early_stop_epoch', 5)
  trainLoss = []
  validLoss = []
  trainError = []
  validError = []
  weights = []
  done = False
  top = 0

  m = x_train.shape[0] // batch
  for i in range(epochs):
    print("Epoch " + str(i) + " started")
    indices = np.arange(m * batch)
    np.random.shuffle(indices)
    if done == True:
      break

    for j in range(m):
      t_y, t_l, t_e = model.forward_pass(x_train[indices[j*batch:(j + 1) * batch]],
                                         y_train[indices[j * batch: (j + 1) * batch]])
      model.backward_pass()
      model.update()

    s_y, s_l, s_e = model.forward_pass(x_test, y_test)
    v_y, v_l, v_e = model.forward_pass(x_valid, y_valid)
    # if we use early stopping
    if earlyStop:
      if len(validLoss) > 0 and v_l < validLoss[-1]:
        top = s_e
      if stopEpoch <= len(validLoss) and v_l > validLoss[-stopEpoch]:
        done = True
        break
    validLoss.append(v_l)
    validError.append(v_e)
    trainLoss.append(t_l)
    trainError.append(t_e)
    print(v_e, s_e)

  plt.plot(trainLoss, color='blue', label='trainLoss')
  plt.plot(validLoss, color='orange', label='validLoss')
  plt.xlabel("Epochs")
  plt.ylabel("Cross Entropy loss E(w)")
  plt.title("Cross Entropy loss for train and validation")
  plt.show()

  plt.plot(trainError, color='blue', label='trainError')
  plt.plot(validError, color='orange', label='validError')
  plt.xlabel("Epochs")
  plt.ylabel("Percent Correct")
  plt.title("Accuracy for train and validation [best Test :" + str(top) + "%]")
  plt.show()

  return top

def test(model, x, t, config):
  """
  Args:
    x : [N, dimI]
    t : [N, dimO]
  Returns:
    accuracy with given model, config and data
  """
  N = x_test.shape[0]
  correct = 0

  y = model.forward_pass(x)
  for i in range(N):
    if np.argmax(y[i]) == np.argmax(t[i]):
      correct += 1

  return correct * 100 / N 

if __name__ == "__main__":
  train_data_fname = 'MNIST_train.pkl'
  valid_data_fname = 'MNIST_valid.pkl'
  test_data_fname = 'MNIST_test.pkl'
  
  configB = {}
  configB['layer_specs'] = [784, 100, 100, 10]
  configB['activation'] = 'tanh'
  configB['batch_size'] = 1000
  configB['epochs'] = 100

  configC = copy.deepcopy(configB)
  configC['learning_rate'] = 0.00004
  configC['layer_specs'] = [784, 50, 50, 10]
  configC['early_stop'] = True
  configC['early_stop_epoch'] = 5
  configC['momentum'] = True
  configC['momentum_gamma'] = 0.9

  # randomize weight + 10% more epochs
  configD1 = copy.deepcopy(configC)
  configD2 = copy.deepcopy(configC)
  configD2['scale_weight'] = True

  # 
  configE1 = copy.deepcopy(configC)
  configE2 = copy.deepcopy(configC)
  configE1['scale_weight'] = True
  configE1['L2_penalty'] = 0
  configE1['learning_rate'] = 0.00004
  configE1['activation'] = 'ReLU'
  configE2['scale_weight'] = True
  configE2['L2_penalty'] = 0.001 * 50000
  configE2['activation'] = 'sigmoid'

  #
  configF1 = copy.deepcopy(configC)
  configF2 = copy.deepcopy(configC)
  configF1['layer_specs'] = [784, 50, 10]
  configF2['layer_specs'] = [784, 50, 50, 50, 50, 10]

  # WHAT QUESTION ARE YOU ON
  config = configE1

  ### Train the network ###
  model = Neuralnetwork(config)
  x_train, y_train = load_data(train_data_fname)
  x_valid, y_valid = load_data(valid_data_fname)
  x_test, y_test = load_data(test_data_fname)

  top = (trainer(model, x_train, y_train, x_valid, y_valid, x_test, y_test, config))
  print("Best Test Result " + str(top))
  train_acc = test(model, x_train, y_train, config)
  valid_acc = test(model, x_valid, y_valid, config)
  test_acc = test(model, x_test, y_test, config)

  config = configD2

  ### Train the network ###
  model = Neuralnetwork(config)
  x_train, y_train = load_data(train_data_fname)
  x_valid, y_valid = load_data(valid_data_fname)
  x_test, y_test = load_data(test_data_fname)

  top = (trainer(model, x_train, y_train, x_valid, y_valid, x_test, y_test, config))
  print("Best Test Result " + str(top))
  train_acc = test(model, x_train, y_train, config)
  valid_acc = test(model, x_valid, y_valid, config)
  test_acc = test(model, x_test, y_test, config)
