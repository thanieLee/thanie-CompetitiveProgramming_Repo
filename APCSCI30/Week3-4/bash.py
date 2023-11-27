import random
import math

def LSB(n):
    idx = 0
    while n&(1<<idx) == 0:
        idx+=1

    return 1<<idx


def h(x, n):
    cnt = 0
    for y in range(n-LSB(n), n):
        if x & y == 0:
            cnt += 1
            
    return cnt

def newH(a, b):
    ans = 0
    zero = 0

    i = 1
    while i <= b:
        if b & i:
            b ^= i

            if (a & b) == 0:
                ans += 1<<zero

        if a & b == 0:
            zero += 1
        i <<= 1
    return ans

for i in range(1, 100):
    for j in range(1, 100):
        print(bin(i), bin(j), h(i, j), newH(i, j))