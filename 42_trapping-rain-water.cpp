#include <iostream>
#include <vector>
#include <stack>

class Solution
{
public:
    int trap(std::vector<int> &height)
    {
        std::vector<int> nextHigher(height.size(), -1);
        std::vector<int> lastHigher(height.size(), -1);
        std::stack<int> stack;

        for (int i = 0; i < height.size(); ++i)
        {
            while (!stack.empty() && height[stack.top()] < height[i])
            {
                nextHigher[stack.top()] = i;
                stack.pop();
            }
            stack.push(i);
        }

        std::stack<int> empty;
        std::swap(stack, empty);
        for (int i = height.size() - 1; i >= 0; --i)
        {
            while (!stack.empty() && height[stack.top()] < height[i])
            {
                lastHigher[stack.top()] = i;
                stack.pop();
            }
            stack.push(i);
        }

        int result = 0;
        for (int i = 0; i < height.size(); ++i)
        {
            if (nextHigher[i] != - 1 && lastHigher[i] != -1)
            {
                int next = nextHigher[i];
                while (nextHigher[next] != -1)
                {
                    int temp = next;
                    next = nextHigher[next];
                    nextHigher[temp] = next;
                }
                int last = lastHigher[i];
                while (lastHigher[last] != -1)
                {
                    int temp = last;
                    last = lastHigher[last];
                    nextHigher[temp] = last;
                }
                result += std::min(height[next], height[last]) - height[i];
            }
        }

        return result;
    }
};

class Solution2
{
public:
    int trap(std::vector<int> &height)
    {
        int size = height.size();
       std::vector<int> maxLeft(size, 0);
       std::vector<int> maxRight(size, 0);

       // 记录每个柱子左边柱子最大高度
       maxLeft[0] = height[0];
       for (int i = 1; i < size; ++i)
       {
           maxLeft[i] = std::max(maxLeft[i - 1], height[i]);
       }
       maxRight[size - 1] = height[size - 1];
       for (int i = size - 2; i >= 0; --i)
       {
           maxRight[i] = std::max(maxRight[i + 1], height[i]);
       }

       int result = 0;
       for (int i = 1; i < size - 1; ++i)
       {
           result += std::min(maxLeft[i], maxRight[i]) - height[i];
       }

       return result;
    }
};

class Solution3
{
public:
    int trap(std::vector<int> &height)
    {
        std::stack<int> stack;
        stack.push(0);
        int result = 0;
        for (int i = 1; i < height.size(); ++i)
        {
            while (!stack.empty() && height[stack.top()] < height[i])
            {
                int mid = stack.top();
                stack.pop();
                if (!stack.empty())
                {
                     int h = std::min(height[stack.top()], height[i]) - height[mid];
                     int w = i - stack.top() - 1;
                     result += h * w;
                }
            }
            stack.push(i);
        }
        return result;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}