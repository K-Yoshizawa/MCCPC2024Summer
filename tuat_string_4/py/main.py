#!/usr/bin/pypy3

# Python Solution (writer)

N, M = map(int, input().split(' '))
C = list(map(int, input().split(' ')))

MOD = 998244353

cnt = [[0 for _ in range(M + 1)] for _ in range(M + 1)]
left_sum = [0 for _ in range(M + 1)]

for i in range(N):
    for j in range(1, M + 1):
        if C[i] == j:
            continue
        cnt[j][C[i]] = (cnt[j][C[i]] + left_sum[j]) % MOD
    left_sum[C[i]] += 1

ans = 0
right_sum = [0 for _ in range(M + 1)]

all_sum = [0 for _ in range(M + 1)]
for i in range(1, M + 1):
    for j in range(1, M + 1):
        all_sum[i] = (all_sum[i] + cnt[i][j]) % MOD

for i in range(N - 1, -1, -1):
    for j in range(1, M + 1):
        if C[i] == j:
            continue
        ans = (ans + (all_sum[j] - cnt[j][C[i]] + MOD) % MOD * right_sum[j] % MOD) % MOD
    right_sum[C[i]] = (right_sum[C[i]] + 1) % MOD
    for j in range(1, M + 1):
        if C[i] == j:
            continue
        cnt[j][C[i]] = (cnt[j][C[i]] - left_sum[j] + MOD) % MOD
        all_sum[j] = (all_sum[j] - left_sum[j] + MOD) % MOD
    left_sum[C[i]] = (left_sum[C[i]] - 1 + MOD) % MOD

print(ans)