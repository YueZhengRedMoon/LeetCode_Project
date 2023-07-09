#include <iostream>
#include <vector>
#include <stack>
#include "leetcode.h"

class Solution
{
public:
    std::vector<int> boundaryOfBinaryTree(TreeNode* root)
    {
        std::vector<int> ans{root->val};

        // 右边界
        std::stack<TreeNode*> rightBoundary;
        TreeNode *node = root->right;
        while (node)
        {
            rightBoundary.push(node);
            if (node->right)
            {
                node = node->right;
            }
            else
            {
                node = node->left;
            }
        }
        bool hasRightBoundary = !rightBoundary.empty();

        std::stack<TreeNode*> stack;
        bool leftBoundaryEnd = (root->left == nullptr);
        stack.push(root);
        while (!stack.empty())
        {
            node = stack.top();
            stack.pop();

            if (node != root)
            {
                if (node->left == nullptr && node->right == nullptr)
                {
                    if (hasRightBoundary && node == rightBoundary.top())
                    {
                        break;
                    }
                    leftBoundaryEnd = true;
                    ans.push_back(node->val);
                }
                if (!leftBoundaryEnd)
                {
                    ans.push_back(node->val);
                }
            }

            if (node->right)
                stack.push(node->right);
            if (node->left)
                stack.push(node->left);
        }

        if (hasRightBoundary)
        {
            while (!rightBoundary.empty())
            {
                node = rightBoundary.top();
                rightBoundary.pop();
                ans.push_back(node->val);
            }
        }

        return ans;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}