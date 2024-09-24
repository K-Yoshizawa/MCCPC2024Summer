#!/usr/bin/pypy3

import sys
import math
from collections import namedtuple

sys.setrecursionlimit(10 ** 7)

MOD7 = 1000000007
MOD998 = 998244353
INF = (1 << 60)
eps = 1e-9

Event = namedtuple('Event', ['x', 'y', 'd', 'id', 'flag', 's'])
Query = namedtuple('Query', ['id', 'flag'])

def shogen(x, y):
    if y >= 0:
        if x > 0:
            return 1
        else:
            return 2
    else:
        if x >= 0:
            return 4
        else:
            return 3

def main():
    n = int(input())
    x = []
    y = []
    r = []
    
    for _ in range(n):
        xi, yi, ri = map(int, input().split())
        x.append(xi)
        y.append(yi)
        r.append(ri)

    events = []
    for i in range(n):
        base = math.atan2(y[i], x[i])
        d = x[i] * x[i] + y[i] * y[i] - r[i] * r[i]
        len = math.sqrt(d)
        th = math.acos(len / math.sqrt(x[i] * x[i] + y[i] * y[i]))
        
        # First event
        X1 = len * x[i] - r[i] * y[i]
        Y1 = len * y[i] + r[i] * x[i]
        events.append(Event(X1, Y1, d, i, 0, shogen(X1, Y1)))
        
        # Second event
        X2 = len * x[i] + r[i] * y[i]
        Y2 = len * y[i] - r[i] * x[i]
        events.append(Event(X2, Y2, d, i, 1, shogen(X2, Y2)))

    from functools import cmp_to_key
    
    def cmp(a, b):
        if a.s == b.s and abs(a.x * b.y - a.y * b.x) < eps:
            return -1 if a.flag < b.flag else 1
        if a.s != b.s:
            return -1 if a.s < b.s else 1
        return -1 if a.x * b.y - a.y * b.x > 0 else 1

    # Sort events
    events.sort(key=cmp_to_key(cmp))
    
    querys = []
    dist = [0] * n
    for i in range(n * 2):
        X, Y, d, idx, flag, s = events[i]
        dist[idx] = d
        querys.append(Query(idx, flag))
    
    querys += querys
    st = set()
    ans = set()
    Min = -1

    for i in range(n * 4):
        idx, flag = querys[i]
        if flag:
            st.add(dist[idx])
            if abs(dist[idx] - min(st)) < eps:
                Min = idx
        else:
            itr = min((x for x in st if abs(x - dist[idx]) < eps), default=None)
            if itr is not None:
                st.remove(itr)
            if Min == -1:
                continue
            if dist[idx] < dist[Min]:
                Min = -1
            if Min == idx:
                if i >= n * 2:
                    ans.add(idx + 1)
                Min = -1

    answer = list(ans)
    answer.sort()
    print(" ".join(map(str, answer)))

if __name__ == "__main__":
    main()
