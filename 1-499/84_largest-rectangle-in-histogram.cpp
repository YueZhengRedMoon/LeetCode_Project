#include <iostream>
#include <stack>
#include <vector>
#include "../debug.h"

class Solution
{
public:
    int largestRectangleArea(std::vector<int> &heights)
    {
        int size = heights.size();
        std::vector<int> minLeftIndex(size);
        std::vector<int> minRightIndex(size);

        // 记录每个柱子左边第一个高度小于自身的柱子的下标
        minLeftIndex[0] = -1;
        for (int i = 1; i < size; ++i)
        {
            int j = i - 1;
            while (j >= 0 && heights[j] >= heights[i])
                j = minLeftIndex[j];
            minLeftIndex[i] = j;
        }

        // 记录每个柱子右边第一个高度小于自身的柱子的下标
        minRightIndex[size - 1] = size;
        for (int i = size - 2; i >= 0; --i)
        {
            int j = i + 1;
            while (j < size && heights[j] >= heights[i])
                j = minRightIndex[j];
            minRightIndex[i] = j;
        }

        debug::printVector(minLeftIndex);
        debug::printVector(minRightIndex);

        int maxArea = 0;
        for (int i = 0; i < size; ++i)
        {
            std::cout << "area[" << i << "]=" <<  heights[i] * (minRightIndex[i] - minLeftIndex[i] -1) << std::endl;
            maxArea = std::max(maxArea, heights[i] * (minRightIndex[i] - minLeftIndex[i] -1));
        }

        return maxArea;
    }
};

class Solution2
{
public:
    int largestRectangleArea(std::vector<int> &heights)
    {
        if (heights.back() > 0)
        {
            heights.push_back(0);
        }

        std::stack<int> stack;
        int maxArea = 0;
        for (int i = 0; i < heights.size(); ++i)
        {
            if (stack.empty() || heights[stack.top()] <= heights[i])
            {
                stack.push(i);
            }
            else if (heights[stack.top()] == heights[i])
            {
                stack.pop();
                stack.push(i);
            }
            else
            {
                while (!stack.empty() && heights[stack.top()] > heights[i])
                {
                    int mid = stack.top();
                    stack.pop();
                    int left = -1;
                    if (!stack.empty())
                    {
                        left = stack.top();
                    }
                    maxArea = std::max(maxArea, (i - left - 1) * heights[mid]);
                }
                stack.push(i);
            }
        }

        return maxArea;
    }
};

int main()
{
    std::vector<int> heights = {2,1,5,6,2,3};
    Solution solution;
    int maxArea = solution.largestRectangleArea(heights);
    std::cout << maxArea << std::endl;
    return 0;
}