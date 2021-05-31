# -*- coding: utf-8 -*-

from more_itertools import unique_everseen

with open('one.csv','r') as f, open('combined.csv','w') as out_file:
    out_file.writelines(unique_everseen(f))