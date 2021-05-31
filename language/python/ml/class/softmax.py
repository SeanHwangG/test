import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
import seaborn as sn
import re
import random

from dataloader import *
from pca import *


class Softmax:
  '''
  Initialize all class variable
  '''

  def __init__(self, people, k, alpha=0.1, tr=0.8, vld=0.1, stoc=False, EC=False):
    self.people = people
    self.k = k
    self.tr = tr
    self.vld = vld
    self.pca = PCA(k)
    self.alpha = alpha
    self.stoc = stoc
    self.EC = EC
    self.nLabel = (8 if EC else 6)

  '''
  split training, validation, test data by people
  '''

  def split_people(self, people):
    self.trainX = []
    self.trainX = []
    self.trainY = []
    self.validX = []
    self.validY = []
    self.testX = []
    self.testY = []

    for key in people:
      l = people[key]
      random.shuffle(l)
      for i in range(6):
        for t in l[i]:
          self.trainX.append(t[0])
          self.trainY.append(t[1])
      for t in l[6]:
        self.validX.append(t[0])
        self.validY.append(t[1])
      for t in l[7]:
        self.testX.append(t[0])
        self.testY.append(t[1])

    # Calculate length of training, test and validation set
    # Randomly select elements for training, test and validation set
    self.trainX = np.array(self.trainX)
    self.trainY = np.array(self.trainY)
    self.validX = np.array(self.validX)
    self.validY = np.array(self.validY)
    self.testX = np.array(self.testX)
    self.testY = np.array(self.testY)

  ''' 
  split training, validation, test data by emotion
  '''

  def split_emotions(self, people):
    people = dict(people)

    self.trainX = []
    self.trainY = []
    self.validX = []
    self.validY = []
    self.testX = []
    self.testY = []

    l = len(self.people)
    lTr = int(l * self.tr)
    lVld = lTr + int(l * self.vld)

    keys = list(self.people.keys())
    random.shuffle(keys)

    for i in range(len(keys)):
      if i < lTr:
        for j in range(len(people[keys[i]])):
          self.trainX.append(people[keys[i]][j][0])
          self.trainY.append(people[keys[i]][j][1])
      elif i < lVld:
        for j in range(len(people[keys[i]])):
          self.validX.append(people[keys[i]][j][0])
          self.validY.append(people[keys[i]][j][1])
      else:
        for j in range(len(people[keys[i]])):
          self.testX.append(people[keys[i]][j][0])
          self.testY.append(people[keys[i]][j][1])

    # Calculate length of training, test and validation set
    # Randomly select elements for training, test and validation set
    self.trainX = np.array(self.trainX)
    self.trainY = np.array(self.trainY)
    self.validX = np.array(self.validX)
    self.validY = np.array(self.validY)
    self.testX = np.array(self.testX)
    self.testY = np.array(self.testY)

  '''
  Train PCA only using training data and apply to every set
  '''

  def transform_data(self):
    self.pcaTrainX = np.zeros((self.trainX.shape[0], self.k))
    self.pcaValidX = np.zeros((self.validX.shape[0], self.k))
    self.pcaTestX = np.zeros((self.testX.shape[0], self.k))

    # Add constant one in first column for x_0
    self.pcaTrainX[:, 0] = np.ones((self.pcaTrainX.shape[0]))
    self.pcaValidX[:, 0] = np.ones((self.pcaValidX.shape[0]))
    self.pcaTestX[:, 0] = np.ones((self.pcaTestX.shape[0]))

    for i in range(0, self.trainX.shape[0]):
      self.pcaTrainX[i, 0:] = self.pca.transform(self.trainX[i])
    for i in range(0, self.validX.shape[0]):
      self.pcaValidX[i, 0:] = self.pca.transform(self.validX[i])
    for i in range(0, self.testX.shape[0]):
      self.pcaTestX[i, 0:] = self.pca.transform(self.testX[i])

  '''
  Calculate average error in set s (with teaching labels lblS) given weights w
  
  Returns: Average error
  '''

  def loss(self, W, X, Y):
    e = 0
    for i in range(X.shape[0]):
      yhat = self.yhat(W, X[i])
      e -= np.log(yhat) @ Y[i]
    return e / X.shape[0]

  '''
  Returns : (6, 1) probability for one input
  '''

  def yhat(self, W, x):
    logit = np.exp(np.matmul(W, x))
    logit /= np.sum(logit)
    return logit

  '''
  Returns : (8, k) gradient of weight
  '''

  def gradient(self, W, X, Y):
    dW = np.zeros(W.shape)
    for i in range(X.shape[0]):
      dW += np.matmul((self.yhat(W, X[i]) - Y[i]).reshape(-1, 1), X[i].reshape(1, -1))
    return dW

  def singleGradient(self, W, x, y):
    return np.matmul((self.yhat(W, x) - y).reshape(-1, 1), x.reshape(1, -1))

  #
  # Compare training loss between Stochiastic and Batch Gradient descent
  #
  def compStoc(self, runs=5):
    bTrain = []
    sTrain = []
    for i in range(0, runs):
      _, _, _, btrain, _, _ = self.batchSoftmax()
      strain = self.stochSoftmax()
      bTrain.append(btrain)
      sTrain.append(strain)
    bTrain = np.array([sum(x) for x in zip(*bTrain)])
    sTrain = np.array([sum(x) for x in zip(*sTrain)])

    # Plot figure
    plt.plot(bTrain, color='blue', label='batch Softmax')
    plt.plot(sTrain, color='orange', label='Stochastic Softmax')
    plt.xlabel("Epoch")
    plt.ylabel("Cross entropy loss E(w)")
    plt.title("Cross entropy loss by training epoch (" + str(runs) + " run average, " + str(self.k) + "-PCA)")
    plt.legend(loc='upper right')
    plt.show()

  '''
  Return : training losses for stochastic gradient descent
  '''

  def stochSoftmax(self, epochs=20):
    # Split into training, validation and test set
    self.split_emotions(self.people)
    self.pca.fit(self.trainX)
    self.transform_data()

    # Store all weights and errors during learning process
    W = [np.zeros((6, self.k))]
    trainE = [self.loss(W[-1], self.pcaTrainX, self.trainY)]

    for i in range(0, epochs):
      nextW = W[-1]
      for j in np.random.permutation(self.pcaTrainX.shape[0]):
        nextW -= self.alpha * self.singleGradient(W[-1], self.pcaTrainX[j], self.trainY[j])
      trainE.append(self.loss(nextW, self.pcaTrainX, self.trainY))
      W.append(nextW)

    return trainE

  '''
  Return : minimum error, correspoding weight, validation error, all weight, accuracy
  '''

  def batchSoftmax(self, epochs=20):
    # Split into training, validation and test set
    if self.EC == True:
      self.split_people(self.people)
    else:
      self.split_emotions(self.people)

    self.split_emotions(self.people)
    self.pca.fit(self.trainX)
    self.transform_data()

    # Store all weights and errors during learning process
    W = [np.zeros((self.nLabel, self.k))]
    validE = [self.loss(W[-1], self.pcaValidX, self.validY)]
    trainE = [self.loss(W[-1], self.pcaTrainX, self.trainY)]

    # Keep best error and corresponding weights
    minW = W[0]
    minE = validE[0]

    for i in range(0, epochs):
      nextW = W[-1] - self.alpha * self.gradient(W[-1], self.pcaTrainX, self.trainY)
      nextE = self.loss(nextW, self.pcaValidX, self.validY)

      trainE.append(self.loss(nextW, self.pcaTrainX, self.trainY))
      validE.append(nextE)
      W.append(nextW)

      if nextE < minE:
        minE = nextE
        minW = nextW

    correct = 0
    for i in range(self.testX.shape[0]):
      if np.argmax(self.yhat(minW, self.pcaTestX[i])) != np.argmax(self.testY[i]):
        correct += 1
    accuracy = correct / len(self.testY)

    return minE, minW, validE, trainE, W, accuracy

  '''
  Run bach softmax 5 times and plot graph
  '''

  def start(self, runs=5):
    avg_evalid = None
    avg_etrain = None
    avg_accuracy = 0
    best = 100
    Wmin = None
    for i in range(0, runs):
      emin, wmin, evalid, etrain, w, accuracy = self.batchSoftmax()

      if emin < best:
        best = emin
        Wmin = wmin
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

    confusion = []

    for x in self.pcaTestX:
      confusion.append(self.yhat(Wmin, x))

    df_cm = pd.DataFrame(confusion, index=[i for i in range(self.nLabel)],
                         columns=[j for j in range(self.nLabel)])

    plt.figure(figsize=(10, 7))

    sn.heatmap(df_cm, annot=True)
    plt.show()

    # Calculate average
    avg_evalid /= runs
    avg_etrain /= runs
    avg_accuracy /= runs

    # Calculate standard deviation
    all_evalid = all_evalid - np.tile(avg_evalid, (runs, 1))
    all_etrain = all_etrain - np.tile(avg_etrain, (runs, 1))
    all_evalid = np.multiply(all_evalid, all_evalid)
    all_etrain = np.multiply(all_etrain, all_etrain)
    strain = np.sqrt(np.sum(all_etrain, axis=0) / runs)
    svalid = np.sqrt(np.sum(all_evalid, axis=0) / runs)

    # Calculate standard deviation for accuracy
    all_accuracy = all_accuracy - avg_accuracy
    all_accuracy = np.multiply(all_accuracy, all_accuracy)
    s_accuracy = np.sqrt(np.sum(all_accuracy, axis=0) / runs)

    print("alpha " + str(self.alpha))
    print("accuracy " + str(avg_accuracy * 100) + "%")
    print("STV" + str(s_accuracy * len(self.testY)))
    print("k " + str(self.k))

    # Plot figure
    for i in [5, 10, 15, 20]:
      y1 = avg_evalid[i] - svalid[i]
      y2 = avg_evalid[i] + svalid[i]
      plt.plot(i, y1, color='blue', marker='_')
      plt.plot(i, y2, color='blue', marker='_')
      plt.vlines(i, y1, y2, color='blue')
    for i in [5, 10, 15, 20]:
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
    for i in range(self.nLabel):
      inverse = self.pca.inverse_transform(Wmin[i])
      plt.imshow(inverse.reshape(np.array(self.trainX[0]).shape), cmap='gray')
      plt.show()


def main():
  images, labels = load_data()
  prefix = re.compile("^.*_")
  suffix = re.compile("[0-9]*\.pgm$")
  people = {}

  # makes confusion matrix 1 in diagonoal
  faces = ["a", "d", "f", "ht", "m", "s"]
  labels, images = zip(*sorted(zip(labels, images)))

  # Store images by person
  for i in range(0, len(labels)):
    s = prefix.search(labels[i]).end()
    e = suffix.search(labels[i]).start()
    p = labels[i][:s - 1]

    # we don't use neutral and happy face
    if labels[i][s:e] == "n" or labels[i][s:e] == "h":
      continue

    y = np.zeros(6)
    y[faces.index(labels[i][s:e])] = 1

    if p not in people:
      people[p] = [[images[i], y]]
    else:
      people[p].append([images[i], y])

  sm_k8 = Softmax(people, 8, alpha=0.1)
  sm_k8.start(50)
  # for k in [4, 8, 16, 32]:
  #   sm_k8 = Softmax(people, k, alpha = 0.05)
  #   sm_k8.start()
  # sm_k8.compStoc()


def mainEC():
  images, labels = load_data()
  prefix = re.compile("^.*_")
  suffix = re.compile("[0-9]*\.pgm$")
  people = {}

  # makes confusion matrix 1 in diagonoal
  faces = ["a", "d", "f", "h", "ht", "m", "n", "s"]
  labels, images = zip(*sorted(zip(labels, images)))

  for i in range(0, len(labels)):
    s = prefix.search(labels[i]).end()
    e = suffix.search(labels[i]).start()
    p = labels[i][:s - 1]

    y = np.zeros(8)
    y[faces.index(labels[i][s:e])] = 1

    if p not in people:
      people[p] = [[images[i], y]]
    else:
      people[p].append([images[i], y])

  sm_k8 = Softmax(people, 8, alpha=0.04, EC=True)
  sm_k8.start()


main()
mainEC()
