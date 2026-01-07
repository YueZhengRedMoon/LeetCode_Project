#include <iostream>
#include <stack>
#include "..\leetcode.h"

class Solution
{
public:
    int maxProduct(TreeNode* root)
    {
        total = preorderTraverse(root);
        ans = 0;
        postorderTraverse(root);
        return (int) (ans % MOD);
    }

private:
    static constexpr int MOD = 1'000'000'007;
    int total;
    long long ans;

    // 前序遍历树，获得树的元素和
    int preorderTraverse(TreeNode* node)
    {
        int sum = node->val;
        if (node->left)
            sum += preorderTraverse(node->left);
        if (node->right)
            sum += preorderTraverse(node->right);
        return sum;
    }

    // 后序遍历二叉树，计算子树的元素和
    int postorderTraverse(TreeNode* node)
    {
        int sum = node->val, leftSum = 0, rightSum = 0;
        if (node->left)
        {
            leftSum = postorderTraverse(node->left);
            ans = std::max(ans, (long long) leftSum * (total - leftSum));
        }
        if (node->right)
        {
            rightSum = postorderTraverse(node->right);
            ans = std::max(ans, (long long) rightSum * (total - rightSum));
        }
        return sum + leftSum + rightSum;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}