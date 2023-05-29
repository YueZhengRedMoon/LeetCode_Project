#include <iostream>
#include <vector>
#include "leetcode.h"

class Solution
{
public:
    std::vector<TreeNode*> delNodes(TreeNode *root, std::vector<int> &to_delete)
    {
        if (root == nullptr)
        {
            return forest;
        }

        for (const int &toDel : to_delete)
        {
            toDelete[toDel] = true;
        }

        if (!toDelete[root->val])
        {
            forest.push_back(root);
        }
        postorderTraversal(root, toDelete[root->val]);

        return forest;
    }

private:
    bool toDelete[1001]{false};
    std::vector<TreeNode*> forest;

    void postorderTraversal(TreeNode *root, bool isDeleted)
    {
        TreeNode *leftTree = root->left;
        if (leftTree)
        {
            bool leftIsDeleted = false;
            if (toDelete[leftTree->val])
            {
                root->left = nullptr;
                leftIsDeleted = true;
            }
            else if (isDeleted)
            {
                forest.push_back(leftTree);
            }
            postorderTraversal(leftTree, leftIsDeleted);
        }

        TreeNode *rightTree = root->right;
        if (rightTree)
        {
            bool rightIsDeleted = false;
            if (toDelete[rightTree->val])
            {
                root->right = nullptr;
                rightIsDeleted = true;
            }
            else if (isDeleted)
            {
                forest.push_back(rightTree);
            }
            postorderTraversal(rightTree, rightIsDeleted);
        }
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}