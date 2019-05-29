#!/usr/bin/env python

import sys
import csv

fnames = sys.argv[1:]

def main():
    if len(fnames) == 0:
        print("Script called with no files given", file = sys.stderr)
        sys.exit(1)
    else:
        parse()
        
def parse(nam = fnames):
    arrays = []
    tmp = []
    for f in nam:
        arrays.append([])
        with open(f, newline='') as csvfile:
            reader = csv.reader(csvfile, delimiter=',', quotechar=r'"')
            for row in reader:
                arrays[-1].append(row)
    for i in range(len(arrays[0])):
        tmp.append(list(zip(arrays[0][i], arrays[1][i])))
    for i in range(len(tmp)):
        for j in range(len(tmp[i])):
            tmp[i][j] = " / ".join(tmp[i][j])
        tmp[i].insert(0,str(i))
        tmp[i] = " & ".join(tmp[i]) + r' \\ \hline'
    tmp = "\n".join(tmp)
    print(tmp)

main()