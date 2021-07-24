import numpy as np
import matplotlib.pyplot as plt
import re
import random

import dataloader
import pca

# Task 2. a)


class LogisticRegressionBatch:

  def __init__(self, c0, c1, k=8, alpha=0.2, tr=0.6, vld=0.2):
    self.c0 = c0  # category c0 (as list of numpy arrays)
    self.c1 = c1  # category c1 (as list ofnumpy arrays)
    self.tr = tr  # proportion training set
    self.vld = vld  # proportion validation set
    self.pca = pca.PCA(k)
    self.k = k
    self.alpha = alpha

    self.train = []
    self.valid = []
    self.test = []
    self.lblTrain = []
    self.lblValid = []
    self.lblTest = []

  '''
  Splits whole data for class c0 and class c1 provided into
  training, validation and test set
  '''

  def split_sets(self):
    self.train = []
    self.valid = []
    self.test = []

    # Split images for category 0
    t, v, tst = self.random_select(self.c0)
    self.train += t
    self.valid += v
    self.test += tst
    self.lblTrain = [0] * len(t)
    self.lblValid = [0] * len(v)
    self.lblTest = [0] * len(tst)

    # Split images for category 1
    t, v, tst = self.random_select(self.c1)
    self.train += t
    self.valid += v
    self.test += tst
    self.lblTrain += [1] * len(t)
    self.lblValid += [1] * len(v)
    self.lblTest += [1] * len(tst)

    # Transform lists of numpy arrays into single numpy array
    self.train = np.stack(self.train, axis=0)
    self.valid = np.stack(self.valid, axis=0)
    self.test = np.stack(self.test, axis=0)

  '''
  Randomly select elements from list for training, validation and
  test set
  
  Returns: Triple containing list of training, validation and test data
           (training, validation, test)
  '''

  def random_select(self, c):
    # Copy list to keep original list unmodified
    c = list(c)

    # empty training, validation and test set
    training = []
    validation = []
    test = []

    # Calculate length of training, test and validation set
    l = len(c)
    lTr = int(l * self.tr)
    lVld = int(l * self.vld)
    lTst = l - lTr - lVld

    # Randomly select elements for training, test and validation set
    for i in range(0, lTr):
      r = random.randint(0, len(c) - 1)
      training.append(c.pop(r))

    for i in range(0, lVld):
      r = random.randint(0, len(c) - 1)
      validation.append(c.pop(r))

    test = c

    return training, validation, test

  '''
  Transform training, validation and test set using pca eigenvalues
  '''

  def transform_data(self):
    self.pcaTrain = np.zeros((self.train.shape[0], self.k + 1))
    self.pcaValid = np.zeros((self.valid.shape[0], self.k + 1))
    self.pcaTest = np.zeros((self.test.shape[0], self.k + 1))

    # Add a column of ones for w_0 bias
    self.pcaTrain[:, 0] = np.ones((self.pcaTrain.shape[0]))
    self.pcaValid[:, 0] = np.ones((self.pcaValid.shape[0]))
    self.pcaTest[:, 0] = np.ones((self.pcaTest.shape[0]))

    # Add the transformed images to training, valid and test set
    for i in range(0, self.train.shape[0]):
      self.pcaTrain[i, 1:] = self.pca.transform(self.train[i])
    for i in range(0, self.valid.shape[0]):
      self.pcaValid[i, 1:] = self.pca.transform(self.valid[i])
    for i in range(0, self.test.shape[0]):
      self.pcaTest[i, 1:] = self.pca.transform(self.test[i])

  '''
  Calculate y given weights w and input x
  
  Returns: Value of y (float)
  '''

  def y(self, w, x):
    wt = np.transpose(w)
    return 1 / (1 + np.exp(-wt @ x))

  '''
  Calculate average error in set s (with teaching labels lblS) given weights w
   
  Returns: Average error
  '''

  def error(self, w, s, lblS):
    if s.shape[0] != len(lblS):
      raise Exception("List s and lblS need to be of equal length")

    e = 0
    for i in range(0, len(s)):
      t = lblS[i]
      y = self.y(w, s[i])
      e -= t * np.log(y) + (1 - t) * np.log(1 - y)

    e = e / len(s)
    return e

  '''
  Calculate sum of gradients given weight w, input set s and teaching labels lblS
  
  Returns: sum of gradients
  '''

  def gradient(self, w, s, lblS):
    if s.shape[0] != len(lblS):
      raise Exception("List s and lblS need to be of equal length")

    de = np.zeros(self.k + 1)
    for i in range(0, len(s)):
      t = lblS[i]
      y = self.y(w, s[i])
      x = s[i]
      de -= (t - y) * x
    return de

  '''
  Perform logistic regression for a number of epoches
  
  Returns: Best error for validation set (emin) with corresponding weights (wmin) 
           and list of errors for validation (evalid) and
           training set (etrain) and weights (w) for epochs,
           accuracy based on test set and wmin weights, standard deviation based
           on test set error
           (emin, wmin, e, w, accuracy, variance)
  '''

  def train_regression(self, epochs=10):
    # Store all weights and errors during learning process
    w = [np.zeros(self.k + 1)]
    evalid = [self.error(w[-1], self.pcaValid, self.lblValid)]
    etrain = [self.error(w[-1], self.pcaTrain, self.lblTrain)]

    # Keep best error and corresponding weights
    wmin = np.zeros(self.k + 1)
    emin = evalid[0]

    for i in range(0, epochs):
      wnext = w[-1] - self.alpha * self.gradient(w[-1], self.pcaTrain, self.lblTrain)
      etrain.append(self.error(wnext, self.pcaTrain, self.lblTrain))
      enext = self.error(wnext, self.pcaValid, self.lblValid)
      evalid.append(enext)
      w.append(wnext)
      if enext < emin:
        emin = enext
        wmin = wnext

    # Evaluate accuracy after learning process
    correct = 0
    for i in range(len(self.pcaTest)):
      yhat = self.y(wmin, self.pcaTest[i])
      if int(yhat + 0.5) == self.lblTest[i]:
        correct += 1
    accuracy = correct / len(self.lblTest)

    return emin, wmin, evalid, etrain, w, accuracy

  '''
  Perform single training process run involving randomly splitting up data
  into training, validation and test set, performing gradient descent and
  analysing model accuracy

  Returns data from train_regression()
  '''

  def single_run(self):
    # Split into training, validation and test set
    self.split_sets()

    # Calculate PCA from training data
    self.pca.fit(self.train)

    # Transform training data
    self.transform_data()

    # Train logistic regression
    return self.train_regression()

  '''
  Start multi-run training process and display statistics
  '''

  def start(self, runs=5, plot=True):
    # Average errors over five runs
    avg_evalid = None
    avg_etrain = None
    avg_accuracy = 0
    for i in range(0, runs):
      emin, wmin, evalid, etrain, w, accuracy = self.single_run()
      w.append(wmin)
      evalid = np.stack(evalid, axis=0)
      etrain = np.stack(etrain, axis=0)
      avg_accuracy += accuracy
      if avg_evalid is None:
        avg_evalid = np.copy(evalid)
        avg_etrain = np.copy(etrain)
        all_etrain = np.zeros((runs, etrain.shape[0]))
        all_evalid = np.zeros((runs, evalid.shape[0]))
        all_accuracy = np.zeros((runs))
        all_etrain[0, :] = etrain
        all_evalid[0, :] = evalid
        all_accuracy[0] = accuracy
      else:
        avg_evalid += evalid
        avg_etrain += etrain
        all_evalid[i, :] = evalid
        all_etrain[i, :] = etrain
        all_accuracy[i] = accuracy

    # Calculate average
    avg_evalid /= runs
    avg_etrain /= runs
    avg_accuracy /= runs

    # Calculate standard deviation for loss function
    all_evalid = all_evalid - np.tile(avg_evalid, (runs, 1))
    all_etrain = all_etrain - np.tile(avg_etrain, (runs, 1))
    all_evalid = np.multiply(all_evalid, all_evalid)
    all_etrain = np.multiply(all_etrain, all_etrain)
    svalid = np.sqrt(np.sum(all_evalid, axis=0) / runs)
    strain = np.sqrt(np.sum(all_etrain, axis=0) / runs)

    # Calculate standard deviation for accuracy
    all_accuracy = all_accuracy - avg_accuracy
    all_accuracy = np.multiply(all_accuracy, all_accuracy)
    s_accuracy = np.sqrt(np.sum(all_accuracy, axis=0) / runs)

    if plot:
      # Print statistics
      print("Learning rate: " + str(self.alpha))
      print("k: " + str(self.k))
      print("Accuracy: {:.1f}% ({:.1f})".format(avg_accuracy * 100, s_accuracy * len(self.pcaTest)))
      # Plot figure
      for i in [2, 4, 8, 10]:
        y1 = avg_evalid[i] - svalid[i]
        y2 = avg_evalid[i] + svalid[i]
        plt.plot(i, y1, color='blue', marker='_')
        plt.plot(i, y2, color='blue', marker='_')
        plt.vlines(i, y1, y2, color='blue')
      for i in [2, 4, 8, 10]:
        y1 = avg_etrain[i] - strain[i]
        y2 = avg_etrain[i] + strain[i]
        plt.plot(i, y1, color='orange', marker='_')
        plt.plot(i, y2, color='orange', marker='_')
        plt.vlines(i, y1, y2, color='orange')
      plt.plot(avg_evalid, color='blue', label='Validation Set')
      plt.plot(avg_etrain, color='orange', label='Training Set')
      plt.xlabel("Epoch")
      plt.ylabel("Cross entropy loss E(w)")
      plt.title("Cross entropy loss by training epoch (" + str(runs) + " run average, " + str(self.k) + "-PCA)")
      plt.legend(loc='upper right')
      plt.show()

    return avg_etrain, strain


def happy_sad():
  print("Start happy sad analysis")

  # Load images
  images, labels = dataloader.load_data()

  # Extract emotion from labels
  t = []
  prefix = re.compile("^.*_")
  suffix = re.compile("[0-9]*\.pgm$")
  for i in range(0, len(labels)):
    l = labels[i]
    s = prefix.search(l).end()
    e = suffix.search(l).start()
    t.append(l[s:e])

  # Create list of tuples in format (image, label) of all images
  tupleImg = list(zip(images, t))

  # Filter happy and sad images
  sadImg = list(filter(lambda x: x[1] == "m", tupleImg))
  happyImg = list(filter(lambda x: x[1] == "h", tupleImg))

  # Remove labels from tuples to get list of images
  sadImg = list(map(lambda x: x[0], list(sadImg)))
  happyImg = list(map(lambda x: x[0], list(happyImg)))

  # Run logistic regression
  alpha = 0.05
  reg_k1 = LogisticRegressionBatch(sadImg, happyImg, k=1, alpha=alpha)
  reg_k1.start()

  reg_k2 = LogisticRegressionBatch(sadImg, happyImg, k=2, alpha=alpha)
  reg_k2.start()

  reg_k4 = LogisticRegressionBatch(sadImg, happyImg, k=4, alpha=alpha)
  reg_k4.start()

  reg_k8 = LogisticRegressionBatch(sadImg, happyImg, k=8, alpha=alpha)
  reg_k8.start()

  # Run logistic regression with different learning rates
  reg_k8_large = LogisticRegressionBatch(sadImg, happyImg, k=8, alpha=1)
  elarge, slarge = reg_k8_large.start(plot=False)

  reg_k8_medium = LogisticRegressionBatch(sadImg, happyImg, k=8, alpha=0.05)
  emedium, smedium = reg_k8_medium.start(plot=False)

  reg_k8_small = LogisticRegressionBatch(sadImg, happyImg, k=8, alpha=0.005)
  esmall, ssmall = reg_k8_small.start(plot=False)

  # Plot figure
  for i in [2, 4, 8, 10]:
    y1 = elarge[i] - slarge[i]
    y2 = elarge[i] + slarge[i]
    plt.plot(i, y1, color='blue', marker='_')
    plt.plot(i, y2, color='blue', marker='_')
    plt.vlines(i, y1, y2, color='blue')
  for i in [2, 4, 8, 10]:
    y1 = emedium[i] - smedium[i]
    y2 = emedium[i] + smedium[i]
    plt.plot(i, y1, color='orange', marker='_')
    plt.plot(i, y2, color='orange', marker='_')
    plt.vlines(i, y1, y2, color='orange')
  for i in [2, 4, 8, 10]:
    y1 = esmall[i] - ssmall[i]
    y2 = esmall[i] + ssmall[i]
    plt.plot(i, y1, color='green', marker='_')
    plt.plot(i, y2, color='green', marker='_')
    plt.vlines(i, y1, y2, color='green')

  plt.plot(elarge, color='blue', label='alpha = 1 (too large)')
  plt.plot(emedium, color='orange', label='alpha = 0.05 (best results)')
  plt.plot(esmall, color='green', label='alpha = 0.005 (too small)')
  plt.xlabel("Epoch")
  plt.ylabel("Cross entropy loss E(w) for training set")
  plt.title("Cross entropy loss by training epoch (" + str(5) + " run average, " + "8-PCA)")
  plt.legend(loc='upper right')
  plt.show()

# 2. c


def afraid_surprised():
  print("Start afraid surprised analysis")

  # Load images
  images, labels = dataloader.load_data()

  # Extract emotion from labels
  t = []
  prefix = re.compile("^.*_")
  suffix = re.compile("[0-9]*\.pgm$")
  for i in range(0, len(labels)):
    l = labels[i]
    s = prefix.search(l).end()
    e = suffix.search(l).start()
    t.append(l[s:e])

  # Create list of tuples in format (image, label) of all images
  tupleImg = list(zip(images, t))

  # Filter fear and surprise images
  fearImg = list(filter(lambda x: x[1] == "f", tupleImg))
  surpriseImg = list(filter(lambda x: x[1] == "s", tupleImg))

  # Remove labels from tuples to get list of images
  fearImg = list(map(lambda x: x[0], list(fearImg)))
  surpriseImg = list(map(lambda x: x[0], list(surpriseImg)))

  # Run logistic regression
  alpha = 0.05
  reg_k8 = LogisticRegressionBatch(fearImg, surpriseImg, k=8, alpha=alpha)
  reg_k8.start()


def main():
  happy_sad()
  afraid_surprised()


main()
