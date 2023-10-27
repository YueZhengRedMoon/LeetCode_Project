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
    TreeNode* mergeTrees(TreeNode* root1, TreeNode* root2)
    {
        if (root1 == nullptr && root2 == nullptr)
        {
            return nullptr;
        }
        else if (root1 == nullptr)
        {
            return root2;
        }
        else if (root2 == nullptr)
        {
            return root1;
        }

        // root1 != nullptr && root2 != nullptr
        root1->val += root2->val;
        root1->left = mergeTrees(root1->left, root2->left);
        root1->right = mergeTrees(root1->right, root2->right);
        return root1;
    }

    TreeNode* mergeNewTrees(TreeNode* root1, TreeNode* root2)
    {
        TreeNode *newRoot = nullptr;
        if (root1 == nullptr && root2 == nullptr)
        {
            return newRoot;
        }
        else if (root1 == nullptr /* && root2 != nullptr */)
        {
            newRoot = new TreeNode(root2->val);
            newRoot->left = mergeNewTrees(nullptr, root2->left);
            newRoot->right = mergeNewTrees(nullptr, root2->right);
        }
        else if ( /* root1 != nullptr && */ root2 == nullptr)
        {
            newRoot = new TreeNode(root1->val);
            newRoot->left = mergeNewTrees(root1->left, nullptr);
            newRoot->right = mergeNewTrees(root1->right, nullptr);
        }
        // root1 != nullptr && root2 != nullptr
        else
        {
            newRoot = new TreeNode(root1->val + root2->val);
            newRoot->left = mergeNewTrees(root1->left, root2->left);
            newRoot->right = mergeNewTrees(root1->right, root2->right);
        }
        return newRoot;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
