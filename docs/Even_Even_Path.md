# Subtree Flip Path Count

## 問題文

$N$ 頂点の根付き木 $T$ が与えられます。

頂点には $1, 2, \dots, N$ の番号が付けられており、頂点 $1$ が根です。
頂点 $i$ は重み $V_i \in \lbrace 0, 1 \rbrace$ を持ちます。また、辺には $1, 2, \dots, N - 1$ の番号が付けられており、辺 $i$ は頂点 $A_i, B_i$ を結んでいます。

$T$ 上のパスの**重み**を、パス上に現れる頂点の重みの総和と定義します。また、パスの**長さ**を、パス上に現れる辺の本数と定義します。

根付き木 $G$ に対し、$f(G)$ を $G$ に含まれる**重み**と**長さ**が共に偶数であるパスの個数と定義します。

$f(T)$ を求めてください。続けて、$i = 1, \dots, N$ について次の問題を解いてください。

> $T$ について、頂点 $i$ を根とする部分木に含まれるすべての頂点(頂点 $i$ も含む)から成る集合を $S_i$ とする。
> 
> $j \in S_i$ について、$V_j$ を $1 - V_j$ に置き換えた後の木を $T_i$ とする。$f(T_i)$ を求めよ。

## 制約

### Final (***点)

- $1 \le N \le 10^5$
- $V_i \in \lbrace 0, 1 \rbrace$
- $1 \le A_i < B_i \le N$
- $T$ は木
- 入力はすべて整数

### Hard (***点)

- Final の制約に以下の制約を追加
- $1 \le N \le 10^5$
- $A_i = \left\lfloor\frac{i + 1}{2}\right\rfloor, B_i = i + 1$ (ただし $\left\lfloor x\right\rfloor$ は $x$ を超えない最大の整数)

### Normal (***点)

- Final の制約に以下の制約を追加
- $1 \le N \le 1000$
- $A_i = \left\lfloor\frac{i + 1}{2}\right\rfloor, B_i = i + 1$ (ただし $\left\lfloor x\right\rfloor$ は $x$ を超えない最大の整数)

### Easy (***点)

- Final の制約に以下の制約を追加
- $1 \le N \le 100$
- $A_i = \left\lfloor\frac{i + 1}{2}\right\rfloor, B_i = i + 1$ (ただし $\left\lfloor x\right\rfloor$ は $x$ を超えない最大の整数)

## 入力

入力は以下の形式で標準入力から与えられます。

<div class="code-math">

$N$ \
$V_1 \ \ \dots \ \ V_N$ \
$A_1 \ \ B_1$ \
$\ \vdots$ \
$A_{N - 1} \ \ B_{N - 1}$

</div>

## 出力

$N + 1$ 行出力してください。
$1$ 行目には、$f(T)$ の値を出力してください。
$i + 1$ 行目には、$i = 1, \dots, N$ の問題の答えを出力してください。
