#include <iostream>
#include <vector>
#include <map>
#include <functional>
#include <algorithm>
#include "../leetcode.h"

class Solution
{
public:
    std::vector<std::vector<int>> verticalTraversal(TreeNode* root)
    {
        std::map<int, std::map<int, std::vector<int>>> tree;
        std::function<void(TreeNode*, int, int)> dfs = [&](TreeNode* node, int row, int col) {
            tree[col][row].push_back(node->val);
            if (node->left)
                dfs(node->left, row + 1, col - 1);
            if (node->right)
                dfs(node->right, row + 1, col + 1);
        };
        dfs(root, 0, 0);
        std::vector<std::vector<int>> ans;
        ans.reserve(tree.size());
        for (auto colIt = tree.begin(); colIt != tree.end(); ++colIt)
        {
            ans.push_back(std::vector<int>());
            std::vector<int> &col = ans.back();
            std::map<int, std::vector<int>> &colMap = colIt->second;
            for (auto rowIt = colMap.begin(); rowIt != colMap.end(); ++rowIt)
            {
                std::vector<int> &row = rowIt->second;
                if (row.size() > 1)
                    std::sort(row.begin(), row.end());
                col.insert(col.end(), row.begin(), row.end());
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
