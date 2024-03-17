n = int(input())
nStr = str(n)
ans = 0
for i in range(1, 10):
    lStr = str(i) * len(nStr)
    if int(lStr) <= n:
        ans += len(nStr)
    else:
        ans += len(nStr)-1

ans += max(len(nStr)-1, 1)
print(ans)