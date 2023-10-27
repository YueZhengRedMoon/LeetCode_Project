#include <iostream>
#include <vector>
#include <stack>

/** Definition for a binary tree node. */
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
    std::vector<int> inorderTraversal(TreeNode* root)
    {
        std::vector<int> inorderSequence;
        std::stack<TreeNode *> stack;

        if (root)
        {
            stack.push(root);
        }

        while (!stack.empty())
        {
            TreeNode *node = stack.top();
            if (node)
            {
                // 将该节点弹出，避免重复操作，下面再将右中左节点添加到栈中
                stack.pop();

                // 添加右节点（空节点不入栈）
                if (node->right)
                {
                    stack.push(node->right);
                }

                // 添加中节点
                stack.push(node);
                stack.push(nullptr);    // 中节点访问过，但是还没有处理，加入空节点作为标记

                // 添加左节点（空节点不入栈）
                if (node->left)
                {
                    stack.push(node->left);
                }
            }
            // 遇到空节点的时候，表示左子树访问完，此时才将下一个节点（也就是中节点）放进结果集
            else
            {
                // 将空节点弹出
                stack.pop();

                // 重新取出栈中元素
                node = stack.top();
                stack.pop();

                // 加入到结果集
                inorderSequence.push_back(node->val);
            }
        }   // while (!stack.empty())

        return inorderSequence;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
