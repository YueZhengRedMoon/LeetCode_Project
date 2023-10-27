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
    bool isBalanced(TreeNode* root)
    {
        return getHeight(root) >= 0;
    }

private:
    /** 获取平衡二叉树的高度，如果二叉树不是平衡二叉树，则返回-1 */
    int getHeight(TreeNode *root)
    {
        if (root == nullptr)
        {
            return 0;
        }

        // 获取左子树的高度
        int leftHeight = getHeight(root->left);
        if (leftHeight == -1)
        {
            // 左子树不是平衡二叉树，整棵树都不是平衡二叉树
            return -1;
        }

        // 获取右子树的高度
        int rightHeight = getHeight(root->right);
        if (rightHeight == -1)
        {
            // 右子树不是平衡二叉树，整棵树都不是平衡二叉树
            return -1;
        }

        if (std::abs(leftHeight - rightHeight) > 1)
        {
            // 左右子树高度差的绝对值超过1，不是平衡二叉树
            return -1;
        }
        else
        {
            // 左右子树高度差的绝对值不超过1，是平衡二叉树，返回其高度
            return 1 + std::max(leftHeight, rightHeight);
        }
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
