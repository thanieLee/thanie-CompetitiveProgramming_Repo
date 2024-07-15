from math import floor, gcd
        


t, s = [int(i) for i in input().split()]

def can(x, y):
    if abs(y)
    
def bsearch(L, R, x):
    while R-L > 1:
        M = (R+L)//2

taxi_total = 1
spidey_total = 1
for i in range(t):
    taxi_total += 4 * (i+1) 

for i in range(s):
    spidey_total += 4 * (i+1)

for i in range(0, s+1):
    cost_left = s-i
    dist_can_travel = floor(cost_left/1.5)
    max_x = dist_can_travel
    max_y = dist_can_travel + i
    sm = max_x + max_y
    total_points = int(floor((sm-s+1)/2))
    if i + dist_can_travel*2 > s:
        if i == 0:
            spidey_total += 4*total_points
        else:
            spidey_total += 8*total_points

d = gcd(taxi_total, spidey_total)
num = taxi_total//d
den = spidey_total//d
if den != 1 and num < den:
    print(f"{num}/{den}")
else:
    print(num)