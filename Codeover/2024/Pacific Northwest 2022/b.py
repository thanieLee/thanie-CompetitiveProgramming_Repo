s = str(input())
bitstring = []

ans = 0
for i in range(len(s)//2):
    if s[i] == s[::-1][i]:
        bitstring.append("1")
    else:
        bitstring.append("0")

print(bitstring)
for i in range(len(s)//2-1):
    if bitstring[i] == "0":
        bitstring[i] = "1"
        if bitstring[i+1] == "1":
            bitstring[i+1] = "0"
        else:
            bitstring[i+1] = "1"
        ans += 1
        if i == 1:
            ans -= 1
    print(bitstring)
if bitstring[-1] == "0":
    ans += 1
print(ans)
    