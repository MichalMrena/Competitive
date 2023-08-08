#include <array>
#include <cstring>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

const int FREQ_TAB_ELEM_COUNT = 'z' - 'a' + 1;
const int FREQ_TAB_BYTE_COUNT = sizeof(int) * FREQ_TAB_ELEM_COUNT;

struct TableHash
{
    std::size_t operator()(std::array<int, FREQ_TAB_ELEM_COUNT> const& xs) const
    {
        std::size_t seed = 0;
        std::hash<int> hasher;
        for (int const x : xs)
        {
            seed ^= hasher(x) + 0x9e3779b9 + (seed<<6) + (seed>>2);
        }
        return seed;
    }
};

struct TableEquals
{
    bool operator()(
        std::array<int, FREQ_TAB_ELEM_COUNT> const& lhs,
        std::array<int, FREQ_TAB_ELEM_COUNT> const& rhs
    ) const
    {
        return 0 == std::memcmp(lhs.data(), rhs.data(), FREQ_TAB_BYTE_COUNT);
    }
};

std::vector<std::vector<std::string>> solve(std::vector<std::string>& strs)
{
    std::unordered_map<
        std::array<int, FREQ_TAB_ELEM_COUNT>,
        std::vector<std::string>,
        TableHash,
        TableEquals
    > groupMap;

    for (std::string& str : strs)
    {
        std::array<int, FREQ_TAB_ELEM_COUNT> table {{}};
        for (char const letter : str)
        {
            ++table[letter - 'a'];
        }

        auto groupIt = groupMap.find(table);
        if (groupIt == groupMap.end())
        {
            auto [newIt, isIn] = groupMap.emplace(table, std::vector<std::string>());
            groupIt = newIt;
        }

        groupIt->second.push_back(std::move(str));
    }

    std::vector<std::vector<std::string>> groups;
    for (auto& [key, group] : groupMap)
    {
        groups.push_back(std::move(group));
    }

    return groups;
}

int main()
{
    std::vector<std::string> strs;
    solve(strs);
}