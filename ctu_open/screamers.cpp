#include <sstream>
#include <cmath>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <string>

using namespace std;

int T, N, M;

struct soil
{
    bool has_grass {false};
    bool is_dead {false};
    int turns {0};

    char to_char()
    {
        return has_grass 
                ? '#' 
                : (is_dead) ? '*' : '.';
    }
};
struct animal;

soil soil_grid[20][20];
animal* animal_grid[20][20] {};

struct animal
{
    int row;
    int col;
    bool is_sheep;
    int turns_since {0};

    animal(int pRow, int pCol, bool pIsSheep) : row {pRow}, col {pCol}, is_sheep {pIsSheep} {};

    char to_char()
    {
        return is_sheep ? 'S' : 'W';
    }

    virtual void move() = 0;
    virtual bool should_die() = 0;
};

struct wolf : public animal
{
    wolf(int pRow, int pCol) : animal {pRow, pCol, false} {};

    virtual void move()
    {
        ++col;
        if (col >= N)
        {
            col = 0;
        }
    }

    virtual bool should_die()
    {
        return turns_since >= 10;
    }
};

struct sheep : public animal
{
    sheep(int pRow, int pCol) : animal {pRow, pCol, true} {};

    virtual void move()
    {
        ++row;
        if (row >= M)
        {
            row = 0;
        }
    }
    
    virtual bool should_die()
    {
        return turns_since >= 5;
    }
};

void print_state()
{
    for (int row {0}; row < M; ++ row)
    {
        for (int col {0}; col < N; ++col)
        {
            if (animal_grid[row][col]) cout << animal_grid[row][col]->to_char();
            else cout << soil_grid[row][col].to_char();
        }
        cout << '\n';
    }
}

void move_animals()
{
    vector<animal*> tmp_animals;
    for (int row {0}; row < M; ++ row)
    {
        for (int col {0}; col < N; ++col)
        {
            if (animal_grid[row][col])
            {
                tmp_animals.push_back(animal_grid[row][col]);
                animal_grid[row][col]->move();
                animal_grid[row][col] = nullptr;
            }
        }
    }

    for (animal * a : tmp_animals)    
    {
        if (animal_grid[a->row][a->col])
        {
            wolf* w {(wolf*)(a->is_sheep ? animal_grid[a->row][a->col] : a)};
            sheep* s {(sheep*)(a->is_sheep ? a : animal_grid[a->row][a->col])};

            animal_grid[a->row][a->col] = w;
            soil_grid[a->row][a->col].is_dead = true;
            soil_grid[a->row][a->col].has_grass = false;
            w->turns_since = 0;

            delete s;
        }
        else
        {
            if (! a->is_sheep)
            {
                ++a->turns_since;
            }

            animal_grid[a->row][a->col] = a;
        }
    }
}

void simulate_grass()
{
    for (int row {0}; row < M; ++ row)
    {
        for (int col {0}; col < N; ++col)
        {
            if (soil_grid[row][col].is_dead)
            {
                if (animal_grid[row][col] && animal_grid[row][col]->is_sheep)
                {
                    ++animal_grid[row][col]->turns_since;    
                }
                continue;
            }

            if (animal_grid[row][col] && animal_grid[row][col]->is_sheep && soil_grid[row][col].has_grass)
            {
                animal_grid[row][col]->turns_since = 0;
                soil_grid[row][col].has_grass = false;
                soil_grid[row][col].turns = 0;
            }
            else if (animal_grid[row][col] && animal_grid[row][col]->is_sheep)
            {
                ++animal_grid[row][col]->turns_since;

                ++soil_grid[row][col].turns;
                if (soil_grid[row][col].turns >= 3)
                {
                    soil_grid[row][col].has_grass = true;
                }
            }
            else
            {
                ++soil_grid[row][col].turns;
                if (soil_grid[row][col].turns >= 3)
                {
                    soil_grid[row][col].has_grass = true;
                }
            }
        }
    }
}

void starve_animals()
{
    for (int row {0}; row < M; ++ row)
    {
        for (int col {0}; col < N; ++col)
        {
            if (animal_grid[row][col])
            {
                if (animal_grid[row][col]->should_die())
                {
                    delete animal_grid[row][col];
                    animal_grid[row][col] = nullptr;
                    soil_grid[row][col].is_dead = true;
                    soil_grid[row][col].has_grass = false;
                }
            }
        }
    }
}

int main_screamers()
{
    string line;
    getline(cin, line);
    istringstream lineStr {line};
    lineStr >> T >> M >> N;

    for (int row {0}; row < M; ++ row)
    {
        getline(cin, line);
        for (int col {0}; col < N; ++col)
        {
            if ('.' == line[col]) continue;
            if ('W' == line[col]) animal_grid[row][col] = new wolf {row, col};
            if ('S' == line[col]) animal_grid[row][col] = new sheep {row, col};
        }
    }

    for (int turn {0}; turn < T; ++turn)
    {
        move_animals();
        simulate_grass();
        starve_animals();
    }
    print_state();


	return 0;
}