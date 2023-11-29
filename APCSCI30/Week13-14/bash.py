al = "abcdefghijklmnopqrstuvwxyz"

s1 = ""

for i in range(2000):
    s1 += al[i%26]
print(s1)
print(s1[0:500])
print(s1[1500:2000])