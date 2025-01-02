n, k = [int(i) for i in input().split()]

def brute_force(n, k):
    s = ""
    cnt = 0
    for i in range(n):
        if i < k:
            s += '0'
        else:
            can = False

            for t in range(1, i):
                if t*k > i:
                    break
                    
                starts = [i-t]
                for j in range(k-1):
                    starts.append(starts[-1] - t)
                
                starts.reverse()
                starts.append(i)
                current = True

                for j in range(len(starts)-2):
                    #print(i, s[starts[j]:starts[j+1]], s[starts[j+1]:starts[j+2]])
                    if s[starts[j]:starts[j+1]] != s[starts[j+1]:starts[j+2]]:
                        current = False

                if current:
                    can = True
            if can:
                s += '1'
                cnt += 1
            else:
                s += '0'
            
    print(s)
    return cnt

# brute = brute_force(n, k)
# print(brute)

def length(i, k):
    if i == 1:
        return k+1
    else:
        return length(i-1, k)*k+1

def answer(i, k):
    if i == 1:
        return 1
    else:
        return answer(i-1, k)*k+1


hold = -1
for i in range(k+1):
    hold = i
    if pow(i, k) > n:
        break

temp = n
ans = 0
can_break = False
for i in range(hold, 0, -1):
    cnter = 0
    while temp >= length(i, k):
        #print(ans, temp, length(i, k), answer(i, k))
        temp -= length(i, k)
        ans += answer(i, k)

        if i == hold:
            can_break = True
            break

        cnter += 1
        if cnter == k:
            break

    if can_break:
        break

# print(k, n, pow(k, k))
# print(ans, temp, ans+temp)
if k <= 10 and n >= pow(k, k):
    print(ans+temp)
else:
    print(ans)