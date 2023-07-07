#include <iostream>
#include "leetcode.h"

class Solution
{
public:
    int longestConsecutive(TreeNode *root)
    {
        ans = 0;
        dfs(root, root->val - 1, 0);
        return ans;
    }

private:
    int ans;

    void dfs(TreeNode * node, int parentVal, int count)
    {
        if (node == nullptr)
            return;

        if (node->val == parentVal + 1)
        {
            if (++count > ans)
            {
                ans = count;
            }
        }
        else
        {
            count = 1;
        }

        dfs(node->left, node->val, count);
        dfs(node->right, node->val, count);
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}