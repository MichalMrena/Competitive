#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include <array>

#include <utility>

using namespace std;

constexpr char WILDCARD {'_'};

string m_line;
string n_line;

array<array<int, 2000>, 11000> MEMO;

auto read_line (string& target) -> int
{
    int tokensExpanded {0};
    string line;
    getline(cin, line);

    ostringstream ostr;
    for (char c : line)
    {
        if (! isdigit(c)) ostr << c;
        else
        {
            ++tokensExpanded;
            for (int i {0}; i < c - '0'; ++i)
                ostr << WILDCARD;   
        }
    }
    
    target = ostr.str();
    return tokensExpanded;
}

auto are_same (char c1, char c2) -> bool
{
    return (c1 == WILDCARD || c2 == WILDCARD)
        || (c1 == c2);
}

auto edit_dist () -> int
{
    for (int i {0}; i <= m_line.length(); ++i)
    {
        for (int j {0}; j <= n_line.length(); ++j)
        {
            if (0 == i)
            {
                MEMO[i][j] = j;
            }
            else if (0 == j)
            {
                MEMO[i][j] = i;
            }
            else if (are_same(m_line[i - 1], n_line[j - 1]))
            {
                MEMO[i][j] = MEMO[i - 1][j - 1];
            }
            else
            {
                auto mins =
                {
                    MEMO[i][j - 1]
                  , MEMO[i - 1][j]
                  , MEMO[i - 1][j - 1] + 1 // replace = remove + insert ...
                };

                MEMO[i][j] = 1 + *min_element(mins.begin(), mins.end());
            }
        }
    }

    return MEMO[m_line.length()][n_line.length()];
}

int main_game()
{
    int result {0};

    result += read_line(m_line);
    result += read_line(n_line);
    result += edit_dist();

    cout << result << '\n';

	return 0;
}