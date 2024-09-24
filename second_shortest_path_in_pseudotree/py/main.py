#!/usr/bin/pypy3

import sys
sys.setrecursionlimit(10 ** 7)

N = int(input())
G = [[] for _ in range(N + 1)]
for _ in range(N):
    u, v = map(int, input().split(' '))
    G[u].append(v)
    G[v].append(u)

leaf_vertex = list()
for i in range(1, N + 1):
    if len(G[i]) == 1:
        leaf_vertex.append(i)

depth = [-1 for _ in range(N + 1)]
belong = [-1 for _ in range(N + 1)]
reach_cycle = [-1 for _ in range(N + 1)]

cycle = list()
history = list()
seen = [False for _ in range(N + 1)]
finished = [False for _ in range(N + 1)]

def dfs1(current: int, previous: int) -> int:
    seen[current] = True
    history.append(current)
    for adjacent in G[current]:
        if adjacent == previous or finished[adjacent]:
            continue
        if seen[adjacent] and not finished[adjacent]:
            history.append(adjacent)
            return adjacent
        position = dfs1(adjacent, current)
        if position != -1:
            return position
    finished[current] = True
    history.pop()
    return -1
cycle_start = dfs1(1, -1)
while len(history):
    cycle.append(history.pop())
    if history[-1] == cycle_start:
        break
cycle_len = len(cycle)
for i in range(cycle_len):
    depth[cycle[i]] = i
    belong[cycle[i]] = 0

def dfs2(current:int, previous:int, current_branch:int, current_depth:int) -> None:
    belong[current] = current_branch
    depth[current] = current_depth
    for adjacent in G[current]:
        if adjacent == previous:
            continue
        dfs2(adjacent, current, current_branch, current_depth + 1)
    return
branch = 1
for v in range(1, N + 1):
    if belong[v] == 0:
        for adjacent in G[v]:
            if belong[adjacent] == 0:
                continue
            reach_cycle[branch] = v
            dfs2(adjacent, v, branch, 1)
            branch += 1

T = int(input())
for _ in range(T):
    A, B = map(int, input().split(' '))
    
    if belong[A] > 0 and belong[A] == belong[B]:
        print(-1)
        continue
    if min(belong[A], belong[B]) == 0 and max(belong[A], belong[B]) > 0:
        if belong[A] > 0 and reach_cycle[belong[A]] == B or belong[B] > 0 and reach_cycle[belong[B]] == A:
            print(-1)
            continue
    if min(belong[A], belong[B]) > 0 and belong[A] != belong[B] and reach_cycle[belong[A]] == reach_cycle[belong[B]]:
        print(-1)
        continue
    
    if belong[A] == 0 and belong[B] == 0:
        dist1 = abs(depth[A] - depth[B])
        dist2 = cycle_len - dist1
        print(max(dist1, dist2))
    elif min(belong[A], belong[B]) == 0:
        if belong[B] == 0:
            A, B = B, A
        C = reach_cycle[belong[B]]
        dist1 = abs(depth[A] - depth[C])
        dist2 = cycle_len - dist1
        print(depth[B] + max(dist1, dist2))
    else:
        C, D = reach_cycle[belong[A]], reach_cycle[belong[B]]
        dist1 = abs(depth[C] - depth[D])
        dist2 = cycle_len - dist1
        print(depth[A] + depth[B] + max(dist1, dist2))
        