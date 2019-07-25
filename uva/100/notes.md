# UVA 100 The 3n + 1 problem
[problem description](https://uva.onlinejudge.org/external/1/p100.pdf)

I am starting with Haskell so here is lets say some solution:
```
maxSequenceLenght :: Int -> Int -> Int
maxSequenceLenght i j = maximum (sequenceLenghts (allIntsBetween i j))
    where allIntsBetween i j
              | i < j     = [i..j]
              | otherwise = [j..i]

          nextN n 
              | even n    = div n 2
              | otherwise = 3 * n + 1
          sequenceForN 1 = [1]
          sequenceForN n = n:sequenceForN (nextN n)

          sequenceLenghts ns = [length (sequenceForN n) | n <- ns]	
```