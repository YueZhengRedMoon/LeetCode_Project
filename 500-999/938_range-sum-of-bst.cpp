#include <iostream>
#include <stack>
#include "../leetcode.h"

class Solution
{
public:
    int rangeSumBST(TreeNode* root, int low, int high)
    {
        int ans = 0;
        std::stack<TreeNode*> stack;
        TreeNode* cur = root;
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
                if (cur->val >= low)
                {
                    if (cur->val <= high)
                    {
                        ans += cur->val;
                    }
                    else
                    {
                        break;
                    }
                }
                cur = cur->right;
            }
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
