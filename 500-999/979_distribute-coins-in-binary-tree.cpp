#include <iostream>
#include "../leetcode.h"

class Solution
{
public:
    int distributeCoins(TreeNode* root)
    {
        ans = 0;
        postorderTraversal(root);
        return ans;
    }

private:
    int ans;

    int postorderTraversal(TreeNode *node)
    {
        if (node == nullptr)
            return 0;

        int left = postorderTraversal(node->left);
        int right = postorderTraversal(node->right);
        int cur = 1 - node->val;

        int sum = left + cur + right;
        ans += std::abs(sum);
        return sum;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}