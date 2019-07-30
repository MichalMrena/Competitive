# UVA 100 The 3n + 1 problem
[problem description](https://uva.onlinejudge.org/external/1/p100.pdf)

This sequence is called [Collatz conjecture](https://en.wikipedia.org/wiki/Collatz_conjecture). Its quite interesting.

I am starting with Haskell so here is some code:
```
maxSequenceLenght i j = maximum (map sequenceLenght integersBetween)
    where
      integersBetween  = if i < j then [i..j] else [j..i]
      sequenceLenght 1 = 1          
      sequenceLenght n = 1 + sequenceLenght (if even n then div n 2 else 3 * n + 1)
```