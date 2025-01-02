import math
from collections import deque
n = int(input())
p = int(input())
arr = deque([float(i) for i in input().split()])
arr.append(arr[0])

def get_area(a, b):
    global arr
    if b-a < 180:
        return 0.5 * math.sin((b-a)*math.pi/180) * (1000.0) * (1000.0)
    elif b-a > 180:
        return -0.5 * math.sin((360-(b-a))*math.pi/180) * (1000.0) * (1000.0)
    else:
        return 0


ans = 0

dp = [[-100000000 for _ in range(p+1)] for _ in range(n+1)]
def solve(j, points):
    global dp
    if points == 0:
        return 0
    if j < 0:
        return 0    
    

    if dp[j][points] != -100000000:
        return dp[j][points]

    ans = -100000000
    for i in range(j):
        ans = max(ans, solve(i, points-1)+get_area(arr[i], arr[j]))

    dp[j][points] = ans
    return ans


# for i in range(n):
#     dp = [[[-100000000, -1] for _ in range(p+1)] for _ in range(2*n)]
#     for j in range(i+1, i+n+1): 
#         for k in range(1, p+1):
#             if k == 1:
#                 dp[j][k] = [get_area(arr[i], arr[j]), j]
#             else:
#                 temp = dp[j-1][k-1]
#                 val = temp[0]+get_area(arr[temp[1]], arr[j])

#                 if dp[j-1][k][0] > dp[j][k][0]:
#                     dp[j][k] = dp[j-1][k]

#                 if val > dp[j][k][0]:
#                     dp[j][k] = [val, j]
                
    
#     # for j in range(i+1, i+n+1):
#     #     for k in range(1, p+1):
#     #         print(i, j, k, dp[j][k])
#     ans = max(ans, dp[i+n][p][0])

for i in range(n):
    ans = max(solve(n, p), ans)
    dp = [[-100000000 for _ in range(p+1)] for _ in range(n+1)]

    left = arr[0]
    arr.popleft()
    arr.pop()
    arr.append(left)
    arr.append(arr[0])


print(ans)
