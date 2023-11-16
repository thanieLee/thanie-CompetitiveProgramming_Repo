import sys, random, math
from itertools import permutations as perm

def getInvCount(arr, n):
 
    inv_count = 0
    for i in range(n):
        for j in range(i + 1, n):
            if (arr[i] > arr[j]):
                inv_count += 1
 
    return inv_count

n = random.randint(2, 8)
arr = [i+1 for i in range(n)]
arr1 = arr.copy()
cnt = 0
ran = random.randint(1, math.factorial(n))
for per in perm(arr1):
    arr = per
    cnt += 1
    if cnt == ran:
        break

arr = list(arr)
print(n)
while True:
    query = [str(i) for i in input().split()]
    if query[0] == "?":
        temp1 = arr[int(query[1])-1]
        temp2 = arr[int(query[2])-1]
        arr[int(query[1])-1] = temp2
        arr[int(query[2])-1] = temp1
        print(getInvCount(arr, n))
        arr[int(query[1])-1] = temp1
        arr[int(query[2])-1] = temp2
    else:
        cop = query[1:].copy()
        for i in range(n):
            cop[i] = int(cop[i])
        if arr == cop:
            print("AC")
        else:
            print("WA")
            print(*arr)

