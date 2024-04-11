TOnx = [str(i) for i in input().split()]
TOny = [str(i) for i in input().split()]
wait = [str(i) for i in input().split()]
TOff = [str(i) for i in input().split()]
opn = [str(i) for i in input().split()]
LrOn = [str(i) for i in input().split()]
lStemp = [str(i) for i in input().split()]

on = [TOnx[2], TOny[2]]
switches = ["A", "B", "C"]
pos = ['', '', ''] 
lights = ["1", "2", "3"]
curOn = ''
curOff = ''
notTouched = ''
for sw in switches:
    if sw in on and sw != TOff[2]:
        curOn = sw
    elif sw in on:
        curOff = sw
    else:
        notTouched = sw

pos[int(LrOn[1])-1] = curOn

for light in lights:
    if light == LrOn[1]:
        continue
    elif light == lStemp[1]:
        if lStemp[3] == "COOL":
            pos[int(light)-1] = notTouched
        else:
            pos[int(light)-1] = curOff

for sw in switches:
    if sw not in pos:
        for i in range(3):
            if pos[i] == '':
                pos[i] = sw
print(*pos)
        


