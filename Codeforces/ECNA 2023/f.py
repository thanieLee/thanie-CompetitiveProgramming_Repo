n = int(input())
arr = [int(i) for i in input().split()]

nex_ptr = []
pre_ptr = []

for i in range(n):
    if i == 0:
        pre_ptr.append(-1)
    else:
        pre_ptr.append(i-1)

    if i == n-1:
        nex_ptr.append(-1)
    else:
        nex_ptr.append(i+1)

op_cnt = 0
start_idx = 0

while op_cnt != n-1:
    can_merge = False
    merge_idx = -1
    temp_val = pow(2, 101)
    remove_idx = -1

    cur = start_idx
    while cur != -1:
        if arr[nex_ptr[cur]] == arr[cur] and not can_merge and nex_ptr[cur] != -1:
            can_merge = True
            merge_idx = cur

        if pre_ptr[cur] != -1 and nex_ptr[cur] != -1:
            if arr[pre_ptr[cur]] != arr[cur] and arr[nex_ptr[cur]] != arr[cur] and temp_val > arr[cur]:
                temp_val = arr[cur]
                remove_idx = cur
        elif pre_ptr[cur] != -1:
            if arr[pre_ptr[cur]] != arr[cur] and temp_val > arr[cur]:
                temp_val = arr[cur]
                remove_idx = cur
        else:
            if arr[nex_ptr[cur]] != arr[cur] and temp_val > arr[cur]:
                temp_val = arr[cur]
                remove_idx = cur
        
        cur = nex_ptr[cur]

    if can_merge:
        arr[merge_idx] = arr[merge_idx]*2
        nex_ptr[merge_idx] = nex_ptr[nex_ptr[merge_idx]]
        pre_ptr[nex_ptr[merge_idx]] = merge_idx
    else:
        if pre_ptr[remove_idx] != -1:
            nex_ptr[pre_ptr[remove_idx]] = nex_ptr[remove_idx]

        if nex_ptr[remove_idx] != -1:
            pre_ptr[nex_ptr[remove_idx]] = pre_ptr[remove_idx]

        if remove_idx == start_idx:
            start_idx = nex_ptr[remove_idx]
            
        nex_ptr[remove_idx] = -1
        pre_ptr[remove_idx] = -1

    op_cnt += 1


print(arr[start_idx])

        
        
