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
    std::vector<int> largestValues(TreeNode* root)
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
            int maxValue = queue.front()->val;
            for (int i = 0; i < numNodeInThisLevel; ++i)
            {
                TreeNode *node = queue.front();
                queue.pop();
                if (node->val > maxValue) maxValue = node->val;
                if (node->left) queue.push(node->left);
                if (node->right) queue.push(node->right);
            }
            result.push_back(maxValue);
        }
        return result;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
