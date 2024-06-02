import random
t = 100
n = 100
print(t)
for i in range(t):
    arr = []
    print(n)
    while len(arr) < n:
        x = random.randint(500, 500)
        arr.append(x)
    print(*arr)