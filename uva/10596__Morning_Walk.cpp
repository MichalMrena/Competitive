#include <iostream> 
#include <vector> 
#include <algorithm>
#include <sstream>
#include <string>

using namespace std; 

string line;

void read_pair(size_t& c1, size_t& c2)
{
    istringstream istr {line};
    istr >> c1 >> c2;
}

void dfs(vector<vector<size_t>>& arcs, vector<bool>& visited, size_t i)
{
    if (visited[i])
    {
        return;
    }

    visited[i] = true;

    for (size_t target : arcs[i])
    {
        dfs(arcs, visited, target);
    }
}

// https://onlinejudge.org/external/105/10596.pdf
int main() 
{ 
    size_t N, R;

    while (getline(cin, line))
    {
        if (line.empty())
        {
            break;
        }

        read_pair(N, R);

        vector<bool>           visited (N, false);
        vector<vector<size_t>> arcs    (N);

        for (size_t i = 0; i < R; ++i)
        {
            size_t c1, c2;
            getline(cin, line);
            read_pair(c1, c2);
            arcs[c1].push_back(c2);
            arcs[c2].push_back(c1);
        }

        size_t firstConnected = 0;
        for (size_t i = 0; i < N; ++i)
        {
            if (arcs.at(i).empty())
            {
                ++firstConnected;
            }
            else
            {
                break;
            }
        }

        if (firstConnected < N)
        {
            dfs(arcs, visited, firstConnected);
        }

        bool someIsUnreachable = 0 == R;
        bool someIsOdd = false;
        for (size_t i = 0; i < N; ++i)
        {
            if (arcs.at(i).size() > 0 && !visited.at(i))
            {
                someIsUnreachable = true;
                break;
            }

            if (arcs.at(i).size() & 1)
            {
                someIsUnreachable = true;
                break;
            }
        }

        if (someIsUnreachable || someIsOdd)
        {
            cout << "Not Possible" << endl;
        }
        else
        {
            cout << "Possible" << endl;
        }
    }

    return 0; 
}