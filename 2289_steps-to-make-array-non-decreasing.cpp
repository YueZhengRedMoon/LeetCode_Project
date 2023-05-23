#include <iostream>
#include <vector>
#include <stack>

class Solution
{
public:
    int totalSteps(std::vector<int> &nums)
    {
        int n = nums.size();
        int ans = 0;
        int max = 0;
        std::stack<int> stack;
        for (int i = 0; i < n; ++i)
        {
            if (nums[i] > max)
            {
                int numLessThanMax = stack.size();
                max = nums[i];
                ans = std::max(ans, numLessThanMax);
                std::stack<int> empty;
                stack.swap(empty);
            }
            else
            {
                while (!stack.empty() && nums[stack.top()] > nums[i])
                {
                    ans = std::max(ans, i - stack.top());
                    stack.pop();
                }
                stack.push(i);
            }
        }
        int numLessThanMax = stack.size();
        ans = std::max(ans, numLessThanMax);

        return ans;
    }
};

int main()
{
    Solution solution;
    std::vector<int> nums = {10,1,2,3,4,5,6,1,2,3};
    int ans = solution.totalSteps(nums);
    std::cout << ans << std::endl;

    std::vector<int> nums2 = {10, 6, 5, 10, 15};
    int ans2 = solution.totalSteps(nums2);
    std::cout << ans2 << std::endl;
    return 0;
}
