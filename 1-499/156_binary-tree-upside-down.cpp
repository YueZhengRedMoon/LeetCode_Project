#include <iostream>
#include "../leetcode.h"

class Solution
{
public:
    TreeNode* upsideDownBinaryTree(TreeNode* root)
    {
        if (root == nullptr) return nullptr;
        if (root->left)
        {
            TreeNode *newRoot = upsideDownBinaryTree(root->left);
            TreeNode *newLeft = upsideDownBinaryTree(root->right);
            root->left->left = newLeft;
            root->left->right = root;
            root->left = nullptr;
            root->right = nullptr;
            return newRoot;
        }
        return root;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}