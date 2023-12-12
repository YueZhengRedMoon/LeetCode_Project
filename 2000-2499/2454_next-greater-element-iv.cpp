#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include "../debug/debug.h"


class Solution
{
public:
    std::vector<int> secondGreaterElement(std::vector<int> &nums)
    {
        int n = nums.size();
        std::vector<int> ans(n, -1);
        std::stack<int> stack;
        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> queue;
        for (int i = 0; i < n; ++i)
        {
            while (!queue.empty() && nums[i] > queue.top().first)
            {
                ans[queue.top().second] = nums[i];
                queue.pop();
            }

            while (!stack.empty() && nums[i] > nums[stack.top()])
            {
                queue.emplace(nums[stack.top()], stack.top());
                stack.pop();
            }

            stack.push(i);
        }
        return ans;
    }
};

int main()
{
    Solution solution;
    std::vector<int> nums = {11,13,15,12,0,15,12,11,9};
    std::vector<int> ans = solution.secondGreaterElement(nums);
    debug::printVector(ans);
    return 0;
}
