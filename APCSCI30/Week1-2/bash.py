import random
n = 499
m = 500

inspec = []
for i in range(n):
    inspec.append(random.randint(0, 1000000))

flightTime = [[0 for _ in range(n)] for _ in range(n)]
for i in range(n):
    for j in range(n):
        if i == j: continue
        flightTime[i][j] = random.randint(0, 1000000)

query = []
for i in range(m):
    s = random.randint(1, n)
    t = random.randint(1, n)
    while s == t:
        s = random.randint(1, n)
        t = random.randint(1, n)
    
    query.append([s, t, random.randint(1, 1000000)])

print(n, m)
print(*inspec)
for arr in flightTime:
    print(*arr)

for arr in query:
    print(*arr)