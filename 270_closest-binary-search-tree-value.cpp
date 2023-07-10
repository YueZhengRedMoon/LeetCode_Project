#include <iostream>
#include "leetcode.h"

class Solution
{
public:
    int closestValue(TreeNode* root, double target)
    {
        if (root->val > target)
        {
            if (root->left)
                return closestValue(root->left, target);
            else if (root->right)
                return closestValue(root->right, target);
            else
                return target;
        }
        else if (root->val < target)
        {
            if (root->right)
                return closestValue(root->right, target);

        }
        else
        {
            return root->val;
        }
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
