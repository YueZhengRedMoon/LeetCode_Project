#include <iostream>
#include <vector>
#include <set>
#include <stack>
#include <limits>

/** 枚举3 */
class Solution3
{
public:
    bool find132pattern(std::vector<int> &nums)
    {
        int n = nums.size();
        if (n < 3) return false;

        // 左侧最小值
        int leftMin = nums[0];

        // 维护右侧元素的有序集合
        std::multiset<int> rightAll;
        for (int i = 2; i < n; ++i)
            rightAll.insert(nums[i]);

        for (int i = 1; i < n - 1; ++i)
        {
            // 找到nums[i]右边第一个比leftMin大的数
            auto it = rightAll.upper_bound(leftMin);
            if (it != rightAll.end() && *it < nums[i])
            {
                return true;
            }

            if (nums[i] < leftMin) leftMin = nums[i];
            rightAll.erase(rightAll.find(nums[i + 1]));
        }

        return false;
    }
};

/** 枚举2 */
class Solution2
{
public:
    bool find132pattern(std::vector<int> &nums)
    {
        int n = nums.size();
        if (n < 3) return false;

        // leftMin[i]:nums[0:i-1]中最小的数
        std::vector<int> leftMin(n + 1, std::numeric_limits<int>::max());
        // 单调递增的单调栈，栈中的元素是潜在的3的位置
        std::stack<int> stack;

        for (int i = 1; i <= n; ++i)
        {
            while (!stack.empty() && nums[stack.top()] <= nums[i - 1])
            {
                stack.pop();
            }
            if (!stack.empty() && leftMin[stack.top()] < nums[i - 1])
            {
                return true;
            }
            stack.push(i - 1);
            leftMin[i] = std::min(leftMin[i - 1], nums[i - 1]);
        }

        return false;
    }
};

/** 枚举1 */
class Solution
{
public:
    bool find132pattern(std::vector<int> &nums)
    {
        int n = nums.size();
        if (n < 3) return false;

        // 维护一个单调递增的单调栈
        std::stack<int> stack;
        int max = std::numeric_limits<int>::min();  // 被弹出单调栈的最大元素，对应2的位置的元素
        stack.push(nums[n - 1]);

        for (int i = n - 2; i >= 0; --i)
        {
            if (nums[i] < max)
            {
                return true;
            }
            while (!stack.empty() && nums[i] > stack.top())
            {
                max = stack.top();
                stack.pop();
            }
            if (nums[i] > max)
            {
                stack.push(nums[i]);
            }
        }

        return false;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
