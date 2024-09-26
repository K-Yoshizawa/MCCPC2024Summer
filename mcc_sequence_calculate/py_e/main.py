#!/usr/bin/pypy3

# Python Solution (Easy)

N = int(input())
A = list(map(int, input().split(' ')))

assert N <= 100

ans = 0
for i in range(N):
    for j in range(i + 1, N):
        for k in range(j + 1, N):
            if A[i] == A[j]:
                continue
            if A[i] == A[k]:
                continue
            if A[j] != A[k]:
                continue
            ans += 1
print(ans)