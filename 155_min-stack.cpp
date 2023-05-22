#include <iostream>
#include <map>
#include <stack>
#include <limits>

/** getMin操作是O(logn)的复杂度 */
class MinStack3
{
public:
    MinStack3()
    {

    }

    void push(int val)
    {
        stack.push(val);
        ++count[val];
    }

    void pop()
    {
        int topVal = stack.top();
        stack.pop();
        auto it = count.find(topVal);
        it->second -= 1;
        if (it->second == 0)
        {
            count.erase(it);
        }
    }

    int top()
    {
        return stack.top();
    }

    int getMin()
    {
        return count.begin()->first;
    }

private:
    std::map<int, int> count;
    std::stack<int> stack;
};

class MinStack2
{
public:
    MinStack2()
    {
        minStack.push(std::numeric_limits<int>::max());
    }

    void push(int val)
    {
        stack.push(val);
        minStack.push(std::min(val, minStack.top()));
    }

    void pop()
    {
        stack.pop();
        minStack.pop();
    }

    int top()
    {
        return stack.top();
    }

    int getMin()
    {
        return minStack.top();
    }

private:
    std::stack<int> stack;
    std::stack<int> minStack;
};

class MinStack
{
public:
    MinStack()
    {

    }

    void push(int val)
    {
        if (stack.empty())
        {
            stack.push(0);
            minVal = val;
        }
        else
        {
            long long delta = val - minVal;
            stack.push(delta);
            if (delta < 0)
            {
                minVal = val;
            }
        }
    }

    void pop()
    {
        long long delta = stack.top();
        stack.pop();
        if (delta < 0)
        {
            minVal -= delta;
        }
    }

    int top()
    {
        long long topVal;
        long long topDelta = stack.top();
        if (topDelta < 0)
        {
            topVal = minVal;
        }
        else
        {
            topVal = topDelta + minVal;
        }
        return static_cast<int>(topVal);
    }

    int getMin()
    {
        return minVal;
    }

private:
    std::stack<long long> stack;
    long long minVal;
};


int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}