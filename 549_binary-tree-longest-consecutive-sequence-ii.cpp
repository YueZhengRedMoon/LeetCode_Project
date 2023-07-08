#include <iostream>
#include <algorithm>
#include "leetcode.h"

class Solution
{
public:
    int longestConsecutive(TreeNode* root)
    {
        ans = 0;
        postorderTraversal(root);
        return ans;
    }

private:
    int ans;

    // 返回值first:从上往下递增序列的最长长度，second:从上往下递减序列的最长长度
    std::pair<int, int> postorderTraversal(TreeNode *node)
    {
        int leftIncreaseCount = 0, leftDecreaseCount = 0;
        int rightIncreaseCount = 0, rightDecreaseCount = 0;
        if (node->left)
        {
            std::pair<int, int> leftLen = postorderTraversal(node->left);
            if (node->val + 1 == node->left->val)
            {
                leftIncreaseCount = leftLen.first;
            }
            else if (node->val - 1 == node->left->val)
            {
                leftDecreaseCount = leftLen.second;
            }
        }
        if (node->right)
        {
            std::pair<int, int> rightLen = postorderTraversal(node->right);
            if (node->val + 1 == node->right->val)
            {
                rightIncreaseCount = rightLen.first;
            }
            else if (node->val - 1 == node->right->val)
            {
                rightDecreaseCount = rightLen.second;
            }
        }

        ans = std::max(ans,
                       std::max({leftIncreaseCount, rightIncreaseCount, leftIncreaseCount + rightDecreaseCount,
                                 leftDecreaseCount + rightIncreaseCount}) + 1);

        return std::make_pair(std::max(leftIncreaseCount, rightIncreaseCount) + 1,
                              std::max(leftDecreaseCount, rightDecreaseCount) + 1);
    }
};



int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}