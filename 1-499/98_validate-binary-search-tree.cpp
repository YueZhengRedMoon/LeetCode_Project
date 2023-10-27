#include <iostream>
#include <limits>
#include <stack>

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution
{
public:
    bool isValidBST(TreeNode *root)
    {
        std::stack<TreeNode *> stack;
        TreeNode *lastNode = nullptr;   // 中序遍历过程中上一个访问的节点
        TreeNode *current = root;
        while (current || !stack.empty())
        {
            // 遍历左子树
            if (current)
            {
                stack.push(current);
                current = current->left;
            }
            // 左子树遍历完，处理栈顶的中节点
            else
            {
                current = stack.top();
                stack.pop();

                if (lastNode && lastNode->val >= current->val)
                {
                    return false;
                }

                lastNode = current;         // 记录上一个访问的节点
                current = current->right;   // 遍历右子树
            }
        }
        return true;
    }

    bool myIsValidBST(TreeNode *root)
    {
        long long minNodeValue, maxNodeValue;
        return myIsValidBST(root, minNodeValue, maxNodeValue);
    }

private:
    bool myIsValidBST(TreeNode *root, long long &minNodeValue, long long &maxNodeValue)
    {
        if (root == nullptr)
        {
            minNodeValue = std::numeric_limits<long long>::max();
            maxNodeValue = std::numeric_limits<long long>::min();
            return true;
        }

        if (root->left == nullptr && root->right == nullptr)
        {
            minNodeValue = root->val;
            maxNodeValue = root->val;
            return true;
        }

        long long leftMin;
        long long leftMax;
        // 判断左子树是否是平衡二叉树
        if (!myIsValidBST(root->left, leftMin, leftMax) || leftMax >= root->val)
        {
            return false;
        }

        long long rightMin;
        long long rightMax;
        if (!myIsValidBST(root->right, rightMin, rightMax) || rightMin <= root->val)
        {
            return false;
        }

        minNodeValue = std::min(leftMin, static_cast<long long>(root->val));
        maxNodeValue = std::max(rightMax, static_cast<long long>(root->val));
        return true;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
