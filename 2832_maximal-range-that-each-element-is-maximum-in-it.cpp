#include <iostream>
#include <vector>
#include <stack>

class Solution
{
public:
    std::vector<int> maximumLengthOfRanges(std::vector<int> &nums)
    {
        int n = nums.size();
        std::vector<int> ans(n);
        std::stack<int> stack;  // 单调递减栈
        for (int i = 0; i < n; ++i)
        {
            while (!stack.empty() && nums[stack.top()] < nums[i])
            {
                int index = stack.top();
                stack.pop();
                if (stack.empty())
                {
                    ans[index] = i;
                }
                else
                {
                    ans[index] = i - stack.top() - 1;
                }
            }
            stack.push(i);
        }
        while (!stack.empty())
        {
            int index = stack.top();
            stack.pop();
            int prev = stack.empty() ? -1 : stack.top();
            ans[index] = n - 1 - prev;
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
