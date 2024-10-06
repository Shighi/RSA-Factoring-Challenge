#!/usr/bin/python3
import sys
from math import sqrt, isqrt

def factorize_large(n):
    n = int(n)
    if n % 2 == 0:
        return (2, n // 2)
    for i in range(3, isqrt(n) + 1, 2):
        if n % i == 0:
            return (i, n // i)
    return (1, n)

if __name__ == "__main__":
    if len(sys.argv) != 2:
        exit(1)
    try:
        num = sys.argv[1]
        p, q = factorize_large(num)
        print(f"{num}={q}*{p}")
    except:
        exit(1)
