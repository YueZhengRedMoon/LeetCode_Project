#include <iostream>
#include <stack>
#include <unordered_set>
#include "../leetcode.h"

class FindElements
{
public:
    FindElements(TreeNode* root)
    {
        std::stack<TreeNode*> stack({root});
        root->val = 0;
        while (!stack.empty())
        {
            TreeNode* node = stack.top();
            stack.pop();
            nodeSet.insert(node->val);

            if (node->left)
            {
                node->left->val = node->val * 2 + 1;
                stack.push(node->left);
            }

            if (node->right)
            {
                node->right->val = node->val * 2 + 2;
                stack.push(node->right);
            }
        }
    }

    bool find(int target)
    {
        return nodeSet.find(target) != nodeSet.end();
    }

private:
    std::unordered_set<int> nodeSet;
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
