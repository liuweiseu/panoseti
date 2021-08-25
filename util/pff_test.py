# test Python API for PFF
# create the file with pff_test.cpp

import json

import pff

def main():
    f = open("test.pff", "rb")
    x = pff.read_json(f)
    y = json.loads(x)
    print(y)
    x = pff.read_image_16(f)
    print(x)

main()
