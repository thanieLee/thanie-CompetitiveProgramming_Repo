from math import *
n, d = [int(i) for i in input().split()]

def dist(a, b):
    global d
    sm = 0
    for i in range(d):
        sm += pow(a[i] - b[i], 2)
    
    return sm

ans = 0
points = []
for i in range(n):
    p = [int(i) for i in input().split()]
    points.append(p)

for i in range(n):
    for j in range(i+1, n):
        if int(sqrt(dist(points[i], points[j]))) == sqrt(dist(points[i], points[j])):
            ans += 1
print(ans)