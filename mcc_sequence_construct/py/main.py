#!/usr/bin/python3

# Python Solution (writer)

M = int(input())

N = 200000
T = list()
for i in range(190001):
    T.append(i * (i - 1) // 2)

ans = list()
remain = M
nex = 10000
cnt = 0
while nex > 0:
    while remain < T[-1]:
        ans.append(111111)
        T.pop()
        cnt += 1
    if len(T) == 2:
        ans.append(111111)
        T.pop()
        cnt += 1
    ans.append(nex)
    remain -= T[-1]
    nex -= 1
print(len(ans))
for i in range(len(ans)):
    print(ans[i], end=('\n' if i + 1 == len(ans) else ' '))