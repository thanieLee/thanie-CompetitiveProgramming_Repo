from math import dist
n = int(input())
x = []
y = []
s = []

for i in range(n):
    xi, yi, si = [float(i) for i in input().split()]
    x.append(xi)
    y.append(yi)
    s.append(si)

slow = float(input())
dists = [[-1 for _ in range(n)] for _ in range(n)]
for i in range(n):
    for j in range(i+1, n):
        dists[i][j] = dist([x[i], y[i]], [x[j], y[j]])
        dists[j][i] = dists[i][j]

slows = []
for i in range(n+1):
    slows.append(pow(slow, i))


def can(M):
    global n, x, y, s
    dp = [[100000000.0 for _ in range(16)] for _ in range(1<<n)]

    for msk in range(1, 1<<n):
        size = 0
        msb = -1
        for i in range(n):
            if (msk & (1<<i)) > 0:
                size += 1
                msb = i
        
        if size == 1:
            time_with_speed = dist([0, 0], [x[msb], y[msb]])/M
            if time_with_speed <= s[msb]:
                dp[msk][msb] = time_with_speed
        else:
            bits = []
            for i in range(n):
                if (msk & (1<<i)) > 0:
                    bits.append(i)
            
            for i in bits:
                prev = msk & ~(1<<i)
                for j in bits:
                    if (msk & (1<<j)) == 0 or i == j: continue
                    if dp[prev][j] == 100000000.0:
                        continue

                    old_time = dp[prev][j]
                    new_time = dists[i][j]/(M*slows[size-1])

                    if (old_time + new_time <= s[i]):
                        dp[msk][i] = min(dp[msk][i], old_time+new_time)

    ans = False
    for i in range(n):
        if (dp[(1<<n)-1][i] != 100000000.0):
            ans = True
    
    return ans

def bsearch(L, R):
    cnt = 0
    while R-L > 0.0000001 and cnt <= 500:
        cnt += 1
        M = (R-L)/2 + L
        if can(M):
            R = M
        else:
            L = M
    
    return L

print(bsearch(0, 1000000.0))
