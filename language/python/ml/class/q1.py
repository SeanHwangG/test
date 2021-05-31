import numpy as np
import matplotlib.pyplot as plt
from PIL import Image

import dataloader
import pca

images, labels = dataloader.load_data()

# 1. a)

'''
The validation and test set are used to evaluate the training process and
optimize training parameters. The training process is affected by the PCA
transformation and would therefore not be independent from the data in the
validation and test set if these sets were included in the PCA transformation.
To guarantee an independent evaluation of the training process, validation and
test data must not influence the PCA transformation.
'''

# 1. b)

print("Show six different emotions from image set")

# Six selected emotions from image set
six_images = images[0]
six_images = np.hstack((six_images, images[1]))
six_images = np.hstack((six_images, images[2]))
six_images = np.hstack((six_images, images[3]))
six_images = np.hstack((six_images, images[5]))
six_images = np.hstack((six_images, images[6]))

# Display six images with different images
plt.imshow(six_images, cmap='gray')
plt.title('Six different emotions from image set')
plt.show()

# 1. c)

# Code for this section has been copied from example code

# Fit PCA
pca = pca.PCA(k=50)
pca.fit(np.array(images[:]))

# Display first 6 eigenvectors
pca.display()
plt.show()
