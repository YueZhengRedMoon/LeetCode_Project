#include <iostream>
#include "../leetcode.h"

class Solution
{
public:
    int sumNumbers(TreeNode* root)
    {
        sum = 0;
        dfs(root, "");
        return sum;
    }

private:
    int sum;

    void dfs(TreeNode *node, std::string number)
    {
        number += std::to_string(node->val);

        if (node->left == nullptr && node->right == nullptr)
        {
            sum += std::atoi(number.c_str());
            return;
        }

        if (node->left) dfs(node->left, number);
        if (node->right) dfs(node->right, number);
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}