def max_cypriot_value(n, arr):
    max_cypriot = arr[0]
    current_sum = arr[0]

    for i in range(1, n):
        current_sum = max(arr[i], current_sum + arr[i])
        max_cypriot = max(max_cypriot, current_sum)

    return max_cypriot

def main():
    t = int(input())
    
    for _ in range(t):
        n = int(input())
        arr = list(map(int, input().split()))
        
        result = max_cypriot_value(n, arr)
        print(result)

if __name__ == "__main__":
    main()
