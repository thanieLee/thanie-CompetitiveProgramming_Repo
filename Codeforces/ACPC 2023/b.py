import math
t = int(input())

prime_sieve = [True for _ in range(1000001)]
prime_sieve[0] = False
prime_sieve[1] = False

for i in range(2, 1000001):
    if not prime_sieve[i]:
        continue

    for j in range(i+i, 1000001, i):
        prime_sieve[j] = False

primes = []

for i in range(2, 1000001):
    if prime_sieve[i]:
        primes.append(i)

while t:
    t -= 1
    n = int(input())
    a = [int(i) for i in input().split()]
    b = [int(i) for i in input().split()]

    a_cnt = []





    