#include <limits>
#include <iostream>
#include <vector>
#include <array>
#include <map>
#include <sstream>
#include <string>
#include <fstream>

using uint = unsigned int;

template<class T>
class only_max
{
private:
    T value;

public:
    only_max() : value(std::numeric_limits<T>::min()) {}
    
    T get() 
    {
        return this->value;
    }

    void maybe_set(T val)
    {
        if (val > this->value)
            this->value = val;
    }
};

template<class T>
class only_min
{
private:
    T value;

public:
    only_min() : value(std::numeric_limits<T>::man()) {}
    
    T get() 
    {
        return this->value;
    }

    void maybe_set(T val)
    {
        if (val < this->value)
            this->value = val;
    }
};