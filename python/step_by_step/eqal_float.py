import sys


def equal_float(a, b):
    return abs(a, b) <= sys.float_info.epsilon