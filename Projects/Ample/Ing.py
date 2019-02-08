# -*- coding: utf-8 -*-

import csv
import re

f1 = open("Ingredient Description Sub-Sample [Sanitized] - Country A Vendors.csv")
f2 = open("Ingredient Description Sub-Sample [Sanitized] - Country B Vendors.csv")

def split_packsize(str): 
    out = re.split(r'(\/|-|(?<=\d)x|\sx\s)', str, maxsplit = 1)
    if len(out) == 1: # In the event of not finding the delimiters 
        out = [None, None] + out
    div = re.split(r'(\D+$)', out[2], maxsplit = 1)
    out = out[0:2] + div[0:2]
    return out

def parse_csv(f, dest = "output.csv"):
    data = csv.reader(f)
    fout = open(dest, mode = 'w', newline = '')
    writer = csv.writer(fout)
    for row in data:
        if re.search(r'^\d{3,}$', row[1]) is not None:
            writer.writerow([row[1]] + split_packsize(row[0]))
        else:
            writer.writerow([row[0]] + split_packsize(row[1]))
    fout.close()
        
parse_csv(f1, "output_countryA_1.csv")
parse_csv(f2, "output_countryB_1.csv")