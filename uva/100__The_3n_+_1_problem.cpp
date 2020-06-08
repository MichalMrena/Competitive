#include <iostream>
#include <map>

using uint = unsigned int;

std::map<uint, uint> memo;

uint sequenceLength(uint n)
{
    if (1 == n) return 1;
    if (memo.find(n) != memo.end()) return memo.at(n);

    uint const nextN    = 1 & n ? 3 * n + 1 : n >> 1;
    uint const nextNLen = sequenceLength(nextN);

    memo.emplace(nextN, nextNLen);

    return 1 + nextNLen;
}

// https://onlinejudge.org/external/1/100.pdf
// https://en.wikipedia.org/wiki/Collatz_conjecture
int main()
{
    uint i, j;
    while (std::cin >> i)
    {
        std::cin >> j;
        std::cout << i << " " << j << " ";

        if (j < i) std::swap(i, j);

        uint maxLen = 0;
        for (uint k = i; k <= j; ++k)
        {
            maxLen = std::max(maxLen, sequenceLength(k));
        }

        std::cout << maxLen << '\n';
    }

    return 0;
}