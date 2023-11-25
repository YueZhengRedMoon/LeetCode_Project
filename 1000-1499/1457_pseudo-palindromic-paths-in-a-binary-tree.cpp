#include <iostream>
#include <vector>
#include "../leetcode.h"

class Solution
{
public:
    int pseudoPalindromicPaths (TreeNode* root)
    {
        ans = 0;
        std::vector<int> count(10, 0);
        preorderTraversal(root, count);
        return ans;
    }

private:
    int ans;

    void preorderTraversal(TreeNode *node, std::vector<int> &count)
    {
        ++count[node->val];
        if (node->left == nullptr && node->right == nullptr)
        {
            int odd = 0;
            for (int i = 1; i <= 9; ++i)
            {
                odd += count[i] & 1;
            }
            ans += (odd <= 1);
            --count[node->val];
            return;
        }
        if (node->left)
            preorderTraversal(node->left, count);
        if (node->right)
            preorderTraversal(node->right, count);
        --count[node->val];
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
