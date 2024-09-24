#!/usr/bin/python3

# Python Solution (writer)

Nstr, Mstr = map(str, input().split(' '))
N = int(Nstr)
M = int(Mstr[-2:])

for i in range(M, M + N):
    for j in range(M, M + N):
        print(f'{(i * j) % 100:02}', end=('\n' if j + 1 == M + N else ' '))