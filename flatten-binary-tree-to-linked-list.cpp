#include <iostream>
#include "leetcode.h"

class Solution
{
public:
    void flatten(TreeNode* root)
    {
        TreeNode *cur = root;
        while (cur)
        {
            if (cur->left)
            {
                // 找到左子树的最右节点
                TreeNode *prev = cur->left;
                while (prev->right)
                {
                    prev = prev->right;
                }
                prev->right = cur->right;
                cur->right = cur->left;
                cur->left = nullptr;
            }
            cur = cur->right;
        }
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}