# UVA 100 The 3n + 1 problem
[problem description](https://uva.onlinejudge.org/external/1/p100.pdf)

I am starting with Haskell so here is code:
```
maxSequenceLenght i j = maximum (map sequenceLenght (if i < j then [i..j] else [j..i]))
    where sequenceLenght 1 = 1          
          sequenceLenght n = 1 + sequenceLenght (if even n then div n 2 else 3 * n + 1)	
```