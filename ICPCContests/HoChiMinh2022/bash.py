from itertools import permutations as perm

def getInvCount(arr, n):
 
    inv_count = 0
    for i in range(n):
        for j in range(i + 1, n):
            if (arr[i] > arr[j]):
                inv_count += 1
 
    return inv_count

n = 4
arr = [i+1 for i in range(n)]

for per in perm(arr):
    pe = list(per)
    print(pe)
    for i in range(n):
        temp = pe[0]
        temp2 = pe[i]
        pe[0] = temp2
        pe[i] = temp
        print(getInvCount(pe, n), end=" ")
        pe[0] = temp
        pe[i] = temp2
    print()