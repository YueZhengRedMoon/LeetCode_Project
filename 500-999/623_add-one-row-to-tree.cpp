#include <iostream>
#include <stack>
#include "../leetcode.h"

class Solution
{
public:
    TreeNode* addOneRow(TreeNode* root, int val, int depth)
    {
        if (depth == 1)
        {
            TreeNode *newRoot = new TreeNode(val, root, nullptr);
            return newRoot;
        }
        std::stack<std::pair<TreeNode*, int>> stack;
        stack.emplace(root, 1);
        while (!stack.empty())
        {
            auto [cur, curDepth] = stack.top();
            stack.pop();

            if (curDepth == depth - 1)
            {
                TreeNode *newLeft = new TreeNode(val, cur->left, nullptr);
                TreeNode *newRight = new TreeNode(val, nullptr, cur->right);
                cur->left = newLeft;
                cur->right = newRight;
            }
            else
            {
                if (cur->left)
                    stack.emplace(cur->left, curDepth + 1);
                if (cur->right)
                    stack.emplace(cur->right, curDepth + 1);
            }
        }
        return root;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}