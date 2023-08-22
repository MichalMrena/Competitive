#include <algorithm>
#include <iostream>
#include <vector>

struct FreqPair
{
    int num_;
    int freq_;
};

std::vector<int> solve(std::vector<int> const& nums, int k)
{
    constexpr int Base = 10'000;
    std::vector<int> freq(2 * Base + 2, 0);
    for (int const num : nums)
    {
        ++freq[Base + num];
    }

    std::vector<FreqPair> pairs;
    pairs.reserve(freq.size());
    for (int i = 0; i < freq.size(); ++i)
    {
        if (freq[i] != 0)
        {
            pairs.push_back(FreqPair{i - Base, freq[i]});
        }
    }

    std::partial_sort(
        pairs.begin(),
        pairs.begin() + k,
        pairs.end(),
        [](FreqPair lhs, FreqPair rhs){ return rhs.freq_ < lhs.freq_; }
    );
    pairs.resize(k);
    std::vector<int> result;
    result.reserve(k);
    for (int i = 0; i < k; ++i)
    {
        result.push_back(pairs[i].num_);
    }
    return result;
}

int main()
{
    for (int const num : solve({-3,-3,-3,1,1,1,1,2,2,2,3}, 3))
    {
        std::cout << num << ",";
    }
    std::cout << "\n";

    for (int const num : solve({1}, 1))
    {
        std::cout << num << ",";
    }
    std::cout << "\n";
}