import random
n = 5
m = 5
print(n, m)
for i in range(m):
    x = random.randint(1, n-1)
    y = random.randint(1, n-1)
    z = random.randint(0, n-1)
    print(x, y, z)
