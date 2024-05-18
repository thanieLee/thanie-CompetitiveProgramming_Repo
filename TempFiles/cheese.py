from functools import cmp_to_key
import locale
f = open("tes", "r")
strings = []

for i in range(24):
    cur = f.readline()
    strings.append(cur)

sorted(strings, key=cmp_to_key(locale.strcoll))
for s in strings:
    print(s)