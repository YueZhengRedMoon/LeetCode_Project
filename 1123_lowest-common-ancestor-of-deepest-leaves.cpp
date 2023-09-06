#include <iostream>
#include "leetcode.h"

class Solution
{
public:
    TreeNode* lcaDeepestLeaves(TreeNode* root)
    {
        leafMaxDepth = 0;
        ans = root;
        postorderTraversal(root, 0);
        return ans;
    }

private:
    int leafMaxDepth;
    TreeNode *ans;

    int postorderTraversal(TreeNode *node, int curDepth)
    {
        if (node == nullptr)
            return curDepth;

        ++curDepth;
        int leftMaxDepth = postorderTraversal(node->left, curDepth);
        int rightMaxDepth = postorderTraversal(node->right, curDepth);

        if (leftMaxDepth == rightMaxDepth && rightMaxDepth >= leafMaxDepth)
        {
            ans = node;
            leafMaxDepth = rightMaxDepth;
        }

        return std::max(leftMaxDepth, rightMaxDepth);
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
