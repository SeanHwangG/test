import os
from setuptools import setup, Extension

module = Extension('spam',
                   sources=['spammodule.cpp', 'cprint_list.cpp'],
                   include_dirs=['.'],
                   language='c++')

setup(name='spam', ext_modules=[module])
