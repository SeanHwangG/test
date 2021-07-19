{% tabs %}
{% tab title='HR_the-captcha-cracker.md' %}

> Question

* print a line containing a 5-character token representing the Captcha's text

```txt
Input:
3 3
0,0,200 0,0,10 10,0,0
90,90,50 90,90,10 255,255,255
100,100,88 80,80,80 15,75,255
Output: VSDFD
```

{% endtab %}
{% tab title='HR_the-captcha-cracker.py' %}

```py
import sys
import numpy
import base64
import pickle
import zlib

serialized = "eNosuHV41Ngf9g0UtyKLtoV6R..."

def sigmoid(x):
  return 1 / (1 + numpy.exp(-x))

def softmax(x):
  e = numpy.exp(x)
  return e / numpy.sum(e, axis=1)[:, None]

def predict(theta1, theta2, X):
  X = numpy.insert(X, 0, 1, axis=1)
  hidden_layer = sigmoid(numpy.dot(X, numpy.transpose(theta1)))
  hidden_layer = numpy.insert(hidden_layer, 0, 1, axis=1)
  Y_predict = softmax(numpy.dot(hidden_layer, numpy.transpose(theta2)))
  return numpy.argmax(Y_predict, axis=1)

def to_monochrome(pixels, rows, cols):
  scale, monochrome = 2, numpy.zeros(shape=(rows/scale, cols/scale))
  for i in range(rows / scale):
    for j in range(cols / scale):
      pixel = numpy.array([0, 0, 0])
      for k in range(scale):
        if (i * scale) + k >= rows:
          continue
        for l in range(scale):
          if (j * scale) + l >= cols:
            continue
          pixel = numpy.maximum(pixel, numpy.array(map(int, pixels[(i*scale)+k][(j*scale)+l].split(","))))
      r, g, b = pixel
      monochrome[i, j] = 1.0 - ((0.0 + r + g + b) / 765)
  return monochrome[:, :]


input_layer_size, hidden_layer_size, nn_params = pickle.loads(zlib.decompress(base64.b64decode(serialized)))
num_labels = 26

t1_len = (input_layer_size+1)*hidden_layer_size
theta1 = nn_params[:t1_len].reshape(hidden_layer_size, input_layer_size+1)
theta2 = nn_params[t1_len:].reshape(num_labels, hidden_layer_size+1)

rows, cols = map(int, sys.stdin.readline().split())
pixels = [sys.stdin.readline().split() for r in range(rows)]
monochromeShift = to_monochrome(pixels, rows, cols)

features = numpy.asarray([
  monochromeShift[:, 0:19].flatten(),
  monochromeShift[:, 16:35].flatten(),
  monochromeShift[:, 33:52].flatten(),
  monochromeShift[:, 50:69].flatten(),
  monochromeShift[:, 66:85].flatten()])

targets_predict = predict(theta1, theta2, features)
print("".join(chr(targets_predict[0] + ord('A')) for i in range(5)))
```

{% endtab %}
{% endtabs %}
