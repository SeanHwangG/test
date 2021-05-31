# -*- coding: utf-8 -*-

import csv

txt_file = r"Data/6_.txt"
csv_file = r"Data/6_.csv"

with open(txt_file, 'r') as mycsv:
    in_txt = csv.reader((line.replace('\0', '') for line in mycsv))
    out_csv = csv.writer(open(csv_file, 'wb'))

    out_csv.writerows(in_txt)