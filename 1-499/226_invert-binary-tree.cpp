//
// Created by Kirie on 2023/3/28.
//
#include <iostream>
#include <queue>
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
    TreeNode* invertTree(TreeNode *root)
    {
        return inorderInvertTree(root);
    }

    /** 中序遍历翻转二叉树 */
    TreeNode* inorderInvertTree(TreeNode *root)
    {
        if (root == nullptr)
        {
            return root;
        }
        inorderInvertTree(root->left);          // 翻转左子树
        std::swap(root->left, root->right);    // 交换左右子节点
        inorderInvertTree(root->left);          // 翻转原右子树
    }

    /** 前序遍历统一迭代法翻转二叉树 */
    TreeNode* uniformlyPostOrderInvertTree(TreeNode *root)
    {
        std::stack<TreeNode *> stack;
        TreeNode *node = root;
        if (root != nullptr)
        {
            stack.push(root);
        }
        while (!stack.empty())
        {
            node = stack.top();
            stack.pop();

            if (node)
            {
                if (node->right) stack.push(node->right);
                if (node->left) stack.push(node->left);

                stack.push(node);
                stack.push(nullptr);
            }
            else
            {
                node = stack.top();
                stack.pop();
                std::swap(node->left, node->right);
            }
        }

        return root;
    }

    /** 前序遍历二叉树 */
    TreeNode* postOrderInvertTree(TreeNode *root)
    {
        std::stack<TreeNode *> stack;
        if (root != nullptr)
        {
            stack.push(root);
        }

        while (!stack.empty())
        {
            TreeNode *node = stack.top();
            stack.pop();

            if (node->right) stack.push(node->right);
            if (node->left) stack.push(node->left);

            std::swap(node->left, node->right);
        }

        return root;
    }

    /** 层序遍历二叉树 */
    TreeNode* levelOrderInvertTree(TreeNode* root)
    {
        std::queue<TreeNode *> queue;
        if (root != nullptr)
        {
            queue.push(root);
        }

        while (!queue.empty())
        {
            // 这一层的节点数
            int numNodeInThisLevel = queue.size();

            // 遍历这一层的节点，将它们的子节点加入到队列中，然后交换它们的子节点
            for (int i = 0; i < numNodeInThisLevel; ++i)
            {
                TreeNode *node = queue.front();
                queue.pop();

                // 将子节点入队
                if (node->left)
                {
                    queue.push(node->left);
                }
                if (node->right)
                {
                    queue.push(node->right);
                }

                // 交换其子节点
                std::swap(node->left, node->right);
            }
        }
        return root;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
