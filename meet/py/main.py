#!/usr/bin/python3

# Python Solution (writer)

N, M = map(int, input().split(' '))
G = [[] for i in range(N)]
for i in range(M):
    A, B, C = map(int, input().split(' '))
    A -= 1
    B -= 1
    G[A].append((C, B))
    G[B].append((C, A))

from heapq import heappush, heappop
queue = list()
INF = 1000000000000

A_dist = [INF for i in range(N)]
queue.append((0, 0))
A_dist[0] = 0
while len(queue) != 0:
    c, u = heappop(queue)
    if A_dist[u] != c:
        continue
    for d, v in G[u]:
        if c + d < A_dist[v]:
            A_dist[v] = c + d
            heappush(queue, (c + d, v))

B_dist = [INF for i in range(N)]
queue.append((0, N - 1))
B_dist[N - 1] = 0
while len(queue) != 0:
    c, u = heappop(queue)
    if B_dist[u] != c:
        continue
    for d, v in G[u]:
        if c + d < B_dist[v]:
            B_dist[v] = c + d
            heappush(queue, (c + d, v))

dist = list()
for i in range(N):
    dist.append(max(A_dist[i], B_dist[i]))
dist.sort()

from bisect import bisect

Q = int(input())
K = list(map(int, input().split(' ')))
for k in K:
    print(bisect(dist, k))