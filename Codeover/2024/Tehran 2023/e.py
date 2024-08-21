from math import acos, dist, pi
n = int(input())
points = []

def dot(p1, p2, p3):
    return (p1[0]-p3[0])*(p2[0]-p3[0]) + (p1[1]-p3[1])*(p2[1]-p3[1])

def angle(p1, p2, p3):
    dist1 = dist(p1, p3)
    dist2 = dist(p2, p3)
    dot_prod = dot(p1, p2, p3)

    return acos((dot_prod)/(dist1*dist2))

print(angle([0, 1], [1, 0], [0, 0]))

for i in range(n):
    x, y = [int(i) for i in input().split()]
    points.append([x, y])

