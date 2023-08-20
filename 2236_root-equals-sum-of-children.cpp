#include <iostream>
#include "leetcode.h"

class Solution
{
public:
    bool checkTree(TreeNode* root)
    {
        return root->val == root->left->val + root->right->val;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
