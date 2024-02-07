#include <iostream>
#include <vector>
#include "../leetcode.h"

class Solution
{
public:
    TreeNode* replaceValueInTree(TreeNode* root)
    {
        std::vector<TreeNode*> level({root});
        root->val = 0;
        while (!level.empty())
        {
            int levelSum = 0;
            std::vector<TreeNode*> nextLevel;
            for (TreeNode* parent : level)
            {
                if (parent->left)
                {
                    levelSum += parent->left->val;
                    nextLevel.push_back(parent->left);
                }
                if (parent->right)
                {
                    levelSum += parent->right->val;
                    nextLevel.push_back(parent->right);
                }
            }
            for (TreeNode* parent : level)
            {
                int leftVal = parent->left ? parent->left->val : 0;
                int rightVal = parent->right ? parent->right->val : 0;
                int childVal = leftVal + rightVal;
                if (parent->left)
                    parent->left->val = levelSum - childVal;
                if (parent->right)
                    parent->right->val = levelSum - childVal;
            }
            std::swap(level, nextLevel);
        }
        return root;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
