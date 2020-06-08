#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

using ll = long long;

int main_family()
{
    int k;
    cin >> k;

    vector<int> valid_lines;

    for (size_t line_num = 1; line_num <= k; line_num++)
    {
        int n;
        cin >> n;

        vector<ll> maxes;
        vector<ll> heighths;
        maxes.reserve(n);
        heighths.reserve(n);

        for (size_t i = 0; i < n; i++)
        {
            ll h;
            cin >> h;
            maxes.push_back(h);
            heighths.push_back(h);
        }

        for (size_t i = maxes.size() - 2; i > 0;)
        {
            --i;
            maxes[i] = max(maxes[i], maxes[i + 1]);
        }

        set<ll> alices;
        alices.insert(heighths[0]);

        for (size_t i = 1; i < n - 1; ++i)
        {
            auto alice_it {alices.upper_bound(heighths[i])};

            if (alice_it != alices.end())
            {
                if (*alice_it < maxes[i + 1])
                {
                    valid_lines.push_back(line_num);
                    break;
                }
            }

            alices.insert(heighths[i]);
        }        
    }

    cout << valid_lines.size() << '\n';
    for (auto vl : valid_lines)
    {
        cout << vl << '\n';
    }

	return 0;
}