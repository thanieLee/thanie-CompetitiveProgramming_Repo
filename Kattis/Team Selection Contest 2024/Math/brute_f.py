from math import gcd, floor
import random

t, s = [int(i) for i in input().split()]

spidey_points = set()
taxi_points = set()
timer = 0
for x in range(-1000, 1001):
    for y in range(-1000, 1001):
        timer += 1
        if x < 0:
            deltax = 1
        else:
            deltax = -1
        
        if y < 0:
            deltay = 1
        else:
            deltay = -1

    
        tempx = x
        tempy = y
        if abs(x) < abs(y):
            tempx = 0
            tempy += abs(x)*deltay
            cnt = abs(x)
        else:
            tempy = 0
            tempx += abs(y)*deltax
            cnt = abs(y)
        
        if cnt*1.5 + abs(tempx) + abs(tempy) <= s:
            spidey_points.add(timer)

timer = 0
for x in range(-1000, 1001):
    for y in range(-1000, 1001):
        timer += 1
        if abs(x) + abs(y) <= t:
            taxi_points.add(timer)

ans = 0
for t_p in taxi_points:
    if t_p in spidey_points:
        ans += 1

print(len(taxi_points), len(spidey_points))
d = gcd(ans, len(spidey_points))
num = ans//d
den =  len(spidey_points)//d
print(num, den)
if den != 1 and num < den:
    brute = f"{num}/{den}"
else:
    brute = "1"

taxi_total = 1
spidey_total = 1
for i in range(t):
    taxi_total += 4 * (i+1)

for i in range(s):
    spidey_total += 4 * (i+1)

for i in range(0, s+1):
    cost_left = s-i
    dist_can_travel = floor(cost_left/1.5)
    if i + dist_can_travel*2 > s:
        if i == 0:
            spidey_total += 4
        else:
            spidey_total += 8

d = gcd(taxi_total, spidey_total)
num = taxi_total//d
den = spidey_total//d
if den != 1 and num < den:
    smart = f"{num}/{den}"
else:
    smart = "1"

if brute != smart:
    print(t, s)
    print(brute, smart)
    exit()