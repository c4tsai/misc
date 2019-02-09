# -*- coding: utf-8 -*-

import csv
import re
import pandas as pd

f1 = open("Ingredient Description Sub-Sample [Sanitized] - Country A Vendors.csv")
f2 = open("Ingredient Description Sub-Sample [Sanitized] - Country B Vendors.csv")

def str_to_num(strg, flt = False):
    try:
        if flt:
            out = float(strg)
        else: 
            out = int(strg)
    except ValueError:
        out = strg
    return out

def split_packsize(strg): 
    temp = re.split(r'(\/|-|(?<=\d)x|\sx\s)', strg, maxsplit = 1)
    if len(temp) == 1: # In the event of not finding the delimiters 
        temp = [None, None] + temp
    div = re.split(r'(\D+$)', temp[2], maxsplit = 1)
    if len(div) == 1: 
        div = [None] + div
    temp = temp[0:2] + div[0:2]
    out = []
    for i in temp: 
        try:
            out.append(i.strip().lower()) # Removes leading whitespace
        except AttributeError:
            out.append('')
    return out

def parse_csv(f):
    data = csv.reader(f)
    out = []
    for row in data:
        if re.search(r'^\d{3,}$', row[1]) is not None:
            out.append([row[1]] + split_packsize(row[0]))
        else:
            out.append([row[0]] + split_packsize(row[1]))
    return out;
        

data1 = pd.DataFrame(parse_csv(f1)[1:], columns = ["Description", "num1", "div", "num2", "unit"])
data2 = pd.DataFrame(parse_csv(f2)[1:], columns = ["Description", "num1", "div", "num2", "unit"])

print(data1.groupby(['unit']).count().sort_values("div", ascending=False))
data1.to_csv("output_countryA_2.csv")
data2.to_csv("output_countryB_2.csv")