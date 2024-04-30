from math import gcd
t = int(input())
while t>0:
    t-=1
    ans = 0
    n, m = [int(i) for i in input().split()]
    for b in range(1, m+1):
        for a in range(1, n+1):
            if (b*gcd(a, b))%(a+b) == 0:
                ans += 1
                print(b, a)
    print(ans)