#! /usr/bin/env python3

# store_redis_data.py file
#
# copy data from redis to the given file
# poll once per second

from io import FileIO
import redis
import json
import sys
import time
from redis_utils import *

file_ptr = None
r = redis_init()
#List of keys with the time stamp values
key_timestamps = {}    

def write_redis_keys(file_ptr:FileIO, redis_keys:list, key_timestamps:dict):
    for rkey in redis_keys:
        redis_value = r.hgetall(rkey)
        value_dict = { k.decode('utf-8'): redis_value[k].decode('utf-8') for k in redis_value.keys() }
        json.dump({rkey: value_dict}, file_ptr)
        file_ptr.write("\n\n")
        key_timestamps[rkey] = value_dict['Computer_UTC']

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Please provide a file for output")
        exit(0)
    elif len(sys.argv) > 2:
        print("Too many command line arguments")
        exit(0)
    file_ptr = open(sys.argv[1], "w+")
    while True:
        write_redis_keys(file_ptr, get_updated_redis_keys(r, key_timestamps), key_timestamps)
        time.sleep(1)
