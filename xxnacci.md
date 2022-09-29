# XXNACCI NUMBER

## はじめに

ARM NEON を使ってみたかった。
適当に練習になりそうなお題を考えた。
とりあえず行列積とかを書いてみたかった。
そういえば fibonacci 数列の第n項を求めるのに行列積とか使ってやるみたいなのがあったなあ。
fibonacci 数列だと2x2の行列同士の積だから、少しサイズが小さいなあ。
tribonacci 数列だと3x3 かー。tetranacci は4x4, pentanacci は5x5, ...。
よし、なんか大きい??nacci数列の第n項を求めるみたいなのをやってみよう。

## 計算方法

### fibonacci 数列の場合

$$
\begin{pmatrix}
f_2 \\
f_1 \\
\end{pmatrix}
=
\begin{pmatrix}
1 & 1\\
1 & 0\\
\end{pmatrix}
\cdot
\begin{pmatrix}
f_1 \\
f_0 \\
\end{pmatrix}
$$

$$
\begin{pmatrix}
f_{n + 1} \\
f_n \\
\end{pmatrix}
=
\begin{pmatrix}
1 & 1\\
1 & 0\\
\end{pmatrix}^n
\cdot
\begin{pmatrix}
f_1 \\
f_0 \\
\end{pmatrix}
$$

### tribonacci

$$
\begin{pmatrix}
f_{n + 2} \\
f_{n + 1} \\
f_n \\
\end{pmatrix}
=
\begin{pmatrix}
1 & 1 & 1\\
1 & 0 & 0\\
0 & 1 & 0\\
\end{pmatrix}^n
\cdot
\begin{pmatrix}
f_2 \\
f_1 \\
f_0 \\
\end{pmatrix}
$$

### tetranacci

$$
\begin{pmatrix}
f_{n + 3} \\
f_{n + 2} \\
f_{n + 1} \\
f_n \\
\end{pmatrix}
=
\begin{pmatrix}
1 & 1 & 1 & 1\\
1 & 0 & 0 & 0\\
0 & 1 & 0 & 0\\
0 & 0 & 1 & 0\\
\end{pmatrix}^n
\cdot
\begin{pmatrix}
f_3 \\
f_2 \\
f_1 \\
f_0 \\
\end{pmatrix}
$$

## アルゴリズム

行列の累乗を計算するアルゴリズムを考える必要がある。
今回は繰り返し2乗法を用いて計算する。

$$
\begin{pmatrix}
1 & 1 \\
1 & 0 \\
\end{pmatrix}^{27}
=
\begin{pmatrix}
1 & 1 \\
1 & 0 \\
\end{pmatrix}^{11011_{(2)}}
=
\begin{pmatrix}
1 & 1 \\
1 & 0 \\
\end{pmatrix}^{16}
\cdot
\begin{pmatrix}
1 & 1 \\
1 & 0 \\
\end{pmatrix}^{8}
\cdot
\begin{pmatrix}
1 & 1 \\
1 & 0 \\
\end{pmatrix}^{2}
\cdot
\begin{pmatrix}
1 & 1 \\
1 & 0 \\
\end{pmatrix}^{1}
$$

行列積をする回数は$O(\log n)$回



## 実装


neon median : 88514 micro sec.  normal median : 303814 micro sec.
## 感想

- 記念すべきNEON初体験
  - 当然もっと速くなるんだろうけど、一応定数倍高速になったという意味では成功
- 意外と何すればいいか分からなくて写経
- 次何やろうか

## 参考

https://developer.arm.com/documentation/102467/0100/Matrix-multiplication-example?lang=en
