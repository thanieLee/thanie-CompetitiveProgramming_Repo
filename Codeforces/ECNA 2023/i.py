n = int(input())
while n > 0:
    n-=1
    s = str(input())
    hyphen_cnt = 0
    is_invalid = False
    digit_cnt = 0
    for i in range(len(s)):
        if s[i] == "-":
            hyphen_cnt += 1
        else:
            digit_cnt += 1
        if i < len(s)-1:
            if s[i] == "-" and s[i+1] == "-":
                is_invalid = True
        
        if i == 0 and s[i] == '-':
            is_invalid = True
        
        if i == len(s)-1 and s[i] == '-':
            is_invalid = True

        if i != len(s)-1 and s[i] == "X":
            is_invalid = True

    if digit_cnt != 10:
        print('invalid')
        continue
    if is_invalid:
        print('invalid')
        continue

    if hyphen_cnt > 3:
        print('invalid')
        continue

    if hyphen_cnt == 3 and s[-2] != '-':
        print('invalid')
        continue

    cur = 10
    cnt = 0
    for i in range(len(s)):
        if s[i] == "-": continue
        if s[i] == "X":
            cnt += cur*10
        else:
            cnt += cur*int(s[i])
        cur-=1

    cnt %= 11

    if cnt != 0:
        print('invalid')
        continue
    
    check_sum = -1
    new_cnt = 9+7*3+8
    digit_par = 0
    for i in range(len(s)-1):
        if s[i] == "-": continue
        mul = 1
        if digit_par%2 == 0:
            mul = 3

        if s[i] == "X":
            new_cnt += mul*10
        else:
            new_cnt += mul*int(s[i])
        
        digit_par += 1
    
    new_cnt %= 10
    new_digit = (10-new_cnt)%10
    print("978-"+ s[0:len(s)-1]+str(new_digit))