#include <iostream>
#include <vector>
#include <stack>
#include "debug.h"

/** 错误 */
class Solution
{
public:
    int mctFromLeafValues(std::vector<int> &arr)
    {
        int n = arr.size();
        // dp[i]:arr[0:i]构成二叉树的叶子时，非叶子节点的最小和
        std::vector<int> dp(n);
        // maxLeaf[i]:arr[0:i]中的最大值
        std::vector<int> maxLeaf(n);
        dp[0] = 0;
        dp[1] = arr[0] * arr[1];
        maxLeaf[0] = arr[0];
        maxLeaf[1] = std::max(arr[0], arr[1]);

        for (int i = 2; i < n; ++i)
        {
            dp[i] = std::min(dp[i - 1] + maxLeaf[i - 1] * arr[i],
                             dp[i - 2] + arr[i] * arr[i - 1] + maxLeaf[i - 2] * std::max(arr[i], arr[i - 1]));
            maxLeaf[i] = std::max(maxLeaf[i - 1], arr[i]);
        }

        debug::printVector(dp);
        return dp[n - 1];
    }
};

class Solution2
{
public:
    int mctFromLeafValues(std::vector<int> &arr)
    {
        const int inf = 0x3f3f3f3f;
        int n = arr.size();
        // dp[i][j]:arr[i:j]构成二叉树的叶子时，非叶子节点的最小和
        // max[i][j]:arr[i:j]中的最大值
        std::vector<std::vector<int>> dp(n, std::vector<int>(n, inf)), maxLeaf(n, std::vector<int>(n));

        for (int j = 0; j < n; ++j)
        {
            dp[j][j] = 0;
            maxLeaf[j][j] = arr[j];
            for (int i = j - 1; i >= 0; --i)
            {
                maxLeaf[i][j] = std::max(arr[i], maxLeaf[i + 1][j]);
                for (int k = i; k < j; ++k)
                {
                    dp[i][j] = std::min(dp[i][j], dp[i][k] + dp[k + 1][j] + maxLeaf[i][k] * maxLeaf[k + 1][j]);
                }
            }
        }

        return dp[0][n - 1];
    }
};

/** 单调栈做法，时间复杂度O(n) */
class Solution3
{
public:
    int mctFromLeafValues(std::vector<int> &arr)
    {
        /** 对arr[i-1], arr[i], arr[i + 1]来说：
         *  如果arr[i-1] > arr[i] && arr[i] < arr[i+1]
         *  如果arr[i-1] < arr[i+1]，则应该优先合并arr[i-1]与arr[i]
         *  如果arr[i-1] > arr[i+1]，则应该优先合并arr[i]与arr[i+1]
         *  */
        int ans = 0;
        std::stack<int> stack;
        for (int x : arr)
        {
            // arr[i] <= arr[i+1]
            while (!stack.empty() && stack.top() <= x)
            {
                int y = stack.top();    // arr[i]
                stack.pop();
                if (stack.empty() || stack.top() > x)   // arr[i-1] > arr[i+1]
                {
                    ans += y * x;   // 合并arr[i]与arr[i+1]
                }
                else    // arr[i-1] < arr[i + 1]
                {
                    ans += stack.top() * y; // 合并arr[i-1]与arr[i]
                }
                // 合并后arr[i-1]变为新的arr[i]
            }
            stack.push(x);
        }
        // 当剩下的节点都是递减的时候，从右往左依次合并，每次新生成的节点是最小的
        while (stack.size() >= 2)
        {
            int x = stack.top();
            stack.pop();
            ans += stack.top() * x;
        }
        return ans;
    }
};

int main()
{
    Solution2 solution;
    std::vector<int> arr = {15,13,5,3,15};
    int ans = solution.mctFromLeafValues(arr);
    std::cout << ans << std::endl;
    return 0;
}