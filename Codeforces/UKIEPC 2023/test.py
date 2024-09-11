cnt = 0
loads_washed = 0
loads_dried = 0
loads_folded = 0
loads_hung = 0
can_dry = False
can_fold = False
can_hang = False
just_wash = False
just_dry = False
just_fold = False
just_hang = False
wash_cnt = 0
dry_cnt = 0
fold_cnt = 0
hung_cnt = 0


while loads_hung < 4:
    print(cnt, loads_washed, loads_dried, loads_folded, loads_hung)
    print(wash_cnt, dry_cnt, fold_cnt, hung_cnt)
    if just_dry:
        can_dry = True
        just_dry = False
    
    if just_fold:
        can_fold = True
        just_fold = False
    
    if just_hang:
        can_hang = True
        just_hang = False
    cnt+=1
    wash_cnt += 1
    wash_cnt %= 60

    if wash_cnt == 0:
        just_dry = True
        loads_washed += 1


    if can_dry and loads_washed == loads_dried+1:
        dry_cnt += 1
    dry_cnt  %= 30
    if dry_cnt == 0 and can_dry:
        just_fold = True
        loads_dried += 1
        can_dry = False
    if can_fold and loads_dried == loads_folded+1:
        fold_cnt += 1
    fold_cnt %= 60
    if fold_cnt == 0 and can_fold:
        just_hang = True
        loads_folded += 1
        can_fold = False
    
    if can_hang and loads_hung+1 == loads_folded:
        hung_cnt += 1

    hung_cnt %= 60
    if hung_cnt == 0 and can_hang:
        loads_hung += 1
        can_hang = False

print(cnt)
    




