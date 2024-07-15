from math import gcd
t, s = [int(i) for i in input().split()]

def can1(x, y):
    #print(x, y, abs(y)*1.5 + abs(x)-abs(y))
    if abs(x) < abs(y):
        if abs(x)*1.5 + abs(y)-abs(x) <= s:
            return True
    else:
        if abs(y)*1.5 + abs(x)-abs(y) <= s:
            return True
    return False
    
def can2(x, y):
    #print(x, y, abs(y)*1.5 + abs(x)-abs(y))
    if abs(x) + abs(y) <= t:
        return True
    return False

def bsearch1(L, R, x):
    while R-L > 1:
        M = (R+L)//2

        if can1(x, M):
            L = M
        else:
            R = M
    return L

def bsearch2(L, R, x):
    while R-L > 1:
        M = (R+L)//2

        if can2(x, M):
            L = M
        else:
            R = M
    return L

cnt = 0
ans = 0
for x in range(-s, s+1):
    ans1 = bsearch1(0, s+1, x)
    ans2 = t - abs(x)
    
    total_taxi_y = max(ans2*2+1, 0)
    total_spidey_y = ans1*2+1
    if total_spidey_y <= total_taxi_y:
        ans += total_spidey_y
    else:
        ans += total_taxi_y
    
    cnt += total_spidey_y

num = ans
den = cnt
d = gcd(num, den)

num = num//d
den = den//d

if den == 1:
    print(num)
else:
    print(f"{num}/{den}")
