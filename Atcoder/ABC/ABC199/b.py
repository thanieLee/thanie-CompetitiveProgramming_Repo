n = int(input())
a = [int(i) for i in input().split()]
b = [int(i) for i in input().split()]

ans = 0

for i in range(1, 1001):
    can = True
    for j in range(n):
        if not (a[j] <= i <= b[j]):
            can = False
    if can:
        ans += 1
print(ans)