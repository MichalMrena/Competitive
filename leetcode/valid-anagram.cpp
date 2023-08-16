#include <cstring>
#include <string>

bool solve(std::string s, std::string t)
{
    if (s.size() != t.size())
    {
        return false;
    }
    int sFreq['z' - 'a' + 1]{};
    int tFreq['z' - 'a' + 1]{};
    for (int i = 0; i < s.size(); ++i)
    {
        ++sFreq[s[i] - 'a'];
        ++tFreq[t[i] - 'a'];
    }
    return not std::memcmp(sFreq, tFreq, sizeof(sFreq));
}

int main()
{
    solve("foo", "boo");
}