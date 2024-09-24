#!/usr/bin/pypy3

# Python Solution (writer)

N, M = map(int, input().split(' '))
P = list(map(int, input().split(' ')))
Q = list(map(int, input().split(' ')))

for i in range(N):
    Q[i] -= 1

from math import log2, ceil

LOG = min(ceil(log2(M)) + 1, 41)
dat = [[-1 for _ in range(LOG)] for _ in range(N)]
who = [[-1 for _ in range(LOG)] for _ in range(N)]

for i in range(N):
    dat[i][0] = P[i]
    who[i][0] = Q[i]
for j in range(1, LOG):
    for i in range(N):
        dat[i][j] = dat[who[i][j - 1]][j - 1] + dat[i][j - 1]
        who[i][j] = who[who[i][j - 1]][j - 1]

ans = set()
for i in range(N):
    step = 0
    ret = i
    for k in range(LOG - 1, -1, -1):
        if step + dat[ret][k] < M:
            step += dat[ret][k]
            ret = who[ret][k]
    ans.add(ret)

ans = sorted(list(ans))
for i in range(len(ans)):
    print(ans[i] + 1, end=('\n' if i + 1 == len(ans) else ' '))
