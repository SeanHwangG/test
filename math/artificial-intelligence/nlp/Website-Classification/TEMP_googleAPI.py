# sudo pip install google-cloud-vision
# Udates PATH for the Google Cloud SDK.
# gcloud auth application-default login and login to the google account

import io
import os

# Imports the Google Cloud client library
#from google.cloud import vision

'''
def detect_safe_search_uri(uri):
    """Detects unsafe features in the file located in Google Cloud Storage or
    on the Web."""
    vision_client = vision.Client()
    image = vision_client.image(source_uri=uri)

    safe = image.detect_safe_search()
    print('adult: {}'.format(safe.adult))
    print('medical: {}'.format(safe.medical))
    print('spoofed: {}'.format(safe.spoof))
    print('violence: {}'.format(safe.violence))
'''


file_name = '/Users/wk/Desktop/checkSafeContent/images/5.png'

vision_client = vision.Client()

with io.open(file_name, 'rb') as image_file:
    content = image_file.read()

image = vision_client.image(content=content)

print(image)
safe = image.detect_safe_search()
'''
print(safe.adult)
print(safe.medical)
print(safe.spoof)
print(safe.violence)
'''
