#include <iostream>
#include <vector>
#include "leetcode.h"

class Solution
{
public:
    std::vector<std::vector<int>> findLeaves(TreeNode *root)
    {
        std::vector<std::vector<int>> ans;
        TreeNode sentinel(0, root, nullptr);
        while (sentinel.left)
        {
            std::vector<int> leavesVal;
            preorderTraversal(sentinel.left, &sentinel, leavesVal);
            ans.push_back(std::move(leavesVal));
        }
        return ans;
    }

private:
    void preorderTraversal(TreeNode *node, TreeNode *parent, std::vector<int> &leavesVal)
    {
        if (node == nullptr)
            return;

        if (node->left == nullptr && node->right == nullptr)
        {
            leavesVal.push_back(node->val);
            if (parent->left == node)
                parent->left = nullptr;
            else
                parent->right = nullptr;
            return;
        }

        if (node->left)
            preorderTraversal(node->left, node, leavesVal);
        if (node->right)
            preorderTraversal(node->right, node, leavesVal);
    }
};

/** 自底向上递归求深度 */
class Solution2
{
public:
    std::vector<std::vector<int>> findLeaves(TreeNode *root)
    {
        postorderTraversal(root);
        return ans;
    }

private:
    std::vector<std::vector<int>> ans;

    int postorderTraversal(TreeNode *node)
    {
        if (node == nullptr)
            return -1;

        int leftDepth = postorderTraversal(node->left);
        int rightDepth = postorderTraversal(node->right);

        int curDepth = std::max(leftDepth, rightDepth) + 1;
        if (curDepth >= ans.size())
        {
            ans.emplace_back(std::vector<int>());
        }
        ans[curDepth].push_back(node->val);

        return curDepth;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
