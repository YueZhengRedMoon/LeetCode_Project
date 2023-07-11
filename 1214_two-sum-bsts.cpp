#include <iostream>
#include <stack>
#include "leetcode.h"

class Solution
{
public:
    bool twoSumBSTs(TreeNode *root1, TreeNode *root2, int target)
    {
        std::stack<TreeNode*> stack;
        TreeNode *cur = root1;
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

                if (search(root2, target - cur->val))
                    return true;

                cur = cur->right;
            }
        }
        return false;
    }

private:
    bool search(TreeNode *root, int target)
    {
        if (root->val > target)
        {
             if (root->left)
                 return search(root->left, target);
             else
                 return false;
        }
        else if (root->val < target)
        {
            if (root->right)
                return search(root->right, target);
            else
                return false;
        }
        else
        {
            return true;
        }
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
