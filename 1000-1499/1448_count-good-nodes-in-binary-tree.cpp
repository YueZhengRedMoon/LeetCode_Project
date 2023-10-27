#include <iostream>
#include "../leetcode.h"

class Solution
{
public:
    int goodNodes(TreeNode* root)
    {
        ans = 0;
        preorderTraversal(root, root->val);
        return ans;
    }

private:
    int ans;

    void preorderTraversal(TreeNode *node, int maxVal)
    {
        if (node == nullptr)
            return;

        if (maxVal <= node->val)
        {
            ++ans;
            maxVal = node->val;
        }

        preorderTraversal(node->left, maxVal);
        preorderTraversal(node->right, maxVal);
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
