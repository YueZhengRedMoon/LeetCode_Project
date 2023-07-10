#include <iostream>
#include <stack>
#include "leetcode.h"

class Solution
{
public:
    int closestValue(TreeNode* root, double target)
    {
        std::stack<TreeNode*> stack;
        TreeNode *cur = root;
        double minAbsDelta = 0x3f3f3f3f, delta = 0x3f3f3f3f;
        while (cur || !stack.empty())
        {
            if (cur)
            {
                stack.push(cur);
                cur = cur->left;
            }
            else
            {
                cur = stack.top();
                stack.pop();

                double temp = std::abs(target - cur->val);
                if (temp >= minAbsDelta)
                {
                    return target + delta;
                }
                minAbsDelta = temp;
                delta = cur->val - target;

                cur = cur->right;
            }
        }
        return target + delta;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
