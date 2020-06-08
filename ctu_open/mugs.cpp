#include <cmath>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <string>

using namespace std;

int N;
vector<int> masks;
vector<int> states;

inline int char_to_mask(char c)
{
    return 1 << (c - 'a');
}

inline int two_pow(int exp)
{
    return 1 << exp;
}

inline int flip_bit(int mask, int i)
{
    return mask ^ (1 << i);
}

constexpr int NOT_VISITED {-1};

int main_mugs()
{
    states.resize(two_pow(20) + 1, NOT_VISITED);
    states[0] = 0;

    string line;
    getline(cin, line);
    N = stoi(line);
    masks.resize(N + 1, 0);
    
    getline(cin, line);
    masks[1] = char_to_mask(line[0]);

    for (size_t i {2}; i <= N; ++i)
    {
        masks[i] = masks[i - 1] ^ char_to_mask(line[i - 1]);
    }

    int maxLenSoFar {1};

    for (int i {1}; i <= N; ++i)
    {
        int currMask = masks[i];

        int leftmost = 1'000'000;
        // check same maska
        if (NOT_VISITED == states[currMask])
        {
            states[currMask] = i;
        }
        else
        {
            leftmost = min(leftmost, states[currMask]);
        }
        
        // check one bit different masky
        for (int j {0}; j < 20; ++j)
        {
            int possibleLeft {states[flip_bit(currMask, j)]};
            if (NOT_VISITED == possibleLeft)
            {
                continue;
            }
            leftmost = min(leftmost, possibleLeft);
        }
        
        int possibleLength = i - leftmost;
        if (possibleLength > maxLenSoFar)
        {
            maxLenSoFar = possibleLength;
        }
    }

    cout << maxLenSoFar << '\n';

	return 0;
}