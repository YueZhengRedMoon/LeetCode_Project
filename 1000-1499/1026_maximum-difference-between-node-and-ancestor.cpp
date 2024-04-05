#include <iostream>
#include <algorithm>
#include "../leetcode.h"

class Solution
{
public:
    int maxAncestorDiff(TreeNode* root)
    {
        ans = 0;
        preorderTraversal(root, root->val, root->val);
        return ans;
    }

private:
    int ans;

    void preorderTraversal(TreeNode* node, int maxAncestor, int minAncestor)
    {
        ans = std::max({ans, std::abs(node->val - maxAncestor), std::abs(node->val - minAncestor)});
        if (node->val > maxAncestor)
            maxAncestor = node->val;
        if (node->val < minAncestor)
            minAncestor = node->val;
        if (node->left)
            preorderTraversal(node->left, maxAncestor, minAncestor);
        if (node->right)
            preorderTraversal(node->right, maxAncestor, minAncestor);
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
