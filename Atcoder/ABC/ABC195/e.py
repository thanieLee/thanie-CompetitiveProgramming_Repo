import sys
sys.setrecursionlimit(10**6)
n = int(input())
s = str(input())
x = str(input())

dp = [[-1 for _ in range(7)] for _ in range(n)]

def solve(i, md):
    if dp[i][md] != -1:
        return dp[i][md]
    elif i == n-1:
        c1 = md
        c2 = (md+int(s[i]))%7

        if x[i] == "T":
            if c1 == 0 or c2 == 0:
                return True
            else:
                return False
        else:
            if c1 == 0 and c2 == 0:
                return False
            else:
                return True
    else:
        cur = x[i]
        next = x[i+1]

        if cur == next:
            c1 = solve(i+1, md)
            c2 = solve(i+1, (md+int(s[i])*pow(10, n-i-1))%7)

            if c1 or c2:
                dp[i][md] = True
                return True
            dp[i][md] = False
            return False
        else:
            c1 = solve(i+1, md)
            c2 = solve(i+1, (md+int(s[i])*pow(10, n-i-1))%7)

            if not c1 or not c2:
                dp[i][md] = True
                return True
            dp[i][md] = False
            return False

win = solve(0, 0)
opposite = {
    "A" : "T",
    "T" : "A"
}

ans = {
    "A" : "Aoki",
    "T" : "Takahashi"
}

if win:
    print(ans[x[0]])
else:
    print(ans[opposite[x[0]]])
