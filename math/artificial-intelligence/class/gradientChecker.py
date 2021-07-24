import neuralnet
import sys

config = {}
# The length of list denotes number of hidden layers; each element denotes number of neurons in that layer; first element is the size of input layer, last element is the size of output layer.
config['layer_specs'] = [784, 100, 100, 10]
config['activation'] = 'sigmoid'  # Takes values 'sigmoid', 'tanh' or 'ReLU'; denotes activation function for hidden layers
config['batch_size'] = 1000  # Number of training samples per batch to be passed to network
config['epochs'] = 50  # Number of epochs to train the model
config['early_stop'] = True  # Implement early stopping or not
config['early_stop_epoch'] = 5  # Number of epochs for which validation loss increases to be counted as overfitting
config['L2_penalty'] = 0  # Regularization constant
config['momentum'] = False  # Denotes if momentum is to be applied or not
config['momentum_gamma'] = 0.9  # Denotes the constant 'gamma' in momentum expression
config['learning_rate'] = 0.0005  # Learning rate of gradient descent algorithm


class GradientChecker:

  def __init__(self, model, X_sample, y_sample):
    self.model = model
    self.X_sample = X_sample
    self.y_sample = y_sample

  def test_weight(self, l, i, j):
    model = self.model
    X_sample = self.X_sample
    y_sample = self.y_sample

    print("")
    print("Weight [{},{}]".format(i, j))

    # Calculate w - e, w + e
    epsilon = 1e-2
    w = l.w[i, j]
    w1 = w - epsilon
    w2 = w + epsilon

    # Calculate loss for (w - e) and (w + e)
    l.w[i, j] = w1
    _, l1, _ = model.forward_pass(X_sample, y_sample)
    l.w[i, j] = w2
    _, l2, _ = model.forward_pass(X_sample, y_sample)
    l.w[i, j] = w  # Set back to original value
    _, lorig, _ = model.forward_pass(X_sample, y_sample)

    print("Weight w: {}".format(w))
    print("Epsilon eps: {}".format(epsilon))
    print("Weight w - eps: {}".format(w1))
    print("Weight w + eps: {}".format(w2))
    print("Loss original: {}".format(lorig))
    print("Loss w - eps: {}".format(l1))
    print("Loss w + eps: {}".format(l2))
    diff = (l2 - l1) / (2 * epsilon)
    print("Gradient dE/dw numerically: {}".format(diff))
    delta = -l.d_w[i, j]  # Neuralnetwork stores gradient negative
    print("Gradient dE/dw backprop: {}".format(delta))
    print("Difference numeric and backprop gradient: {}".format(diff - delta))
    print("Difference within +/- eps^2?: {}".format(abs(diff - delta) < epsilon ** 2))
    if not abs(diff - delta) < epsilon ** 2:
      raise Exception("Gradient doesn't match")
      print("----------------------------")
      print("ERROR: GRADIENT NOT MATCHING")
      print("----------------------------")
    print("")

  def test_bias(self, l, i):
    model = self.model
    X_sample = self.X_sample
    y_sample = self.y_sample

    print("")
    print("Bias Weight [{}]".format(i))

    # Calculate b - e, b + e
    epsilon = 1e-3
    b = l.b[0, i]
    b1 = b - epsilon
    b2 = b + epsilon

    # Calculate loss for (b - e) and (b + e)
    l.b[0, i] = b1
    _, l1, _ = model.forward_pass(X_sample, y_sample)
    l.b[0, i] = b2
    _, l2, _ = model.forward_pass(X_sample, y_sample)
    l.b[0, i] = b  # Set back to original value
    _, lorig, _ = model.forward_pass(X_sample, y_sample)

    print("Bias Weight b: {}".format(b))
    print("Epsilon eps: {}".format(epsilon))
    print("Weight - eps: {}".format(b1))
    print("Weight + eps: {}".format(b2))
    print("Loss original: {}".format(lorig))
    print("Loss b - eps: {}".format(l1))
    print("Loss b + eps: {}".format(l2))
    diff = (l2 - l1) / (2 * epsilon)
    print("Gradient dE/dw numerically: {}".format(diff))
    delta = -l.d_b[i]  # Neuralnetwork stores gradient negative
    print("Gradient dE/dw backprop: {}".format(delta))
    print("Difference numeric and backprop gradient: {}".format(diff - delta))
    print("Diff withn +/- eps^2: {}".format(abs(diff - delta) < epsilon ** 2))
    if not abs(diff - delta) < epsilon ** 2:
      raise Exception("Gradient doesn't match")
      print("----------------------------")
      print("ERROR: GRADIENT NOT MATCHING")
      print("----------------------------")
    print("")


if __name__ == "__main__":

  model = neuralnet.Neuralnetwork(config)

  # Load data
  train_data_fname = 'MNIST_train.pkl'
  valid_data_fname = 'MNIST_valid.pkl'
  test_data_fname = 'MNIST_test.pkl'

  X_train, y_train = neuralnet.load_data(train_data_fname)
  X_valid, y_valid = neuralnet.load_data(valid_data_fname)
  X_test, y_test = neuralnet.load_data(test_data_fname)

  # Train model for a few epochs
  batch = 1000
  epochs = 3
  m = X_train.shape[0] // batch
  print("Training started ({} epochs)".format(epochs))
  for i in range(epochs):
    print("Epoch {} started".format(i))
    for j in range(m):
      model.forward_pass(X_train[j*batch:(j + 1) * batch],
                         y_train[j * batch: (j + 1) * batch])
      model.backward_pass()
      model.update()

  print("Training finished ({} epochs)".format(epochs))
  print("")

  # Select one sample
  X_sample = X_train[0:1, :]
  y_sample = y_train[0:1, :]

  # Create Checker object
  checker = GradientChecker(model, X_sample, y_sample)

  # Do forward_pass on sample and then backward_pass to calculate gradient
  model.forward_pass(X_sample, y_sample)
  model.backward_pass()

  # Pick one output bias weight:
  output = model.layers[-1]
  print("Output bias:")
  checker.test_bias(output, 1)

  # Pick one hidden bias weight:
  hidden = model.layers[0]
  print("First hidden layer bias")
  checker.test_bias(hidden, 9)

  # Pick two hidden to output weights:
  print("Hidden to output weight")
  checker.test_weight(output, 3, 4)
  checker.test_weight(output, 4, 5)

  # Pick two input to hidden weights:
  print("Input to hidden weight")
  checker.test_weight(hidden, 2, 3)
  checker.test_weight(hidden, 6, 7)

  if len(sys.argv) > 1 and sys.argv[1] == "all":
    # Bias
    for k in reversed(range(len(model.layers))):
      l = model.layers[k]
      print("Layer {}".format(k))
      if isinstance(l, neuralnet.Layer):
        for i in range(l.b.shape[1]):
          checker.test_bias(l, i)

    # Weights
    l = model.layers[-3]
    for k in reversed(range(len(model.layers))):
      l = model.layers[k]
      print("Layer {}".format(k))
      if isinstance(l, neuralnet.Layer):
        for i in range(l.w.shape[0]):
          for j in range(l.w.shape[1]):
            checker.test_weight(l, i, j)
