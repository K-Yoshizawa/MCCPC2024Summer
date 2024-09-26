#!/usr/bin/pypy3

# Python Solution (Hard)

N = int(input())
A = list(map(int, input().split(' ')))

ans = 0
cum = 0
cnt = [0 for _ in range(N + 1)]
for i in range(N - 1, -1, -1):
    ans += cum - (cnt[A[i]] - 1) * cnt[A[i]] // 2
    cum += cnt[A[i]]
    cnt[A[i]] += 1
print(ans)