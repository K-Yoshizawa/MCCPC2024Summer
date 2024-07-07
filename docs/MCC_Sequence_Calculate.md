# MCC Sequence (Calculate Ver.)

## 問題文

長さ $n$ の数列 $a = (a_1, \dots, a_n)$ に対し、 $f(a)$ を次の条件をすべて満たす整数 $(i, j, k)$ の組の個数と定めます。

- $1 \le i < j < k \le n$
- $A_i \ne A_j$
- $A_i \ne A_k$
- $A_j = A_k$

長さ $N$ の数列 $A = (A_1, \dots, A_N)$ が与えられます。 $f(A)$ の値を求めてください。

## 制約

- $3 \le N \le 2 \times 10^5$
- $1 \le A_i \le N$
- 入力はすべて整数

## 入力

入力は以下の形式で標準入力から与えられます。

<div class="code-math">

$N$ \
$A_1 \ \ \dots \ \ A_N$

</div>

## 出力

答えを $1$ 行に出力してください。

## 想定解法

後ろから見ていく