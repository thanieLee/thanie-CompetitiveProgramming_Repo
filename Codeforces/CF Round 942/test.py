from itertools import permutations as perm
n = int(input())
arr = [int(i) for i in input().split()]


newArr = []
for i in range(n):
    for j in range(arr[i]):
        newArr.append(i)

ans = 0
for test in perm(newArr, n):
    if len(set(test)) == n:
        ans += 1
print(ans)