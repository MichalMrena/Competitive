#include <iostream>
#include <string>
#include <vector>

/**
 *  This solution is bit of an overkill but still better than using hash-map
 *  (Dictionary, HashMap, std::unordered_map) for finding closing bracket.
 *  For such a small number of elements, just use linear search over vector
 *  or a hard-coded solution like I did.
 */
bool solve(std::string s)
{
    if (s.size() % 2 != 0)
    {
        return false;
    }

    std::vector<char> stack;
    stack.resize(s.size());
    char* sp = stack.data();
    for (char const c : s)
    {
        if (c == '(' || c == '[' || c == '{')
        {
            *sp++ = c;
            continue;
        }

        int const notEmpty = stack.data() != sp;
        if (not notEmpty)
        {
            return false;
        }

        switch (c)
        {
            case ')': if (*(sp - 1) != '(') return false; else sp -= notEmpty; break;
            case ']': if (*(sp - 1) != '[') return false; else sp -= notEmpty; break;
            case '}': if (*(sp - 1) != '{') return false; else sp -= notEmpty; break;
        }
    }
    return stack.data() == sp;
}

int main()
{
    std::cout << solve("()") << "\n";
    std::cout << solve("()[]{}") << "\n";
    std::cout << solve("(]") << "\n";
    std::cout << solve("(") << "\n";
    std::cout << solve("]") << "\n";
}