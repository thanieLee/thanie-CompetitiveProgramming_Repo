from math import gcd
n = int(input())
def f(n):
    ans = 0
    for i in range(1, n+1):
        if gcd(n, i) > 1:
            ans += 1
    return ans

def g(n):
    return f(n)/n

mx_temp = -1
mx_so_far = -1
for i in range(2, n):
    if g(i) > mx_temp:
        mx_temp = g(i)
        mx_so_far = i

    print(f"{i}:", f(i), g(i), "max so far:", mx_so_far, f(mx_so_far))

