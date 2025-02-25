# MCC Sequence (Calculate Version)

## 問題文

長さ $n$ の数列 $a = (a_1, \dots, a_n)$ に対し、 $f(a)$ を次の条件をすべて満たす整数 $(i, j, k)$ の組の個数と定めます。

- $1 \le i < j < k \le n$
- $A_i \ne A_j$
- $A_i \ne A_k$
- $A_j = A_k$

長さ $N$ の数列 $A = (A_1, \dots, A_N)$ が与えられます。 $f(A)$ の値を求めてください。

## 制約

### Hard

- $3 \le N \le 2 \times 10^5$
- $1 \le A_i \le N$
- 入力はすべて整数

### Easy

- Hard の制約に以下の制約を追加
- $3 \le N \le 100$

## 入力

入力は以下の形式で標準入力から与えられます。

<div class="code-math">

$N$ \
$A_1 \ \ \dots \ \ A_N$

</div>

## 出力

答えを $1$ 行に出力してください。

## 入力例1
```
5
1 2 2 3 3
```

## 出力例1
```
4
```

条件を満たす $(i, j, k)$ の組は次の $4$ つです。

- $(1, 2, 3)$
- $(1, 4, 5)$
- $(2, 4, 5)$
- $(3, 4, 5)$

よって、 $f(A) = 4$ より、 $4$ を出力してください。

この入出力例は Easy・Hard の制約を満たします。

## 入力例2
```
9
9 9 8 2 4 4 3 5 3
```

## 出力例2
```
10
```

この入出力例は Easy・Hard の制約を満たします。