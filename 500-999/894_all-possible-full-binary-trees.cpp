#include <iostream>
#include <vector>
#include "../leetcode.h"

class Solution
{
public:
    std::vector<TreeNode *> allPossibleFBT(int n)
    {
        if (n % 2 == 0)
            return {};

        // f[i]:含有i个节点的所有可能的真二叉树
        std::vector<std::vector<TreeNode*>> f(n + 1);

        f[1].push_back(new TreeNode());

        for (int i = 3; i <= n; i += 2)
        {
            for (int l = 1; l < i; l += 2)
            {
                int r = i - 1 - l;
                for (TreeNode* leftTree : f[l])
                {
                    for (TreeNode* rightTree : f[r])
                    {
                        TreeNode* root = new TreeNode();
                        root->left = copyTree(leftTree);
                        root->right = copyTree(rightTree);
                        f[i].push_back(root);
                    }
                }
            }
        }

        return f[n];
    }

private:
    TreeNode* copyTree(TreeNode* root)
    {
        if (root == nullptr)
            return nullptr;

        TreeNode* newRoot = new TreeNode();
        newRoot->left = copyTree(root->left);
        newRoot->right = copyTree(root->right);
        return newRoot;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
