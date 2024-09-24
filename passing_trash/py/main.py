#!/usr/bin/pypy3

# Python Solution (writer)

N, M = map(int, input().split(' '))
P = list(map(int, input().split(' ')))
Q = list(map(int, input().split(' ')))

for i in range(N):
    Q[i] -= 1

from math import log2, ceil

LOG = min(ceil(log2(M)) + 1, 41)
dat = [[0 for _ in range(N)] for _ in range(LOG)]
who = [[0 for _ in range(N)] for _ in range(LOG)]

for i in range(N):
    dat[0][i] = P[i]
    who[0][i] = Q[i]
for i in range(1, LOG):
    for j in range(N):
        dat[i][j] = dat[i - 1][who[i - 1][j]] + dat[i - 1][j]
        who[i][j] = who[i - 1][who[i - 1][j]]

ans = set()
for i in range(N):
    step = 0
    ret = i
    for k in range(LOG - 1, -1, -1):
        if step + dat[k][ret] < M:
            step += dat[k][ret]
            ret = who[k][ret]
    ans.add(ret)

ans = list(ans)
ans.sort()
for i in range(len(ans)):
    print(ans[i] + 1, end=('\n' if i + 1 == len(ans) else ' '))
