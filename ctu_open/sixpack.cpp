#include <iostream>
#include <vector>
#include <array>
#include <algorithm>

using namespace std;

using ll = long long;

constexpr int EMPTY {-1};
constexpr ll RES_MOD {1'000'000'007};
constexpr array<int, 19> UNIQUE_SUMS {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};

int N, K, M;

vector<array<int, 19>> col_ways;
array<vector<int>, 2> grid;
array<int, 3> lower_bounds;

int main_sixpack()
{
    cin >> N >> K >> M;

    col_ways.resize(N, {});
    grid[0].resize(N, EMPTY);
    grid[1].resize(N, EMPTY);

    for (int m {0}; m < M; ++ m)
    {
        int col_i, row_i, val;
        cin >> col_i >> row_i >> val;
        grid[row_i][col_i] = val;
    }

    for (int col_i {0}; col_i < N; ++col_i)
    {
        if (grid[0][col_i] == EMPTY && grid[1][col_i] == EMPTY)
        {
            col_ways[col_i] = UNIQUE_SUMS;
        }
        else if (grid[0][col_i] == EMPTY || grid[1][col_i] == EMPTY)
        {
            int val {grid[0][col_i] == EMPTY ? grid[1][col_i] : grid[0][col_i]};
            for (int secondVal {0}; (val + secondVal) <= min(18, K) && secondVal <= 9; ++secondVal)
            {
                col_ways[col_i][val + secondVal] = 1;
            }
            lower_bounds[col_i % 3] = max(lower_bounds[col_i % 3], val);
        }
        else
        {
            col_ways[col_i][ grid[0][col_i] + grid[1][col_i] ] = 1;

            lower_bounds[col_i % 3] = max(lower_bounds[col_i % 3], grid[0][col_i] + grid[1][col_i]);
        }
    }

    ll result {0};

    for (int c1 {lower_bounds[0]}; c1 <= 18 && c1 <= K; ++c1)
    {
        for (int c2 {lower_bounds[1]}; (c2 <= 18) && (c1 + c2 <= K); ++c2)
        {
            for (int c3 {lower_bounds[2]}; (c3 <= 18) && (c1 + c2 + c3 <= K); ++c3)
            {
                if (c1 + c2 + c3 != K) continue;
                
                int comb[3] {c1, c2, c3};
                ll subResult {1};
                
                for (int col_i {0}; col_i < N; ++col_i)
                {
                    int waysNum {col_ways[col_i][ comb[col_i % 3] ]};

                    if (0 == waysNum)
                    {
                        subResult = 0;
                        break;
                    }

                    subResult = ((subResult % RES_MOD) * (waysNum % RES_MOD)) % RES_MOD;
                }

                result += subResult;
                result %= RES_MOD;
            }
        }
    }

    cout << result << '\n';

	return 0;
}