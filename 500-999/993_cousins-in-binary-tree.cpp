#include <iostream>
#include <functional>
#include "..\leetcode.h"

class Solution
{
public:
    bool isCousins(TreeNode* root, int x, int y)
    {
        int xDepth = -1, yDepth = -1;
        TreeNode *xParent = nullptr, *yParent = nullptr;
        std::function<bool(TreeNode*, TreeNode*, int)> dfs = [&](TreeNode* node, TreeNode* parent, int depth) -> bool {
            if (node->val == x)
            {
                xDepth = depth;
                xParent = parent;
                if (xDepth == yDepth && xParent != yParent)
                {
                    return true;
                }
            }
            else if (node->val == y)
            {
                yDepth = depth;
                yParent = parent;
                if (xDepth == yDepth && xParent != yParent)
                {
                    return true;
                }
            }

            if (xDepth != -1 && yDepth != -1)
            {
                if (xDepth != yDepth || xParent == yParent)
                    return false;
            }

            if (node->left && dfs(node->left, node, depth + 1))
                return true;
            if (node->right && dfs(node->right, node, depth + 1))
                return true;

            return false;
        };

        return dfs(root, nullptr, 0);
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
