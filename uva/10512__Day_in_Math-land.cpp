#include <iostream> 
#include <vector>
#include <cmath>
#include <algorithm>

double P, Q;

struct solution
{
    double X;
    double Y;
    solution(double x, double y) : X {x}, Y {y} {}
};

bool is_int(double n)
{
    return std::abs(std::round(n) - n) < 1e-8;
}

bool is_zero(double d)
{
    return std::abs(d) < 1e-8;
}

int to_int(double d)
{
    return static_cast<int>(std::round(d));
}

bool is_valid_num(double d)
{
    return !std::isnan(d) && is_int(d);
}

bool is_valid_pair(double x, double y)
{
    if (!is_valid_num(x) || !is_valid_num(y)) return false;

    auto const xInt = to_int(x);
    auto const yInt = to_int(y);

    if (xInt < yInt) return false;

    auto const pTest = (xInt + yInt) * yInt;
    auto const qTest = (xInt - yInt) * xInt;

    return pTest == P && qTest == Q;
}

solution min_x(std::vector<solution> const& ps)  
{
    return *std::min_element(ps.begin(), ps.end(), 
            [](solution const& s1, solution const& s2) { return s1.X < s2.X; });
}

std::vector<solution> solve()
{
    std::vector<solution> ps;

    double const y1 =   std::sqrt((1.0 / 4) * (3 * P + Q + std::sqrt(Q * Q + P * P + 6 * P * Q)));
    double const y2 =   std::sqrt((1.0 / 4) * (3 * P + Q - std::sqrt(Q * Q + P * P + 6 * P * Q)));
    double const y3 = - std::sqrt((1.0 / 4) * (3 * P + Q + std::sqrt(Q * Q + P * P + 6 * P * Q)));
    double const y4 = - std::sqrt((1.0 / 4) * (3 * P + Q - std::sqrt(Q * Q + P * P + 6 * P * Q)));

    double const x1 = is_zero(y1) ? std::sqrt(Q) : (P - y1 * y1) / y1;
    double const x2 = is_zero(y2) ? std::sqrt(Q) : (P - y2 * y2) / y2;
    double const x3 = is_zero(y3) ? std::sqrt(Q) : (P - y3 * y3) / y3;
    double const x4 = is_zero(y4) ? std::sqrt(Q) : (P - y4 * y4) / y4;

    if (is_valid_pair(x1, y1)) ps.emplace_back(x1, y1);
    if (is_valid_pair(x2, y2)) ps.emplace_back(x2, y2);
    if (is_valid_pair(x3, y3)) ps.emplace_back(x3, y3);
    if (is_valid_pair(x4, y4)) ps.emplace_back(x4, y4);

    return ps;
}

void show(size_t i, std::vector<solution> const& ps)
{
    std::cout << "Case " << i << ':' << std::endl;
    if (ps.empty())
    {
        std::cout << "Impossible." << std::endl;
    }
    else
    {
        std::cout << to_int(min_x(ps).X) << ' ' << to_int(min_x(ps).Y) << std::endl;
    }
}

// https://onlinejudge.org/external/105/10512.pdf
int main() 
{ 
    size_t N;
    std::cin >> N;

    for (size_t i = 1; i <= N; ++i)
    {
        std::cin >> P >> Q;
        show(i, solve());
    }

    return 0; 
}