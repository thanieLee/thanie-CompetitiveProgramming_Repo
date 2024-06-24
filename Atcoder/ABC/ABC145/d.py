x, y = [int(i) for i in input().split()]
def power(x, y, p):
    res = 1
    x = x % p
    if x == 0:
        return 0
    while y > 0:
        if y & 1:
            res = (res * x) % p
        y = y >> 1
        x = (x * x) % p
    return res
 
def mod_inverse(a, m):
    return power(a, m - 2, m)
 
def mod_div(a, b, m):
    a = a % m
    inv = mod_inverse(b, m)
    return (inv * a) % m

fact = [1]
MOD = 1000000007
cum = 1
for i in range(1, 1000001):
    cum *= i
    cum %= MOD
    fact.append(cum)

tx = x
ty = y

cnt = 0

if (x%3 == y%3) and (x%3 != 0):
    print(0)
    exit()

if (x%3 == 0 and y%3 != 0):
    print(0)
    exit()

if (x%3 != 0 and y%3 == 0):
    print(0)
    exit()

if (2*x > 4*y) or (4*x < 2*y):
    print(0)
    exit()
    
while tx*2 != ty:
    cnt+=1
    tx-=1
    ty+=1


n = tx
r = cnt

print(mod_div(fact[n], fact[r]*fact[n-r], MOD))