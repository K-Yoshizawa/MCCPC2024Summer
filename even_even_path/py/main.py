#!/usr/bin/pypy3

import sys
sys.setrecursionlimit(10**6)

N = int(input())
V = list(map(int, input().split(' ')))
T = [[] for _ in range(N)]
for i in range(N - 1):
    A, B = map(int, input().split(' '))
    A, B = A - 1, B - 1
    T[A].append(B)
    T[B].append(A)

ans = [0 for _ in range(N)]
sub_ans = [0 for _ in range(N)]
parent_list = [-1 for _ in range(N)]
matrix = [[0, 0, 0, 0] for _ in range(N)]
def dfs1(current:int, parent:int) -> list:
    parent_list[current] = parent
    ans[current] = sub_ans[current] = 0
    ret = [0, 0, 0, 0]
    for child in T[current]:
        if child == parent:
            continue
        c00, c01, c10, c11 = dfs1(child, current)
        ans[current] += ans[child]
        sub_ans[current] += sub_ans[child]
        c00, c01 = c01, c00
        c10, c11 = c11, c10
        if V[current] == 0:
            ans[current] += ret[0b00] * c00
            ans[current] += ret[0b01] * c01
            ans[current] += ret[0b10] * c10
            ans[current] += ret[0b11] * c11
            sub_ans[current] += ret[0b00] * c10
            sub_ans[current] += ret[0b01] * c11
            sub_ans[current] += ret[0b10] * c00
            sub_ans[current] += ret[0b11] * c01
        else:
            ans[current] += ret[0b00] * c10
            ans[current] += ret[0b01] * c11
            ans[current] += ret[0b10] * c00
            ans[current] += ret[0b11] * c01
            sub_ans[current] += ret[0b00] * c00
            sub_ans[current] += ret[0b01] * c01
            sub_ans[current] += ret[0b10] * c10
            sub_ans[current] += ret[0b11] * c11
        ret[0b00] += c00
        ret[0b01] += c01
        ret[0b10] += c10
        ret[0b11] += c11
    if V[current] == 0:
        ret[0b00] += 1
    else:
        ret[0b00], ret[0b10] = ret[0b10], ret[0b00]
        ret[0b01], ret[0b11] = ret[0b11], ret[0b01]
        ret[0b10] += 1
    ans[current] += ret[0b00]
    sub_ans[current] += ret[0b10]
    matrix[current] = ret
    return ret

dfs1(0, -1)
first_ans = ans[0]
print(first_ans)

def dfs2(current:int, parent:int, offset:list) -> None:
    # print(f'# Vertex {current + 1} -> [{ans[current]}], <{sub_ans[current]}>')
    # print(f'    [{offset[0b00]}, {offset[0b01]}]')
    # print(f'    [{offset[0b10]}, {offset[0b11]}]')
    ans[current] = first_ans - ans[current] + sub_ans[current]
    ans[current] -= matrix[current][0b00] * offset[0b00]
    ans[current] -= matrix[current][0b10] * offset[0b10]
    ans[current] += matrix[current][0b00] * offset[0b10]
    ans[current] += matrix[current][0b10] * offset[0b00]
    for child in T[current]:
        if child == parent:
            continue
        next_offset = offset.copy()
        p00, p01, p10, p11 = matrix[current]
        c00, c01, c10, c11 = matrix[child]
        c00, c01 = c01, c00
        c10, c11 = c11, c10
        if V[current] == 1:
            next_offset[0b00], next_offset[0b10] = next_offset[0b10], next_offset[0b00]
            next_offset[0b01], next_offset[0b11] = next_offset[0b11], next_offset[0b01]
            c00, c10 = c10, c00
            c01, c11 = c11, c01
        p00 -= c00
        p01 -= c01
        p10 -= c10
        p11 -= c11
        next_offset[0b00] += p00
        next_offset[0b01] += p01
        next_offset[0b10] += p10
        next_offset[0b11] += p11
        next_offset[0b00], next_offset[0b01] = next_offset[0b01], next_offset[0b00]
        next_offset[0b11], next_offset[0b10] = next_offset[0b10], next_offset[0b11]
        dfs2(child, current, next_offset)
    return

dfs2(0, -1, [0, 0, 0, 0])
for i in range(N):
    print(ans[i])
