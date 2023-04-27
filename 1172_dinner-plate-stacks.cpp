#include <iostream>
#include <stack>
#include <vector>

/** 超时 */
class DinnerPlates
{
public:
    DinnerPlates(int cap) : capacity(cap), firstEmptyStackIndex(0), lastNotEmptyStackIndex(-1)
    {
        stacks.reserve(100001);
        stacks.emplace_back(std::stack<int>());
    }

    void push(int val)
    {
        while (firstEmptyStackIndex < stacks.size() && stacks[firstEmptyStackIndex].size() == capacity)
        {
            ++firstEmptyStackIndex;
        }

        // 所有栈都满了，需要开辟一个新的栈
        if (firstEmptyStackIndex == stacks.size())
        {
            stacks.emplace_back(std::stack<int>());
        }

        stacks[firstEmptyStackIndex].push(val);
        if (firstEmptyStackIndex > lastNotEmptyStackIndex)
        {
            lastNotEmptyStackIndex = firstEmptyStackIndex;
        }
    }

    int pop()
    {
        while (lastNotEmptyStackIndex >= 0 && stacks[lastNotEmptyStackIndex].empty())
        {
            --lastNotEmptyStackIndex;
        }
        if (lastNotEmptyStackIndex < 0)
        {
            return -1;
        }

        int val = stacks[lastNotEmptyStackIndex].top();
        stacks[lastNotEmptyStackIndex].pop();
        if (stacks[lastNotEmptyStackIndex].empty() && lastNotEmptyStackIndex < firstEmptyStackIndex)
        {
            firstEmptyStackIndex = lastNotEmptyStackIndex;
        }
        return val;
    }

    int popAtStack(int index)
    {
        if (index >= stacks.size() || stacks[index].empty())
        {
            return -1;
        }

        int val = stacks[index].top();
        stacks[index].pop();
        if (index < firstEmptyStackIndex)
        {
            firstEmptyStackIndex = index;
        }

        return val;
    }

private:
    std::vector<std::stack<int>> stacks;
    int capacity;
    int firstEmptyStackIndex;
    int lastNotEmptyStackIndex;
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}