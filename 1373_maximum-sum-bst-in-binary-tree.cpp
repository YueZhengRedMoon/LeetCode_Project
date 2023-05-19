#include <iostream>
#include <stack>
#include <limits>
#include "leetcode.h"

/** 思路错误 */
class Solution
{
public:
    int maxSumBST(TreeNode* root)
    {
        /** 如果一棵子树是二叉搜索树：
         * 那么它的中序遍历得到的序列是升序的
         * 它中序遍历的第一个节点的左孩子必定为空，且它不能是它上一个访问节点的右孩子，
         * 它中序遍历的最后一个节点的右孩子必定为空，且它访问的上一个节点要么是它的左孩子，要么是它的父节点,且该节点是右孩子 */
        int ans = 0;
        int sum = 0;   // 当前的累加和
        std::stack<TreeNode*> stack;
        TreeNode *cur = root;          // 当前遍历到的节点
        TreeNode *last = nullptr;      // 上个访问的节点
        TreeNode *first = nullptr;     // 二叉搜索树中序遍历第一个访问的节点
        while (cur || !stack.empty())
        {
            // 遍历左子树
            while (cur)
            {
                stack.push(cur);
                cur = cur->left;
            }

            // 左子树遍历完，访问中节点
            cur = stack.top();
            stack.pop();
            // 单独考虑cur是叶子节点的情况
            if (cur->left == nullptr && cur->right == nullptr)
            {
                ans = std::max(ans, cur->val);
            }
            // 当前节点可能是子树中序遍历的第一个节点
            if (cur->left == nullptr && (last == nullptr || last->right != cur))
            {
                if (first == nullptr || cur->val <= last->val)
                {
                    first = cur;
                    sum = cur->val;
                }
                else
                {
                    sum += cur->val;
                }
            }
            // 当前节点不是子树中序遍历的第一个节点
            else
            {
                // 当前节点处于二叉搜索树中
                if (first && cur->val > last->val)
                {
                    sum += cur->val;
                    // 看当前节点是否是子树中序遍历的最后一个节点
                    if (cur->right == nullptr && (last == cur->left || last->right == cur))
                    {
                        ans = std::max(ans, sum);
                    }
                }
                else
                {
                    first = nullptr;
                }
            }
            last = cur;

            // 遍历右子树
            cur = cur->right;
        }

        return ans;
    }
};

class Solution2
{
public:
    struct SubTree
    {
        bool isBST;
        int maxVal;
        int minVal;
        int sumVal;
    };

    int maxSumBST(TreeNode* root)
    {
        postTraversal(root);
        return ans;
    }

private:
    const int inf{std::numeric_limits<int>::max()};
    const int ninf{std::numeric_limits<int>::min()};
    int ans{0};

    SubTree postTraversal(TreeNode *root)
    {
        if (root == nullptr)
        {
            return {true, ninf, inf, 0};
        }

        SubTree left = postTraversal(root->left);
        SubTree right = postTraversal(root->right);
        if (left.isBST && right.isBST && root->val > left.maxVal && root->val < right.minVal)
        {
            int maxVal = root->right ? right.maxVal : root->val;
            int minVal = root->left ? left.minVal : root->val;
            int sum = left.sumVal + root->val + right.sumVal;
            ans = std::max(ans, sum);
            return {true, maxVal, minVal, sum};
        }
        else
        {
            return {false};
        }
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}