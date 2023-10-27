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
    int findBottomLeftValue(TreeNode* root)
    {
        bottomLeftNode = nullptr;
        bottomLeftNodeDepth = 0;
        traversal(root, 1);
        return bottomLeftNode->val;
    }

private:
    TreeNode *bottomLeftNode{nullptr};
    int bottomLeftNodeDepth{0};

    void traversal(TreeNode *node, int depth)
    {
        // node判空在调用traversal之前

        // 是叶子节点
        if (node->left == nullptr && node->right == nullptr)
        {
            if (depth > bottomLeftNodeDepth)
            {
                bottomLeftNode = node;
                bottomLeftNodeDepth = depth;
            }
            return;
        }

        if (node->left) traversal(node->left, depth + 1);
        if (node->right) traversal(node->right, depth + 1);
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
