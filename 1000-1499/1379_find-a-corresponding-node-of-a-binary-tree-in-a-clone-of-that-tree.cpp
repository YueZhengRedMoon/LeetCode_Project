#include <iostream>
#include <stack>
#include "../leetcode.h"

class Solution
{
public:
    TreeNode* getTargetCopy(TreeNode* original, TreeNode* cloned, TreeNode* target)
    {
        std::stack<TreeNode*> stack1({original}), stack2({cloned});
        while (!stack1.empty())
        {
            TreeNode* curNode1 = stack1.top();
            stack1.pop();
            TreeNode* curNode2 = stack2.top();
            stack2.pop();

            if (curNode1 == target)
            {
                return curNode2;
            }

            if (curNode1->left)
            {
                stack1.push(curNode1->left);
                stack2.push(curNode2->left);
            }
            if (curNode1->right)
            {
                stack1.push(curNode1->right);
                stack1.push(curNode2->right);
            }
        }
        return nullptr;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
