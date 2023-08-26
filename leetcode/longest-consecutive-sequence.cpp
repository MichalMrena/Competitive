#include <algorithm>
#include <iostream>
#include <vector>

int solve(std::vector<int> nums)
{
    // Faster than "O(n)" hash-set solution...

    if (nums.size() == 0)
    {
        return 0;
    }

    std::sort(nums.begin(), nums.end());

    auto it = nums.begin();
    auto endIt = nums.end();
    int max = 1;
    int prev = *it;
    ++it;
    for (;;)
    {
        int len = 1;
        for (;;)
        {
            if (it == endIt)
            {
                break;
            }

            if (*it == prev)
            {
                ++it;
                continue;
            }

            if (*it != prev + 1)
            {
                prev = *it;
                break;
            }

            prev = *it;
            ++len;
            ++it;
        }
        max = std::max(len, max);
        if (it == endIt)
        {
            break;
        }
        ++it;
    }
    return max;
}

int main()
{
    std::cout << solve({100,4,200,1,3,2}) << "\n";
    std::cout << solve({0,3,7,2,5,8,4,6,0,1,8,8}) << "\n";
    std::cout << solve({}) << "\n";
    std::cout << solve({2}) << "\n";
    std::cout << solve({3,10}) << "\n";
    std::cout << solve({2,3,10}) << "\n";
    std::cout << solve({9,1,4,7,3,-1,0,5,8,-1,6}) << "\n";
}