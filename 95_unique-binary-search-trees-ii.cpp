#include <iostream>
#include <vector>
#include "leetcode.h"

class Solution
{
public:
    std::vector<TreeNode*> generateTrees(int n)
    {
        // dp[i]:i个节点组成的所有二叉搜索树
        std::vector<std::vector<TreeNode*>> dp(n + 1);
        dp[0].push_back(nullptr);

        for (int i = 1; i <= n; ++i)
        {
            // 遍历左子树的节点数
            for (int left = 0; left < i; ++left)
            {
                // 对应的右子树的节点数
                int right = i - 1 - left;

                // 组合左子树与右子树
                for (const auto& leftTree : dp[left])
                {
                    for (const auto& rightTree : dp[right])
                    {
                        TreeNode *root = new TreeNode();
                        root->left = copyTree(leftTree);
                        root->right = copyTree(rightTree);
                        dp[i].push_back(root);
                    }
                }
            }
        }

        for (auto &root : dp[n])
        {
            inorderTraversal(root, 1);
        }

        return dp[n];
    }

private:
    TreeNode* copyTree(TreeNode *const &source)
    {
        if (source == nullptr)
        {
            return nullptr;
        }
        TreeNode *root = new TreeNode();
        root->left = copyTree(source->left);
        root->right = copyTree(source->right);
        return root;
    }

    int inorderTraversal(TreeNode *root, int val)
    {
        if (root == nullptr)
        {
            return val;
        }
        val = inorderTraversal(root->left, val);
        root->val = val++;
        val = inorderTraversal(root->right, val);
        return val;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
