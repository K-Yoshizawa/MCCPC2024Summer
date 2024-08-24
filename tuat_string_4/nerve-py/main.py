#!/usr/bin/pypy3

# author : Nerve

from sys import stdin, stdout
from collections import defaultdict

class Modint(int):
    mod = 998244353

    def modpow(self, i: int, r: int) -> int:
        return pow(i, r, Modint.mod)

    def modinv(self, i: int, r: int = 1) -> int:
        return pow(i, Modint.mod - 1 - r, Modint.mod)

    def __add__(self, other):
        return Modint(int.__add__(self, other) % Modint.mod)

    def __sub__(self, other):
        return Modint(int.__sub__(self, other) % Modint.mod)

    def __mul__(self, other):
        return Modint(int.__mul__(self, other) % Modint.mod)

    def __floordiv__(self, other):
        return Modint(int.__mul__(self, self.modinv(other)) % Modint.mod)

    __truediv__ = __floordiv__

    def __pow__(self, other):
        return Modint(self.modpow(self, other))

    def __radd__(self, other):
        return Modint(int.__add__(other, self) % Modint.mod)

    def __rsub__(self, other):
        return Modint(int.__sub__(other, self) % Modint.mod)

    def __rmul__(self, other):
        return Modint(int.__mul__(other, self) % Modint.mod)

    def __rfloordiv__(self, other):
        return Modint(int.__mul__(other, self.modinv(self)) % Modint.mod)

    __rtruediv__ = __rfloordiv__

    def __rpow__(self, other):
        return Modint(self.modpow(other, self))

    def __iadd__(self, other):
        self = self.__add__(other)
        return self

    def __isub__(self, other):
        self = self.__sub__(other)
        return self

    def __imul__(self, other):
        self = self.__mul__(other)
        return self

    def __ifloordiv__(self, other):
        self = self.__mul__(self.modinv(other))
        return self

    def __neg__(self):
        return (self.mod - self) % self.mod

    __itruediv__ = __ifloordiv__

    def __ipow__(self, other):
        self = Modint(self.modpow(self, other))
        return self

MAX_M = 1000

# (S_i, S_j) を数える
counts = [[Modint(0) for _ in range(MAX_M)] for _ in range(MAX_M)]

def main():
    input = stdin.read
    data = input().split()

    N = int(data[0])
    M = int(data[1])
    C = list(map(int, data[2:N+2]))
    C = [x - 1 for x in C]

    left_sum = [Modint(0) for _ in range(M)]
    idx = 0

    for i in range(N):
        for j in range(M):
            if C[i] == j:
                continue
            counts[j][C[i]] += left_sum[j]
        left_sum[C[i]] += Modint(1)

    ans = Modint(0)
    right_sum = [Modint(0) for _ in range(M)]

    allsum = [Modint(0) for _ in range(M)]
    for i in range(M):
        for j in range(M):
            allsum[i] += counts[i][j]

    for i in reversed(range(N)):
        for j in range(M):
            if C[i] == j:
                continue
            ans += (allsum[j] - counts[j][C[i]]) * right_sum[j]

        right_sum[C[i]] += Modint(1)

        for j in range(M):
            if C[i] == j:
                continue
            counts[j][C[i]] -= left_sum[j]
            allsum[j] -= left_sum[j]

        left_sum[C[i]] -= Modint(1)

    stdout.write(str(ans) + '\n')

if __name__ == "__main__":
    main()
