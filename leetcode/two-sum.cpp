#include <unordered_map>
#include <vector>

auto solve(std::vector<int> const& numbers, int target) -> std::vector<int>
{
    std::unordered_map<int, int> memo;
    for (int index = 0; index < numbers.size(); ++index)
    {
        int const num = numbers[index];
        int const otherNum = target - num;
        auto const memoIt = memo.find(otherNum);
        if (memoIt != memo.end())
        {
            int const otherIndex = memoIt->second;
            return {otherIndex, index};
        }
        memo.emplace(num, index);
    }
    return {};
}

int main()
{
    solve({2,7,11,15}, 9);
    solve({3,2,4}, 6);
    solve({3,3}, 6);
}