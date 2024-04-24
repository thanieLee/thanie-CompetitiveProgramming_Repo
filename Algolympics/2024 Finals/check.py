inp = open("in", "r")
out = open("out", "r")

n = int(inp.readline())
perm = [int(i) for i in inp.readline().split()]
print(n)
print(*perm)

c = int(inp.readline())
print(c)
swaps = []
for i in range(c):
    cur = [str(i) for i in inp.readline().split()]
    swaps.append([int(cur[1])-1, int(cur[2])-1])
    print(*swaps[-1])

ye = out.readline()
outputSwaps1 = [int(i)-1 for i in out.readline().split()]
outputSwaps2 = [int(i)-1 for i in out.readline().split()]

perm1 = perm.copy()
for i in range(c):
    curSwap = swaps[outputSwaps1[i]]
    temp = perm1[curSwap[0]]
    perm1[curSwap[0]] = perm1[curSwap[1]]
    perm1[curSwap[1]] = temp

perm2 = perm.copy()
for i in range(c):
    curSwap = swaps[outputSwaps2[i]]
    temp = perm2[curSwap[0]]
    perm2[curSwap[0]] = perm2[curSwap[1]]
    perm2[curSwap[1]] = temp

print(*perm1)
print(*perm2)
print(perm1 == perm2)