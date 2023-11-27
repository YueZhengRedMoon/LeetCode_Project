#include <iostream>
#include <stack>
#include <vector>
#include "debug.h"

class Solution
{
public:
    int sumSubarrayMins(std::vector<int> &arr)
    {
        int n = arr.size();

        // 考虑数组中的每一个元素，它可以作为哪些子数组中的最小值
        // 对于arr[i]，假设它左边的最后一个<arr[i]的元素的下标为l，它右边的第一个<=arr[i]的元素的下标为r
        // 则arr(l, r)中所有包含arr[i]的子数组的最小值都是arr[i]

        // 单调递增栈，从栈底到栈顶的元素是递增的
        std::vector<int> stack;

        // leftNearestLess[i]:arr[i]左侧距离arr[i]最近的<arr[i]的元素的下标，如果不存在，则为-1
        std::vector<int> leftNearestLess(n, -1);
        for (int i = 0; i < n; ++i)
        {
            while (!stack.empty() && arr[stack.back()] >= arr[i])
                stack.pop_back();
            if (!stack.empty())
            {
                leftNearestLess[i] = stack.back();
            }
            stack.push_back(i);
        }

        stack.clear();
        // rightNearestLessEqual[i]:arr[i]右侧距离arr[i]最近的<=arr[i]的元素的下标，如果不存在，则为n
        std::vector<int> rightNearestLessEqual(n, n);
        for (int i = n - 1; i >= 0; --i)
        {
            while (!stack.empty() && arr[stack.back()] > arr[i])
                stack.pop_back();
            if (!stack.empty())
            {
                rightNearestLessEqual[i] = stack.back();
            }
            stack.push_back(i);
        }

        const long long MOD = 1e9 + 7;
        long long ans = 0;
        for (int i = 0; i < n; ++i)
        {
            ans = (ans + (long long) arr[i] * (i - leftNearestLess[i]) * (rightNearestLessEqual[i] - i)) % MOD;
        }
        return (int) ans;
    }
};

class Solution2
{
public:
    int sumSubarrayMins(std::vector<int> &arr)
    {
        int n = arr.size();
        // leftNearestLess[i]:arr[i]左侧距离arr[i]最近的<arr[i]的元素的下标，如果不存在，则为-1
        std::vector<int> leftNearestLess(n, -1);
        // rightNearestLessEqual[i]:arr[i]右侧距离arr[i]最近的<=arr[i]的元素的下标，如果不存在，则为n
        std::vector<int> rightNearestLessEqual(n, n);

        std::stack<int> stack;
        for (int i = 0; i < n; ++i)
        {
            while (!stack.empty() && arr[stack.top()] >= arr[i])
            {
                rightNearestLessEqual[stack.top()] = i;
                stack.pop();
            }
            if (!stack.empty())
                leftNearestLess[i] = stack.top();
            stack.push(i);
        }

        const long long MOD = 1e9 + 7;
        long long ans = 0;
        for (int i = 0; i < n; ++i)
        {
            ans = (ans + (long long) arr[i] * (i - leftNearestLess[i]) * (rightNearestLessEqual[i] - i)) % MOD;
        }
        return (int) ans;
    }
};

class Solution3
{
public:
    int sumSubarrayMins(std::vector<int> &arr)
    {
        const long long MOD = 1e9 + 7;
        long long ans = 0;
        arr.push_back(-1);
        std::stack<int> stack;
        stack.push(-1);
        for (int r = 0; r < arr.size(); ++r)
        {
            while (stack.size() > 1 && arr[stack.top()] >= arr[r])  // arr的末尾添加了一个-1，所以最终所有元素都会被弹出
            {
                int i = stack.top();
                stack.pop();
                ans = (ans + (long long) arr[i] * (i - stack.top()) * (r - i)) % MOD;
            }
            stack.push(r);
        }
        return (int) ans;
    }
};

int main()
{
    Solution solution;
    std::vector<int> arr = {3, 1, 2, 4};
    int ans = solution.sumSubarrayMins(arr);
    logObj(ans);
    return 0;
}
