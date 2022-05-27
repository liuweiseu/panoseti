# read the first nframes of a PFF file;
# return an array
# 0 N0
# 255 N1
#
# where N0 is the number of pixels with values from 0 to 255 etc.

import os, sys
import pff

def get_hist(file, nframes=100):
    fin = open(file, "rb");
    hist = [0]*256
    for i in range(nframes):
        x = pff.read_json(fin)
        if x is None:
            break
        x = pff.read_image(fin, 32, 2)
        if x is None:
            break
        for j in range(1024):
            v = x[j]>>8
            hist[v] += 1
    fin.close()
    return hist

# compute the x and 1-x quantiles of a file
def get_quantiles(file, x):
    hist = get_hist(file)
    total = 0;
    for i in range(256):
        total += hist[i]
    loval = total*x
    hival = total*(1-x)
    lo = -1
    hi = -1
    total = 0;
    for i in range(256):
        total += hist[i]
        if lo<0 and total >= loval:
            lo = i*256
        if hi<0 and total >= hival:
            hi = i*256
    return [lo, hi]
