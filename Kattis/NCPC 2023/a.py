n, k = [int(i) for i in input().split()]

if k >= n:
    print(0)
    exit()

ans = 1
inc = 1
temp = k+1

while temp < n:
    if temp*k > n:
        print(inc, n//(temp*k), inc*(n//(temp*k)), "yes")
        ans += inc*(n//(temp*k))
        break
    else:
        print(inc, k, inc*k, "no")
        ans += inc*(k)
        temp *= k
        inc += 1

    if inc == k:
        break
print(ans)