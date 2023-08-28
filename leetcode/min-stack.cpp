#include <vector>

class MinStack
{
public:
    MinStack()
    {
        stack_.reserve(3 * 10'000);
        minStack_.reserve(3 * 10'000);
    }

    void push(int val)
    {
        if (minStack_.empty())
        {
            stack_.push_back(val);
            minStack_.push_back(val);
            return;
        }

        stack_.push_back(val);
        if (val <= minStack_.back())
        {
            minStack_.push_back(val);
        }
    }

    void pop()
    {
        int const val = stack_.back();
        stack_.pop_back();
        if (val == minStack_.back())
        {
            minStack_.pop_back();
        }
    }

    int top()
    {
        return stack_.back();
    }

    int getMin()
    {
        return minStack_.back();
    }

private:
    std::vector<int> stack_;
    std::vector<int> minStack_;
};

int main()
{
    MinStack s;
    s.push(0);
    s.push(1);
    s.push(0);
    s.getMin();
    s.pop();
    s.getMin();
}