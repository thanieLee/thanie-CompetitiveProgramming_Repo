import math
n = int(input())
arr = [int(i) for i in input().split()]

mul = 1
for i in range(n):
    mul = math.lcm(mul, arr[i])

ans = 0

for i in range(n):
    ans += int(mul/arr[i])
    ans %= 1000000007
print(int(ans))