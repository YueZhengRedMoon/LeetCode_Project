#include <iostream>
#include "leetcode.h"

class Solution
{
public:
    int countUnivalSubtrees(TreeNode* root)
    {
        ans = 0;
        postorderTraversal(root);
        return ans;
    }

private:
    int ans;

    bool postorderTraversal(TreeNode *node)
    {
        if (node == nullptr)
            return true;

        bool leftIsUniVal = postorderTraversal(node->left);
        bool rightIsUniVal = postorderTraversal(node->right);

        bool isUniVal = leftIsUniVal && rightIsUniVal
                        && (node->left == nullptr || node->left->val == node->val)
                        && (node->right == nullptr || node->right->val == node->val);
        if (isUniVal)
            ++ans;
        return isUniVal;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
