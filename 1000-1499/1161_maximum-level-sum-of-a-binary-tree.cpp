#include <iostream>
#include <vector>
#include "../leetcode.h"

class Solution
{
public:
    int maxLevelSum(TreeNode* root)
    {
        int maxSum = root->val, ans = 1;
        std::vector<TreeNode*> curLevel({root});
        int level = 1;
        while (!curLevel.empty())
        {
            std::vector<TreeNode*> nxtLevel;
            int sum = 0;
            for (TreeNode* node : curLevel)
            {
                sum += node->val;
                if (node->left)
                    nxtLevel.push_back(node->left);
                if (node->right)
                    nxtLevel.push_back(node->right);
            }

            if (sum > maxSum)
            {
                maxSum = sum;
                ans = level;
            }

            ++level;
            std::swap(curLevel, nxtLevel);
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}