import math
t = int(input())

while t:
    t-=1
    x, y= [int(i) for i in input().split()]

    a = x
    if (100-y) <= 0:
        print(-1)
        continue

    b = int(math.ceil((a*y)/(100-y)))


    print(a+b)
