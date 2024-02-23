#include <iostream>
#include <vector>
#include <algorithm>
#include "../leetcode.h"

class Solution
{
public:
    long long kthLargestLevelSum(TreeNode* root, int k)
    {
        std::vector<long long> levelSum;
        std::vector<TreeNode*> level({root});
        while (!level.empty())
        {
            long long sum = 0;
            std::vector<TreeNode*> nextLevel;
            for (TreeNode* node : level)
            {
                sum += node->val;
                if (node->left)
                    nextLevel.push_back(node->left);
                if (node->right)
                    nextLevel.push_back(node->right);
            }
            levelSum.push_back(sum);
            std::swap(level, nextLevel);
        }

        int n = levelSum.size();
        if (k > n)
        {
            return -1;
        }
        else
        {
            std::nth_element(levelSum.begin(), levelSum.begin() + n - k, levelSum.end());
            return levelSum[n - k];
        }
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
