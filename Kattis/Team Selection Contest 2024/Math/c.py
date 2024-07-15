from math import comb
n = int(input())

for i in range(n):
    r, s, x, y, w = [int(i) for i in input().split()]
    single_event_prob = 1/pow(s, y)
    win_chance = 0
    for i in range(x, y+1):
        cnt = comb(y, i)
        cnt *= pow(s-r+1, i)
        cnt *= pow(r-1, y-i)
        win_chance += cnt
    lose_chance = 1-(win_chance/pow(s, y))
    p = (win_chance/pow(s, y))*w
    print("yes" if p > 1 else "no")
