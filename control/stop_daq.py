#! /usr/bin/env python

# stop_daq.py
# This script is run (remotely) on a DAQ node to stop recording
# - get the PID of the hashpipe process
# - send it a STOP signal
#
# On success, print OK.  Otherwise print an error message

import sys, os, signal

pid_filename = 'daq_pid'

def main():
    if len(sys.argv) != 1:
        print("usage: start_daq.py dirname")
        return

    try:
        f = open(pid_filename, 'r')
    except:
        print("can't open PID file")
        return
    pid = int(f.read())
    f.close()
    os.kill(pid, signal.SIGSTOP)
    os.unlink(pid_filename)

    print('OK')

main()