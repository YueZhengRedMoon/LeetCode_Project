#include <iostream>
#include <vector>
#include <unordered_map>
#include "leetcode.h"

/** 频繁查询第k个最小的值的情况 */
class Solution
{
public:
    int kthSmallest(TreeNode *root, int k)
    {
        // 预处理每棵子树的节点数
        calcNodeCount(root);

        TreeNode *node = root;
        while (node)
        {
            int leftCount = node->left == nullptr ? 0 : nodeCount[node->left];
            if (leftCount >= k)
            {
                node = node->left;
            }
            else if (leftCount == k - 1)
            {
                break;
            }
            else
            {
                k -= leftCount + 1;
                node = node->right;
            }
        }

        return node->val;
    }

private:
    std::unordered_map<TreeNode*, int> nodeCount;

    int calcNodeCount(TreeNode *root)
    {
        if (root == nullptr) return 0;
        return nodeCount[root] = 1 + calcNodeCount(root->left) + calcNodeCount(root->right);
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}