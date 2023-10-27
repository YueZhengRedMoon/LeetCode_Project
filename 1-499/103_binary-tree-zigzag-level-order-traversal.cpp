#include <iostream>
#include <vector>
#include <deque>
#include "../leetcode.h"

class Solution
{
public:
    std::vector<std::vector<int>> zigzagLevelOrder(TreeNode* root)
    {
        std::vector<std::vector<int>> ans;
        if (root == nullptr) return ans;
        std::deque<TreeNode*> curLevel, nextLevel;
        nextLevel.push_back(root);
        bool l2r = true;    // 从左向右
        while (!nextLevel.empty())
        {
            std::swap(curLevel, nextLevel);
            int curLevelSize = curLevel.size();
            std::vector<int> level;
            level.reserve(curLevelSize);

            int i, end, delta;
            if (l2r)
            {
                i = 0;
                end = curLevelSize;
                delta = 1;
            }
            else
            {
                i = curLevelSize - 1;
                end = -1;
                delta = -1;
            }
            for (; i != end; i += delta)
            {
                TreeNode *cur = curLevel[i];
                level.push_back(cur->val);
                if (l2r)
                {
                    if (cur->left) nextLevel.push_back(cur->left);
                    if (cur->right) nextLevel.push_back(cur->right);
                }
                else
                {
                    if (cur->right) nextLevel.push_front(cur->right);
                    if (cur->left) nextLevel.push_front(cur->left);
                }
            }
            l2r = !l2r;
            std::deque<TreeNode*> empty;
            curLevel.swap(empty);
            ans.push_back(std::move(level));
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
