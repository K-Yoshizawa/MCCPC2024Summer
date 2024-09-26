#!/usr/bin/pypy3

# Python Solution (Normal)

N = int(input())
A = list(map(int, input().split(' ')))

assert N <= 1000

ans = 0
C = [[0 for _ in range(N + 1)] for _ in range(N + 1)]
for k in range(N):
    Aj = A[k]
    for Ai in range(1, N + 1):
        if Ai == Aj:
            continue
        ans += C[Ai][Aj]
    j = k
    for i in range(j):
        C[A[i]][Aj] += 1
print(ans)