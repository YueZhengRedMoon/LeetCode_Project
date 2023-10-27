#include <iostream>

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution
{
public:
    int maxDepth(TreeNode* root)
    {
        result = 0;
        if (root == nullptr) return 0;
        getDepth(root, 1);
        return result;
    }

private:
    /** 已知的二叉树的最大深度 */
    int result;

    void getDepth(TreeNode *node, int depth)
    {
        // 处理中节点
        if (depth > result)
        {
            // 当前深度超过了已知的二叉树最大深度，更新它
            result = depth;
        }

        if (node->left == nullptr && node->right == nullptr) return;

        if (node->left) getDepth(node->left, depth + 1);
        if (node->right) getDepth(node->right, depth + 1);
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
