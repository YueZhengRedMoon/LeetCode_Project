#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include "leetcode.h"

class Solution
{
public:
    std::vector<std::vector<int>> verticalOrder(TreeNode* root)
    {
        if (root == nullptr)
            return {};

        postorderTraversal(root, 0, 0);

        std::vector<std::vector<int>> ans;
        ans.reserve(tree.size());
        for (auto it1 = tree.begin(); it1 != tree.end(); ++it1)
        {
            std::vector<int> col;
            col.reserve(it1->second.size());
            for (auto it2 = it1->second.begin(); it2 != it1->second.end(); ++it2)
            {
                col.push_back(it2->second);
            }
            ans.push_back(std::move(col));
        }

        return ans;
    }

private:
    std::map<int, std::multimap<int, int>> tree;

    void postorderTraversal(TreeNode *node, int col, int row)
    {
        tree[col].emplace(row, node->val);

        if (node->left)
            postorderTraversal(node->left, col - 1, row + 1);
        if (node->right)
            postorderTraversal(node->right, col + 1, row + 1);
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
