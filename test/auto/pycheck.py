#!/usr/bin/python3
import os
import subprocess 
import sys

ret = os.system("g++ -std=c++11 &>/dev/null " + sys.argv[1])
if ret != 0 :
    exit(1)
else:
    output = subprocess.check_output(["./a.out"]);
    if output.decode("utf-8") == sys.argv[2]:
        exit(0)
    else:
        exit(2)
        
