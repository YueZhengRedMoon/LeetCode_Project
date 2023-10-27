#include <iostream>
#include <stack>

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
    bool hasPathSum(TreeNode *root, int targetSum)
    {
        if (root)
        {
            targetSum_ = targetSum;
            return traversal(root, 0);
        }
        else
        {
            return false;
        }
    }

private:
    int targetSum_;

    bool traversal(TreeNode *node, int sum)
    {
        // node判空在调用traversal之前

        sum += node->val;
        // node是叶子节点
        if (node->left == nullptr && node->right == nullptr)
        {
            if (sum == targetSum_)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        bool leftHasPathSum = false;
        if (node->left)
        {
            leftHasPathSum = traversal(node->left, sum);
        }
        bool rightHasPathSum = false;
        if (node->right)
        {
            rightHasPathSum = traversal(node->right, sum);
        }

        return leftHasPathSum || rightHasPathSum;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
