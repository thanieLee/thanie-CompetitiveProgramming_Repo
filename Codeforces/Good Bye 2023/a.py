n = int(input())

for _ in range(n):
    n, k = [int(i) for i in input().split()]
    arr = [int(i) for i in input().split()]
    prod = 1
    for i in range(n):
        prod *= arr[i]

    if (2023%prod != 0):
        print("NO")
        continue

    print("YES")
    for i in range(k-1):
        print(1, end=" ")
    
    print(2023//prod)