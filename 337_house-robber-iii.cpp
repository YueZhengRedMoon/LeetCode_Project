#include <iostream>
#include <unordered_map>
#include <stack>
#include "leetcode.h"

class Solution
{
public:
    int rob(TreeNode* root)
    {
        std::stack<TreeNode*> stack;
        TreeNode* current = root;
        TreeNode* last = nullptr;

        // dp[root].first:偷窃以root为根的房子可以偷到的最大金额
        // dp[root].second:不偷窃以root为根的房子可以偷到的最大金额
        std::unordered_map<TreeNode*, std::pair<int, int>> dp;

        while (current || !stack.empty())
        {
            while (current)
            {
                stack.push(current);
                current = current->left;
            }
            current = stack.top();
            // 右子树处理完
            if (current->right == nullptr || current->right == last)
            {
                stack.pop();

                // 偷窃current可以偷到的金额
                int robCurrent = current->val;
                if (current->left)
                    robCurrent += dp[current->left].second;
                if (current->right)
                    robCurrent += dp[current->right].second;
                dp[current].first = robCurrent;

                // 不偷窃current可以偷到的金额
                int notRobCurrent = 0;
                if (current->left)
                    notRobCurrent += std::max(dp[current->left].first, dp[current->left].second);
                if (current->right)
                    notRobCurrent += std::max(dp[current->right].first, dp[current->right].second);
                dp[current].second = notRobCurrent;

                last = current;
                current = nullptr;
            }
            // 右子树没有处理完
            else
            {
                current = current->right;
            }
        }

        return std::max(dp[root].first, dp[root].second);
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}