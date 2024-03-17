s = str(input())

ans = set()

def check(s):
    for i in range(len(s)-1):
        if s[i] == 's' and s[i+1] == 's':
            newString = s[:i] + "B" + s[i+2:]
            ans.add(newString)
            check(newString)

ans.add(s.lower())
check(s.lower())
for an in ans:
    print(an)