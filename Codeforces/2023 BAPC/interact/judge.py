import sys

f = open("case", "r")
n = int(f.readline())
table = [[-1 for _ in range(n)] for _ in range(n)]
mx = 0
for i in range(n):
    row = [int(x) for x in f.readline().split()]
    for j in range(n):
        table[n-i-1][j] = row[j]
        mx = max(mx, row[j])

print(n)
sys.stdout.flush()
while True:
    query = [str(i) for i in input().split()]
    if query[0] == "!":
        if mx == int(query[1]):
            print("woah right")
            exit()
        else:
            print("poopies wrong")
            exit()
    else:
        print(table[int(query[2])-1][int(query[1])-1])
        sys.stdout.flush()



