out = []

for i in range(1, 1000):
    for j in range(i):
        out.append([i, j])

print(len(out))

for pair in out:
    print(pair[0], pair[1])