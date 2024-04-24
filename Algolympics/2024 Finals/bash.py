import random
n = 10
print(n)
perm = []
while len(perm) < n:
    perm.append(random.randint(1, 1000000000))
print(*perm)
c = 9
print(c)
test = [set() for _ in range(200001)]
for i in range(c):
    a = random.randint(1, n)
    b = random.randint(1, n)
    while b in test[a-1] or b == a:
        b = random.randint(1, n)
    test[a-1].add(b)
    print("SWAP", a, b)
