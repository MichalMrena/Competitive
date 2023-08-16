#include <unordered_set>
#include <vector>

bool solve(std::vector<int> const& nums)
{
    std::unordered_set<int> memo;
    memo.reserve(nums.size());
    for (int const num : nums)
    {
        if (not memo.insert(num).second)
        {
            return true;
        }
    }
    return false;
}

int main()
{
    solve({1,1,2,3});
}