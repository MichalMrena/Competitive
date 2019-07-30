#include <limits>
#include <iostream>
#include <map>
#include <fstream>

using uint = unsigned int;

template<class T>
class only_max
{
private:
    T value;

public:
    only_max() : value(std::numeric_limits<T>::min()) {}
    
    T get() 
    {
        return this->value;
    }

    void maybe_set(T val)
    {
        if (val > this->value)
            this->value = val;
    }
};

std::map<uint, uint> memo;

uint sequenceLength(uint n)
{
    if (1 == n)
        return 1;

    if (memo.find(n) != memo.end())
        return memo.at(n);

    uint nextN( 1 & n ? 3 * n + 1 : n >> 1 );
    uint nextNLen( sequenceLength(nextN) );

    memo[nextN] = nextNLen;

    return 1 + nextNLen;
}

int main()
{
    std::ifstream inputFile( "input.txt" );
    // std::istream & input( inputFile );
    std::istream & input( std::cin );
    uint i;
    uint j;

    while (input >> i)
    {
        input >> j;
        std::cout << i << " " << j << " ";

        if (j < i)
            std::swap(i, j);

        only_max<uint> maxLen;
        for (uint k(i); k <= j; ++k)
        {
            maxLen.maybe_set(sequenceLength(k));
        }
        std::cout << maxLen.get() << '\n';
    }

    return 0;
}