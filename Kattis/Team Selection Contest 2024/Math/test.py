cnt = 0
for i in range(0, 2019):
    for j in range(0, 2019):
        if i*i + j*j == 2018*2018:
            print(i, j)
            cnt += 1
print(cnt)