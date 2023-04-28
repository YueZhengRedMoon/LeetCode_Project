#include <iostream>
#include <stack>
#include <vector>
#include <set>

/** 超时 */
class MyDinnerPlates
{
public:
    MyDinnerPlates(int cap) : capacity(cap), firstEmptyStackIndex(0), lastNotEmptyStackIndex(-1)
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

class DinnerPlates
{
public:
    DinnerPlates(int c) : capacity(c)
    {
        stack.reserve(100001);
        top.reserve(100001);
    }

    void push(int val)
    {
        if (poppedPos.empty())
        {
            int pos = stack.size();
            stack.emplace_back(val);
            if (pos % capacity == 0)
            {
                top.emplace_back(0);
            }
            else
            {
                ++top.back();
            }
        }
        else
        {
            int pos = *poppedPos.begin();
            poppedPos.erase(pos);
            stack[pos] = val;
            int index = pos / capacity;
            ++top[index];
        }
    }

    int pop()
    {
        while (!stack.empty() && poppedPos.find(stack.size() - 1) != poppedPos.end())
        {
            stack.pop_back();
            int pos = *poppedPos.rbegin();
            poppedPos.erase(pos);
            if (pos % capacity == 0)
            {
                top.pop_back();
            }
        }

        if (stack.empty())
        {
            return - 1;
        }
        else
        {
            int pos = stack.size() - 1;
            int val = stack.back();
            stack.pop_back();
            if (pos % capacity == 0)
            {
                top.pop_back();
            }
            else
            {
                --top.back();
            }
            return val;
        }
    }

    int popAtStack(int index)
    {
        if (index >= top.size())
        {
            return -1;
        }
        int stackTop = top[index];
        if (stackTop < 0)
        {
            return -1;
        }
        --top[index];
        int pos = index * capacity + stackTop;
        poppedPos.emplace(pos);
        return stack[pos];
    }

private:
    int capacity;
    std::vector<int> stack;
    std::vector<int> top;
    std::set<int> poppedPos;
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}