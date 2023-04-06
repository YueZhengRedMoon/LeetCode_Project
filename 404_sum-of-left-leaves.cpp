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
    int sumOfLeftLeaves(TreeNode* root)
    {
        sum = 0;

        // root必定不为空
        traversal(root, false);

        return sum;
    }

private:
    int sum{0};

    void traversal(TreeNode *node, bool isLeftChild)
    {
        if (node->left == nullptr && node->right == nullptr)
        {
            if (isLeftChild)
            {
                sum += node->val;
            }
            return;
        }

        if (node->left) traversal(node->left, true);
        if (node->right) traversal(node->right, false);
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
