#include <iostream>
#include <vector>
#include <limits>
#include "leetcode.h"

class Solution
{
public:
    struct Tree
    {
        bool isBST;     // 是否是二叉搜索树
        int maxNode;    // 二叉搜索树的最大节点
        int minNode;    // 二叉搜索树的最小节点
        int nodeCount;  // 节点数
    };

    int largestBSTSubtree(TreeNode* root)
    {
        ans = 0;
        backtracking(root);
        return ans;
    }

private:
    const int inf{std::numeric_limits<int>::max()};
    const int ninf{std::numeric_limits<int>::min()};
    int ans;

    Tree backtracking(TreeNode *node)
    {
        if (node == nullptr)
        {
            return {true, ninf, inf, 0};
        }

        Tree leftTree = backtracking(node->left);
        Tree rightTree = backtracking(node->right);
        if (leftTree.isBST && rightTree.isBST && leftTree.maxNode < node->val && rightTree.minNode > node->val)
        {
            int nodeCount = leftTree.nodeCount + 1 + rightTree.nodeCount;
            if (nodeCount > ans)
                ans = nodeCount;
            int minNode = leftTree.minNode == inf ? node->val : leftTree.minNode;
            int maxNode = rightTree.maxNode == ninf ? node->val : rightTree.maxNode;
            return {true, maxNode, minNode, nodeCount};
        }
        return {false};
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}