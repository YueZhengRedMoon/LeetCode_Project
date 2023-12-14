#include <iostream>
#include <vector>
#include "../leetcode.h"

class Solution
{
public:
    TreeNode* reverseOddLevels(TreeNode* root)
    {
        int curLevel = 0;
        std::vector<TreeNode*> queue({root});
        while (!queue.empty())
        {
            std::vector<TreeNode*> nextLevel;
            nextLevel.reserve(queue.size() * 2);
            if (curLevel % 2 == 1)
            {
                int levelSize = queue.size();
                for (int i = 0, j = levelSize - 1; i < j; ++i, --j)
                {
                    std::swap(queue[i]->val, queue[j]->val);
                }
            }
            for (TreeNode *node : queue)
            {
                if (node->left)
                {
                    nextLevel.push_back(node->left);
                    nextLevel.push_back(node->right);
                }
            }
            std::swap(queue, nextLevel);
            ++curLevel;
        }
        return root;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
