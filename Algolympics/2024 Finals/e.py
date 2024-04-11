t = int(input())
while t > 0:
    t -= 1
    n = int(input())
    arr = [int(i) for i in input().split()]
    arr.sort()
    ans = 0
    for i in range(n-1):
        ans = max(abs(arr[i]-arr[i+1]), ans)
    print(ans)