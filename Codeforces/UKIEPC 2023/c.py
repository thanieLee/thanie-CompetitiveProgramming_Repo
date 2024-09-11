import math
n = int(input())
p = int(input())
arr = [float(i) for i in input().split()]

for i in range(n):
    arr.append(arr[i]+360)
def get_area(a, b):
    global arr
    if b-a < 180:
        return 0.5 * math.sin((b-a)*math.pi/180) * (1000.0) * (1000.0)
    elif b-a > 180:
        return -0.5 * math.sin((360-(b-a))*math.pi/180) * (1000.0) * (1000.0)
    else:
        return 0

dp = [[[-10000000 for _ in range(p+1)] for _ in range(2*n)] for _ in range(2*n)]
mx = [[-10000000 for _ in range(p+1)] for _ in range(2*n)]
for i in range(n):
    dp[i][i][0] = 0
    for l in range(i+1):
        for k in range(p+1):
            mx[i][k] = max(mx[i][k], dp[l][i][k])


    for j in range(i+1, 2*n):
        if (i%n) == (j%n) and i != j:
            break
        for k in range(1, p+1):
            dp[i][j][k] = max(dp[i][j][k], mx[i][k-1] + get_area(arr[i], arr[j]))

ans = 0
print(get_area(359, 90+360))
for i in range(2*n):
    for j in range(2*n):
        for k in range(p+1):
            print(i, j, k, dp[i][j][k])


for i in range(2*n):
    for j in range(2*n):
        if j >= i+n:
            continue
        print(i, j, dp[i][j][p])
        ans = max(ans, dp[i][j][p])
print(ans)
 