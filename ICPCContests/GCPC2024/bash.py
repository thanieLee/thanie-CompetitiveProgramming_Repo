print("{", end="")
cur = 1
prev = 1

for i in range(40):
    print(cur, end=", ")
    temp = cur
    cur = cur+prev
    prev = temp
print("}", end="")