import numpy as np
import pickle


def softmax(x):
  """
  Args :
    input value [1, dim]
  Returns :
    softmax [1, dim]
  """

  return output


def load_data(fname):
  """Read MNIST data from filname

  Args:
    minimum: file name

  Returns:
    images : [N, [1, dimI]]
    labels : [N, [1, dimO]]
  """
  f = open("data/" + fname,'rb')
  data = pickle.load(f)
  images = []
  labels = []
  for d in data:
    images.append(np.array(d[:-1]).reshape(1, -1))
    encoded = np.zeros(10).reshape(1, -1)
    encoded[0][int(d[-1]) - 1] = 1
    labels.append(encoded)

  images = np.asarray(images)
  labels = np.asarray(labels)
  return images, labels


class Activation:
  """
  Attributes:
    X
  """
  def __init__(self, activation_type = "sigmoid"):
    self.activation_type = activation_type
    self.X = None # Save the input 'x' for activation to this variable for computing gradients.
  
  def forward_pass(self, a):
    """
    Args:
      a: input as np array [1, dim]
    Returns:
      output as np array   [1, dim]
    """
    if self.activation_type == "sigmoid":
      return self.sigmoid(a)
    
    elif self.activation_type == "tanh":
      return self.tanh(a)
    
    elif self.activation_type == "ReLU":
      return self.relu(a)
  
  def backward_pass(self, delta):
    """
    Args:
    Returns:
    """
    if self.activation_type == "sigmoid":
      grad = self.grad_sigmoid()
    
    elif self.activation_type == "tanh":
      grad = self.grad_tanh()
    
    elif self.activation_type == "ReLU":
      grad = self.grad_ReLU()
    
    return grad * delta
      
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
    ret=[]
    for i in x:
      ret.append(0 if i < 0 else i)  
    return ret

  def grad_sigmoid(self):
    """TODO
    """
    return grad

  def grad_tanh(self):
    """TODO
    Write the code for gradient through tanh activation function that takes in a numpy array and returns a numpy array.
    """
    return grad

  def grad_ReLU(self):
    """TODO
    Write the code for gradient through ReLU activation function that takes in a numpy array and returns a numpy array.
    """
    return grad

class Layer():
  """
  Attributes
    A   : forward out [N, dimN]
    X   : forward in  [N, dimP]
    d_X : gradient x  [N, dimP]
    w   : weight      [dimP, dimN]
    d_w : gradient w  [dimP, dimN]
    b   : bias        [1, dimN]
    d_b : gradient b  [1, dimN]
  """
  def __init__(self, dimP, dimN):
    np.random.seed(42)
    self.w = np.random.randn(dimP, dimN)
    self.b = np.zeros((1, dimN)).astype(np.float32)
    self.X = None
    self.A = None
    self.d_X = None
    self.d_w = None
    self.d_b = None

  def forward_pass(self, X):
    """
    Args:
      X : input [N, dimP]
    Returns:
      output [N, dimN]
    """
    self.X = X
    self.A = np.matmul(X, self.w) + self.b
    return self.A
  
  def backward_pass(self, delta):
    """
    Args:
      delta : gradient from next layer (1, dimN)

    Returns:
      
    
    Write the code for backward pass. This takes in gradient from its next layer as input,
    computes gradient for its weights and the delta to pass to its previous layers.
    """
    self.d_X = delta
    
    return self.d_X

      
class Neuralnetwork():
  """
  Attributes
    X   : input [N, [1, dimI]]
    Y   : ouput [N, [1, dimO]]
  """
  def __init__(self, config):
    self.layers = []
    self.X = None
    self.Y = None
    self.targets = None  # Save the targets in forward_pass in this variable
    for i in range(len(config['layer_dims']) - 1):
      self.layers.append( Layer(config['layer_dims'][i], config['layer_dims'][i+1]) )
      if i < len(config['layer_dims']) - 2:
        self.layers.append(Activation(config['activation']))  
    
  def forward_pass(self, X, targets=None):
    """
    Args:
      X       : Inputs         [N, [1, dimI]]
      targets : Correct label  [N, [1, dimO]]
    Returns:
      loss :
      Y    : predicted label [N, [1, dimO]]
    """
    self.X = X
    for l in self.layers:
      X = l.forward_pass(X)
    self.Y = X
    loss = None
    if targets != None:
      loss = loss_func(targets, Y)
    return loss, self.Y

  def loss_func(self, Y, T):
    '''
    Args:
      Y : predicted label [N, [1, dimO]]
      T : actual label    [N, [1, dimO]]
    Returns:
      Cross Entropy Loss
    '''
    m = Y.shape[0]
    loss = 0
    for i in range(m):
      loss += np.dot(Y[i] * np.log(T[i])) + np.dot(1 - Y[i], np.log(1 - T[i]))

    return -loss / m
    
  def backward_pass(self):
    '''TODO
    implement the backward pass for the whole network. 
    hint - use previously built functions.
    '''
      

def trainer(model, X_train, Y_train, X_valid, Y_valid, config):
  """TODO
  Write the code to train the network. Use values from config to set parameters
  such as L2 penalty, number of epochs, momentum, etc.
  """
  
def test(model, X, T, config):
  """
  Args:
    X : [N, [1, dimI]]
    T : [N, [1, dimO]]
  Returns:
    accuracy with given model, config and data
  """
  loss, Y = model.forward_pass(X)

  N = X_test.shape[0]
  correct = 0
  for i in range(N):
    if np.argmax(Y[i]) == np.argmax(Y_test[i]):
      correct += 1

  return correct * 100 / N 

if __name__ == "__main__":
  train_data_fname = 'MNIST_train.pkl'
  valid_data_fname = 'MNIST_valid.pkl'
  test_data_fname = 'MNIST_test.pkl'
  
  config = {}
  config['layer_dims'] = [784, 100, 100, 10]  # number of hidden layers; first is input, last is output.
  config['activation'] = 'sigmoid' # Takes values 'sigmoid', 'tanh' or 'ReLU'; 
  config['batch_size'] = 1000  # Number of training samples per batch to be passed to network
  config['epochs'] = 50  # Number of epochs to train the model
  config['earlY_stop'] = True  # Implement early stopping or not
  config['early_stop_epoch'] = 5  # # of epoch for which validation loss increases to be counted as overfitting
  config['L2_penalty'] = 0  # Regularization constant
  config['momentum'] = False  # Denotes if momentum is to be applied or not
  config['momentum_gamma'] = 0.9  # Denotes the constant 'gamma' in momentum expression
  config['learning_rate'] = 0.0001 # Learning rate of gradient descent algorithm
  ### Train the network ###
  model = Neuralnetwork(config)
  X_train, Y_train = load_data(train_data_fname)
  X_valid, Y_valid = load_data(valid_data_fname)
  X_test, Y_test = load_data(test_data_fname)
  trainer(model, X_train, Y_train, X_valid, Y_valid, config)
  test_acc = test(model, X_test, Y_test, config)
  print(test_acc)

