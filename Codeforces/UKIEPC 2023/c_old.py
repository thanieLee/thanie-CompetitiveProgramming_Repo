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
    for l in range(i):
        for k in range(p):
            mx[i][k] = max(mx[i][k], dp[l][i][k])
            
    for j in range(i+1, 2*n):
        if j == i+n+1:
            break
        for k in range(1, p+1):
            if k == 1:
                dp[i][j][k] = get_area(arr[i], arr[j])
                #print(i, j, k, dp[i][j][k], mx[i][k-1])
            else:
                add = get_area(arr[i], arr[j])
                dp[i][j][k] = max(mx[i][k-1]+add, dp[i][j][k])
                #print(i, j, k, dp[i][j][k], mx[i][k-1], add)
ans = -10000000

print(mx[1][1])
print(get_area(arr[2], arr[4]))
print(get_area(arr[3], arr[4]))
print(get_area(arr[4], arr[4]))
for i in range(n):
    for j in range(i+1, 2*n):
        for k in range(p+1):
            print(i, j, k, dp[i][j][k])


for i in range(n):
    for j in range(i+1, 2*n):
        if j == i+n+1:
            break
        
        ans = max(dp[i][j][p], ans)

        
print(ans)
                