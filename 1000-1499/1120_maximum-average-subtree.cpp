#include <iostream>
#include "../leetcode.h"

class Solution
{
public:
    double maximumAverageSubtree(TreeNode* root)
    {
        ans = 0.0;
        postorderTraversal(root);
        return ans;
    }

private:
    double ans;

    std::pair<double, int> postorderTraversal(TreeNode *node)
    {
        if (node == nullptr)
            return std::make_pair(0.0, 0);

        std::pair<double, int> left = postorderTraversal(node->left);
        std::pair<double, int> right = postorderTraversal(node->right);

        double sum = left.first + node->val + right.first;
        int count = left.second + 1 + right.second;

        ans = std::max(ans, sum / count);
        return std::make_pair(sum, count);
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
