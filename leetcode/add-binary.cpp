#include <algorithm>
#include <string>

auto solve(std::string a, std::string b) -> std::string
{
    std::size_t const longer = std::max(a.size(), b.size());
    std::string c(longer, 'x');
    std::size_t i = 0;
    int carry = 0;
    while (i < longer)
    {
        int const bitA = i < a.size() ? a[a.size() - i - 1] - '0' : 0;
        int const bitB = i < b.size() ? b[b.size() - i - 1] - '0' : 0;
        int const sum  = bitA + bitB + carry;
        int const bitC = sum % 2;
        carry = sum > 1;
        c[c.size() - i - 1] = bitC + '0';
        ++i;
    }
    return carry ? "1" + c : c;
}

int main()
{
    solve("11", "1");
}