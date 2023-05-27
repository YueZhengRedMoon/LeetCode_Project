#include <iostream>
#include <stack>
#include "leetcode.h"

class BSTIterator
{
public:
    BSTIterator(TreeNode* root) : cur (root)
    {

    }

    int next()
    {
        while (cur)
        {
            stack.push(cur);
            cur = cur->left;
        }
        cur = stack.top();
        stack.pop();
        int val = cur->val;
        cur = cur->right;
        return val;
    }

    bool hasNext()
    {
        return !stack.empty() || cur;
    }

private:
    std::stack<TreeNode*> stack;
    TreeNode *cur;
};


int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
