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
    std::vector<std::vector<int>> levelOrder(TreeNode* root)
    {
        std::vector<std::vector<int>> levelSequence;
        std::queue<TreeNode *> queue;
        if (root != nullptr)
        {
            queue.push(root);
        }

        while (!queue.empty())
        {
            int size = queue.size();    // 这一层的节点数
            // 开始遍历这一层
            std::vector<int> level;
            for (int i = 0; i < size; ++i)
            {
                TreeNode *node = queue.front();
                queue.pop();
                level.push_back(node->val);
                if (node->left)
                {
                    queue.push(node->left);
                }
                if (node->right)
                {
                    queue.push(node->right);
                }
            }
            levelSequence.push_back(level);
        }
        return levelSequence;
    }

    /** 递归法实现层序遍历 */
    
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
