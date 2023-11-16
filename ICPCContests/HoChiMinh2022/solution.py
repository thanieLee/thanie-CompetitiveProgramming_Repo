import sys
n = int(input())

queries = []

for i in range(n):
    print("?", 1, i+1)
    sys.stdout.flush()
    x = int(input())
    queries.append(x)

vis = [False for _ in range(n)]
ans = [0 for _ in range(n)]

temp = 0
for i in range(1, n):
    if queries[0] > queries[i]:
        temp += 1
vis[temp] = True
ans[0] = temp
for i in range(n-1, 0, -1):
    prod = 1
    if queries[i] < queries[0]:
        prod = -1
    
    cnt = ((abs(queries[i]-queries[0])+1)//2)
    cur  = 0
    idx = ans[0]
    while (cur <= cnt):
        idx += prod
        if not vis[idx]:
            cur += 1
            if cur == cnt:
                while vis[idx]:
                   idx += prod
                
                break
    
    
    vis[idx] = True
    ans[i] = idx


print("!", end=" ")
for i in range(len(ans)):
    ans[i] += 1
print(*ans)