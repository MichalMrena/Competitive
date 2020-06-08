#include <iostream> 
#include <cstddef>
#include <vector>
#include <cmath>
#include <algorithm>
#include <array>
#include <map>

using namespace std; 
using ull = int64_t;

bool is_odd(ull n)
{
    return n & 1;
}

bool is_even(ull n)
{
    return !is_odd(n);
}

ull gcd(ull a, ull b)
{
    return !b ? a : gcd(b, a % b);
}

ull mul_mod(ull a, ull b, ull m)
{
    ull x = 0;
    ull y = a % m;

    while (b > 0)
    {
        if (is_odd(b))
        {
            x = (x + y) % m;
        }
        y = (y * 2) % m;
        b /= 2;
    }
    
    return x % m;
}

ull pow_mod(ull base, ull exp, ull m)
{
    ull res = 1;    
    base = base % m;
   
    if (base == 0) return 0;
  
    while (exp > 0)  
    {  
        if (is_odd(exp))  
        {
            res = mul_mod(res, base, m);
        }
  
        exp = exp / 2;
        base = mul_mod(base, base, m);
    }  

    return res; 
}

void miller_r_d(ull n, ull& r, ull& d)
{
    r = 0;
    n &= ~1;

    while (is_even(n))
    {
        ++r;
        n /= 2;
    }    

    d = n;
}

bool is_prime_miller(ull n)
{
    if (1 == n)     return false;
    if (2 == n)     return true;
    if (is_even(n)) return false;

    static constexpr array<ull, 12> as = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};

    ull r;
    ull d;
    miller_r_d(n, r, d);

    for (ull a : as)
    {
        if (!(a >= 2 && a <= min(n - 2.0, 2 * log(n) * log(n)))) continue;

        ull x = pow_mod(a, d, n);
        if (1 == x || n - 1 == x) continue;

        bool finished = true;
        for (ull i = 0; i < r - 1; ++i)
        {
            x = mul_mod(x, x, n);
            if (n - 1 == x) { finished = false; break; }
        }

        if (finished) return false;
    }

    return true;
}

ull get_divisor(ull n)
{
    if(is_even(n)) return 2;

    ull x = rand() % n + 1;
    ull c = rand() % n + 1;
    ull y = x;
    ull g = 1;

    while (g == 1)
    {
        x = (mul_mod(x, x, n) + c) % n;
        y = (mul_mod(y, y, n) + c) % n;
        y = (mul_mod(y, y, n) + c) % n;
        g = gcd(std::abs(x - y), n);
    }

    return g;
}

void solve_step(ull n, map<ull, ull>& fs)
{
    if (1 == n)      { return; }
    if (is_prime_miller(n)) { ++fs[n]; return; }

    ull div = get_divisor(n);
    solve_step(div, fs);
    solve_step(n / div, fs);
}

map<ull, ull> solve(ull n)
{
    if (1 == n)
    {
        return {{1, 1}};
    }

    map<ull, ull> fs;
    solve_step(n, fs);    
    return fs;
}

void show(ull n, map<ull, ull> const& fs)
{
    cout << n << " = ";

    auto last = fs.rbegin()->first;

    for (auto& pair : fs)
    {
        cout << pair.first;

        if (pair.second > 1)
        {
            cout << '^' << pair.second;
        }

        if (pair.first != last)
        {
            cout << " * ";
        }
    }

    cout << endl;
}

// https://onlinejudge.org/external/114/11476.pdf
// https://en.wikipedia.org/wiki/Pollard%27s_rho_algorithm
// https://en.wikipedia.org/wiki/Miller%E2%80%93Rabin_primality_test
int main() 
{ 
    size_t N;
    cin >> N;

    for (size_t i = 0 ; i < N; ++i)
    {
        ull n;
        cin >> n;
        show(n, solve(n));
    }

    return 0; 
}