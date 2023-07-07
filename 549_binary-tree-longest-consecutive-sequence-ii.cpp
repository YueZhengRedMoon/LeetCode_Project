#include <iostream>
#include "leetcode.h"

/** 错误，不能用中序遍历 */
class Solution
{
public:
    int longestConsecutive(TreeNode* root)
    {
        ans = 1;
        postorderTraversal(root, root->val, 1, 1);
        inorderTraversal(root, 0x3f3f3f3f, 1, 1);
        return ans;
    }

private:
    int ans;

    void postorderTraversal(TreeNode *node, int parentVal, int increaseCount, int decreaseCount)
    {
        if (node->val == parentVal + 1)
        {
            if (++increaseCount > ans)
                ans = increaseCount;
            decreaseCount = 1;
        }
        else if (node->val == parentVal - 1)
        {
            if (++decreaseCount > ans)
                ans = decreaseCount;
            increaseCount = 1;
        }
        else
        {
            increaseCount = 1;
            decreaseCount = 1;
        }

        if (node->left) postorderTraversal(node->left, node->val, increaseCount, decreaseCount);
        if (node->right) postorderTraversal(node->right, node->val, increaseCount, decreaseCount);
    }

    int inorderTraversal(TreeNode *node, int prevVal, int increaseCount, int decreaseCount)
    {
        if (node->left)
            prevVal = inorderTraversal(node->left, prevVal, increaseCount, decreaseCount);

        if (node->val == prevVal + 1)
        {
            if (++increaseCount > ans)
                ans = increaseCount;
            decreaseCount = 1;
        }
        else if (node->val == prevVal - 1)
        {
            if (++decreaseCount > ans)
                ans = decreaseCount;
            increaseCount = 1;
        }
        else
        {
            increaseCount = 1;
            decreaseCount = 1;
        }

        prevVal = node->val;

        if (node->right)
            prevVal = inorderTraversal(node->right, prevVal, increaseCount, decreaseCount);

        return prevVal;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}