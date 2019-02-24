import os
import subprocess


def opt_dist(s, D):
    subprocess.call(["g++", "zad4.cpp"])
    proc = subprocess.call("./a.out")
    print(proc)


