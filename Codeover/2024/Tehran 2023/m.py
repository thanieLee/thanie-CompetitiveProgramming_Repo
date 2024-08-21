from collections import defaultdict
n = int(input())
a = []
strings = defaultdict(int)
cnt = 0
total_strings = []

for i in range(n):
    s = str(input())
    if s not in strings:
        strings[s] = cnt
        cnt += 1
        total_strings.append(0)
    a.append(strings[s])
    total_strings[strings[s]] += 1
print(a)
print(total_strings)