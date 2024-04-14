n = 100000
m = 100
q = 100000
print(n, m)
for i in range(1, m+1):
    print(i, end=" ")
print()
for i in range(n):
    print((i%m)+1, (i+1)%m+1)
print(q)
for i in range(q):
    print("PERM", i+1, i+1)