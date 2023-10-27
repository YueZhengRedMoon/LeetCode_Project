#include <iostream>
#include <vector>
#include <stack>

class Solution
{
public:
    int totalSteps(std::vector<int> &nums)
    {
        int ans = 0;
        // first:左边最近的更大的数，second:它被删除的时刻
        std::stack<std::pair<int, int>> stack;  // 递减栈
        for (int num : nums)
        {
            int maxT = 0;
            while (!stack.empty() && stack.top().first <= num)
            {
                maxT = std::max(maxT, stack.top().second);  // 统计最大的被删除时刻
                stack.pop();
            }
            // 如果栈为空，则表示num左边没有比它更大的数，它不会被删除，因此删除时刻为0
            maxT = stack.empty() ? 0 : maxT + 1;
            ans = std::max(ans, maxT);
            stack.emplace(num, maxT);
        }
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
