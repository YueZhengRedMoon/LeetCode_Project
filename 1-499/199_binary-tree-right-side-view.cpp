#include <iostream>
#include <vector>
#include <queue>

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
    std::vector<int> rightSideView(TreeNode* root)
    {
        std::vector<int> result;
        std::queue<TreeNode *> queue;
        if (root != nullptr)
        {
            queue.push(root);
        }
        while (!queue.empty())
        {
            int numNodeInThisLevel = queue.size();
            for (int i = 0; i < numNodeInThisLevel - 1; ++i)
            {
                TreeNode *node = queue.front();
                queue.pop();
                if (node->left) queue.push(node->left);
                if (node->right) queue.push(node->right);
            }
            TreeNode *rightmost = queue.front();
            queue.pop();
            if (rightmost->left) queue.push(rightmost->left);
            if (rightmost->right) queue.push(rightmost->right);
            result.push_back(rightmost->val);
        }
        return result;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
