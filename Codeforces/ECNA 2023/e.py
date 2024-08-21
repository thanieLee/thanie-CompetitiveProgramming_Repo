from math import log2
s = str(input())

for i in range(len(s)-1):
    if s[i] == s[i+1] and s[i] == "O":
        print("INVALID")
        exit()

if s[-1] != "O":
    print("INVALID")
    exit()
all_starts = []
i = 16
while i <= pow(2, 47):
    if (i-1)%3 == 0:
        all_starts .append((i-1)//3)

    i *= 2


def solve(n):
    cur = n
    for i in range(len(s)-2, -1, -1):
        if cur == 1 or pow(2, int(log2(cur))) == cur:
            return "INVALID"

        if s[i] == "E":
            cur *= 2
        else:
            if (cur-1)%3 != 0:
                return "INVALID"
            cur = (cur-1)//3
    
    return cur

for i in all_starts:
    if solve(i) != "INVALID":
        print(solve(i))
        exit()
print("INVALID")

