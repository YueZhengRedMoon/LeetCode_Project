#include <iostream>
#include "..\leetcode.h"

class Solution
{
public:
    TreeNode* subtreeWithAllDeepest(TreeNode* root)
    {
        return postorderTraverse(root).first;
    }

private:
    std::pair<TreeNode*, int> postorderTraverse(TreeNode* node)
    {
        if (node == nullptr)
        {
            return {nullptr, 0};
        }

        std::pair<TreeNode*, int> leftRes = postorderTraverse(node->left);
        std::pair<TreeNode*, int> rightRes = postorderTraverse(node->right);
        if (leftRes.second > rightRes.second)   // 左子树更深
        {
            return {leftRes.first, leftRes.second + 1};
        }
        else if (leftRes.second < rightRes.second)  // 右子树更深
        {
            return {rightRes.first, rightRes.second + 1};
        }
        else    // 两棵子树的深度一样
        {
            return {node, leftRes.second + 1};
        }
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}