#include <algorithm> 
#include <iostream> 
#include <cmath> 
#include <vector> 

using namespace std; 
  
struct point 
{ 
    double X; 
    double Y; 
}; 
  
struct circle 
{ 
    point C; 
    double R; 
}; 
  
double dist(point const& a, point const& b) 
{ 
    return sqrt(pow(a.X - b.X, 2) + pow(a.Y - b.Y, 2)); 
} 
  
bool contains(circle const& c, point const& p) 
{ 
    return dist(c.C, p) <= c.R; 
} 
  
point get_circle_center(double bx, double by, double cx, double cy) 
{ 
    double B = bx * bx + by * by; 
    double C = cx * cx + cy * cy; 
    double D = bx * cy - by * cx; 
    return { (cy * B - by * C) / (2 * D), 
             (bx * C - cx * B) / (2 * D) }; 
} 
  
circle circle_from(point const& A, point const& B, point const& C) 
{ 
    point I = get_circle_center(B.X - A.X, B.Y - A.Y, 
                                C.X - A.X, C.Y - A.Y); 
  
    I.X += A.X; 
    I.Y += A.Y; 
    return { I, dist(I, A) }; 
} 
  
circle circle_from(point const& A, point const& B) 
{ 
    point C = { (A.X + B.X) / 2.0, (A.Y + B.Y) / 2.0 }; 
    return { C, dist(A, B) / 2.0 }; 
} 
  
bool contains_all(circle const& c, vector<point> const& P) 
{ 
    for (const point& p : P) 
    {
        if (!contains(c, p)) return false; 
    }    

    return true; 
} 
  
circle min_circle_trivial(vector<point>& P) 
{ 
    if (P.empty())          return { { 0, 0 }, 0 }; 
    else if (P.size() == 1) return { P[0], 0 }; 
    else if (P.size() == 2) return circle_from(P[0], P[1]); 
  
    for (int i = 0; i < 3; i++) 
    { 
        for (int j = i + 1; j < 3; j++) 
        { 
            circle c = circle_from(P[i], P[j]); 
            if (contains_all(c, P)) return c; 
        } 
    } 

    return circle_from(P[0], P[1], P[2]); 
} 
  
circle welzl_helper(vector<point>& P, vector<point> R, int n) 
{ 
    if (n == 0 || R.size() == 3) 
    { 
        return min_circle_trivial(R); 
    } 
  
    int idx = rand() % n; 
    point p = P[idx]; 
  
    swap(P[idx], P[n - 1]); 
  
    circle d = welzl_helper(P, R, n - 1); 
  
    if (contains(d, p)) 
    { 
        return d; 
    } 
  
    R.push_back(p); 
  
    return welzl_helper(P, R, n - 1); 
} 
  
circle welzl(vector<point> const& P) 
{ 
    vector<point> P_copy = P; 
    random_shuffle(P_copy.begin(), P_copy.end()); 
    return welzl_helper(P_copy, {}, P_copy.size()); 
} 
  
// https://onlinejudge.org/external/100/10005.pdf
// https://www.geeksforgeeks.org/minimum-enclosing-circle-set-2-welzls-algorithm/
int main() 
{ 
    for (;;)
    {
        vector<point> ps;
        double R;
        size_t n;

        cin >> n;

        if (0 == n)
        {
            break;
        }

        ps.reserve(n);
        ps.clear();

        for (size_t i = 0; i < n; ++i)
        {
            point p;
            cin >> p.X >> p.Y;
            ps.push_back(p);
        }

        cin >> R;

        circle minCircle = welzl(ps);

        if (minCircle.R <= R)
        {
            std::cout << "The polygon can be packed in the circle.\n";
        }
        else
        {
            std::cout << "There is no way of packing that polygon.\n";
        }
    }
  
    return 0; 
}