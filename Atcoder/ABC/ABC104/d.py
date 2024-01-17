s = str(input())
ans = 0
def solve(st):
    a = 0
    b = 0
    c = 0

    for i in range(len(st)):
        if st[i] == "A":
            a += 1
        elif st[i] == "B":
            b += a
        elif st[i] == "C":
            c += b
        else:
            c += b
            b += a
            a += 1

    return c

def solveAll(cur):
    global s, ans

    if len(cur) == len(s):
        ans += solve(cur)
    else:
        if s[len(cur)] == "?":
            solveAll(cur+"A")
            solveAll(cur+"B")
            solveAll(cur+"C")
        else:
            solveAll(cur+s[len(cur)])

solveAll("")
print(ans)

