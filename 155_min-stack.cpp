#include <iostream>
#include <map>
#include <stack>

/** getMin操作是O(logn)的复杂度 */
class MinStack
{
public:
    MinStack()
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

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}