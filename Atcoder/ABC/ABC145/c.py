from math import sqrt, factorial, dist
from itertools import permutations as perm




n = int(input())
points = []
for _ in range(n):
    xi, yi = [int(i) for i in input().split()]
    points.append([xi, yi])

ans = 0
for per in perm(points):
    cnt = 0
    for i in range(1, n):
         cnt += dist([per[i-1][0], per[i-1][1]], [per[i][0], per[i][1]])
    
    ans += cnt

print(ans/factorial(n))
