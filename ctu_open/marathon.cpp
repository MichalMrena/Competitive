#include <cmath>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>

#include <fstream>

using namespace std;

using ll = long long;

vector<ll> r;
vector<ll> Ks;

ll N, K;

auto calc_abs_diff (ll shift) -> ll
{
    ll absMove {0};

    for (ll i {0}; i < N; i++)
    {
        absMove += abs((r[i] - Ks[i] + shift));
    }

    return absMove;
}

ll my_max(ll n1, ll n2)
{
    return n1 > n2 ? n1 : n2;
}

int main_marathon()
{
	cin >> N >> K;

	r.resize(N);
	Ks.resize(N);

	for (ll i = 0; i < N; i++)
	{
		cin >> r[i];
	}
	std::sort(r.begin(), r.end());

	for (ll i {0}; i < N; i++)
	{
		Ks[i] = r[0] + K * i;
	}

    const ll span {max((N - 1) * K, r.back() - r[0])};
    ll left  {-span};
    ll right {span};
	for (;;)
	{
		if (right - left <= 1) break;

        double third {(right - left) / 3.0};
        ll leftThird  {left + my_max((ll)floor(third), 1)};
        ll rightThird {right - my_max((ll)ceil(third), 1)};

        ll fLeftThird {calc_abs_diff(leftThird)};
        ll fRightTHird {calc_abs_diff(rightThird)};

        if (fLeftThird > fRightTHird)
        {
            left = leftThird;            
        }
        else
        {
            right = rightThird;
        }
	}

    cout << min(calc_abs_diff(left), calc_abs_diff(right)) << '\n';

	return 0;
}