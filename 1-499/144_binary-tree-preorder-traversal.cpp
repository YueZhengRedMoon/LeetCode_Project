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
    std::vector<int> preorderTraversal(TreeNode* root)
    {
        std::vector<int> preorderSequence;
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
                stack.pop();

                // 添加右节点（空节点不入栈）
                if (node->right)
                {
                    stack.push(node->right);
                }

                // 添加左节点（空节点不入栈）
                if (node->left)
                {
                    stack.push(node->left);
                }

                // 添加中节点
                stack.push(node);
                stack.push(nullptr);
            }
            // 遇到空指针，下一个节点就是要处理的中节点
            else
            {
                stack.pop();    // 弹出空指针

                // 重新取出栈中元素
                node = stack.top();
                stack.pop();

                // 加入到结果集
                preorderSequence.push_back(node->val);
            }
        } // while (!stack.empty())

        return preorderSequence;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
