def no(a, b):
    can = True
    for i in range(len(a)):
        if a[i] > b[i]:
            can = False
    return can

t = int(input())
while (t>0):
    t -= 1
    n = int(input())
    a = [int(i) for i in input().split()]
    b = [int(i) for i in input().split()]
    
    ans = 0
    while not no(a, b):
        ans += 1
        n = 