from setuptools import setup


def readme():
  with open('README.md') as f:
    README = f.read()
  return README


setup(
  name="robotcar",
  version="1.0.0",
  description="robotcar simulator package for education",
  long_description=readme(),
  author="UCSD Robotic Lab",
  author_email="g5hwang@ucsd.edu",
  license="MIT",
  classifiers=[
    "License :: OSI Approved :: MIT License",
    "Programming Language :: Python :: 3",
    "Programming Language :: Python :: 3.7",
  ],
  packages=["robotcar"],  # which file should be imported
  include_package_data=True,
  install_requires=["cv2"],
)
