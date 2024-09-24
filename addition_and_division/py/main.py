#!/usr/bin/python3

# Python Solution (writer)

T = int(input())
for _ in range(T):
    N, M, K = map(int, input().split(' '))
    print(M * (K + 1) + (1 if K == N - 1 else 0))