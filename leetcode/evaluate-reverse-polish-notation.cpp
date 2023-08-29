#include <charconv>
#include <iostream>
#include <string>
#include <vector>

int parse_better(std::string const& s)
{
    int result;
    std::from_chars(s.data(), s.data() + s.size(), result);
    return result;
}

int parse_naive(std::string const& s)
{
    return std::stoi(s);
}

int solve(std::vector<std::string> tokens)
{
    std::vector<int> stack;
    stack.reserve(tokens.size());
    for (std::string const& str : tokens)
    {
        char const last = str.back();
        if (not (last == '+' || last == '-' || last == '*' || last == '/'))
        {
            stack.push_back(parse_better(str));
            continue;
        }

        int const y = stack.back();
        stack.pop_back();
        int const x = stack.back();
        stack.pop_back();
        switch (last)
        {
        case '+': stack.push_back(x + y); break;
        case '-': stack.push_back(x - y); break;
        case '*': stack.push_back(x * y); break;
        case '/': stack.push_back(x / y); break;
        }

    }
    return stack.back();
}

int main()
{
    std::cout << solve({"2","1","+","3","*"}) << "\n";
    std::cout << solve({"4","13","5","/","+"}) << "\n";
    std::cout << solve({"10","6","9","3","+","-11","*","/","*","17","+","5","+"}) << "\n";
}