#!/usr/bin/pypy3

import sys
sys.setrecursionlimit(10 ** 7)

def main():
    s = input().strip()
    N = len(s)
    right = [-1] * N

    # 括弧の対応を記録
    st = []
    for i in range(N - 1, -1, -1):
        if s[i] == '(':
            right[i] = st.pop()
        elif s[i] == ')':
            st.append(i)

    def dfs(le, ri, gd, hf):
        if not hf:
            result = []
            i = le
            while i < ri:
                num = ord(s[i]) - ord('0')
                if 0 <= num < 10:
                    result.append(str(min(9, num + gd)))
                else:
                    if s[i] == '+':
                        pass
                    elif s[i] == 'G':
                        result.append(dfs(i + 2, right[i + 1], gd + 1, 0))
                        i = right[i + 1]
                    else:
                        pos = dfs(i + 2, right[i + 1], 0, 1)
                        for e in pos:
                            nn = ord(e) - ord('0')
                            result.append(str(min(9, nn + gd)))
                        i = right[i + 1]
                i += 1
            return ''.join(result)
        else:
            sum_val = 0
            i = le
            while i < ri:
                num = ord(s[i]) - ord('0')
                if 0 <= num < 10:
                    sum_val += min(9, num + gd)
                else:
                    if s[i] == '+':
                        pass
                    elif s[i] == 'G':
                        sum_val += int(dfs(i + 2, right[i + 1], gd + 1, 1))
                        i = right[i + 1]
                    else:
                        pos = dfs(i + 2, right[i + 1], 0, 1)
                        for e in pos:
                            nn = ord(e) - ord('0')
                            sum_val += min(9, nn + gd)
                        i = right[i + 1]
                i += 1
            return str(sum_val)

    print(dfs(0, N, 0, 0))

if __name__ == "__main__":
    main()