#include <iostream>
#include <limits>
#include "leetcode.h"

class Solution
{
public:
    TreeNode* sufficientSubset(TreeNode* root, int limit)
    {
        limit_ = limit;
        int maxGoVal = postorderTraversal(root, 0);
        if (maxGoVal < limit_)
        {
            root = nullptr;
        }
        return root;
    }

private:
    int limit_;

    int postorderTraversal(TreeNode *node, int comeVal)
    {
        if (node == nullptr)
        {
            return -0x3f3f3f3f;
        }
        if (node->left == nullptr && node->right == nullptr)
        {
            return node->val;
        }

        comeVal += node->val;
        int leftMaxGoVal = postorderTraversal(node->left, comeVal);
        if (leftMaxGoVal + comeVal < limit_)
        {
            node->left = nullptr;
        }
        int rightMaxGoVal = postorderTraversal(node->right, comeVal);
        if (rightMaxGoVal + comeVal < limit_)
        {
            node->right = nullptr;
        }
        int maxGoVal = node->val + std::max(leftMaxGoVal, rightMaxGoVal);
        return maxGoVal;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}