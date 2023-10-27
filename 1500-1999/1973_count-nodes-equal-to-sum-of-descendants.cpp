#include <iostream>
#include "../leetcode.h"

class Solution
{
public:
    int equalToDescendants(TreeNode *root)
    {
        ans = 0;
        postorderTraversal(root);
        return ans;
    }

private:
    int ans;

    long long postorderTraversal(TreeNode *node)
    {
        if (node == nullptr)
            return 0;

        long long leftSubTreeSum = postorderTraversal(node->left);
        long long rightSubTreeSum = postorderTraversal(node->right);
        if (leftSubTreeSum + rightSubTreeSum == node->val)
            ++ans;
        return node->val + leftSubTreeSum + rightSubTreeSum;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
