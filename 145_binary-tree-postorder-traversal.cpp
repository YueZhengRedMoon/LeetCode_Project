//
// Created by Kirie on 2023/3/27.
//
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
    /** 统一迭代法 */
    std::vector<int> postorderTraversal(TreeNode* root)
    {
        std::vector<int> postorderSequence;
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

                // 添加中节点
                stack.push(node);
                stack.push(nullptr);

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
            }
            // 访问到空指针，表示中节点左右子树均处理完，此时栈中下一个元素就是中节点
            else
            {
                stack.pop();    // 弹出空指针

                // 重新取出栈中元素
                node = stack.top();
                stack.pop();

                // 加入到结果集
                postorderSequence.push_back(node->val);
            }
        } // while (!stack.empty())

        return postorderSequence;
    }

    /** 通过last指针记录上一个处理的节点来实现后续遍历 */
    std::vector<int> postorderTraversalLastPtr(TreeNode* root)
    {
        std::vector<int> postorderSequence;

        std::stack<TreeNode *> stack;
        TreeNode *currentNode = root;
        TreeNode *lastNode = nullptr;   // 上一个处理的节点
        while (currentNode || !stack.empty())
        {
            // 遍历左子树
            while (currentNode)
            {
                stack.push(currentNode);
                currentNode = currentNode->left;
            }

            currentNode = stack.top();
            // 当前节点的左右子树都遍历完，处理当前节点
            if (currentNode->right == nullptr || currentNode->right == lastNode)
            {
                // 当前节点的左右子树都遍历完，处理当前节点
                postorderSequence.push_back(currentNode->val);
                stack.pop();            // 将当前节点出栈
                lastNode = currentNode; // 记录上一个处理的节点
                currentNode = nullptr;  // 将当前节点置空，以便访问下一个栈顶节点
            }
            else
            {
                // 当前节点右子树还未遍历完，遍历右子树
                currentNode = currentNode->right;
            }
        }

        return postorderSequence;
    }

    /** 双栈实现后序遍历 */
    std::vector<int> postorderTraversalDoubleStack(TreeNode* root)
    {
        std::vector<int> postorderSequence;
        if (root == nullptr)
        {
            return postorderSequence;
        }

        std::stack<TreeNode *> stack;
        std::stack<TreeNode *> sequenceStack;

        stack.push(root);
        while (!stack.empty())
        {
            TreeNode *node = stack.top();
            stack.pop();
            sequenceStack.push(node);

            if (node->left)
            {
                stack.push(node->left);
            }
            if (node->right)
            {
                stack.push(node->right);
            }
        }

        while (!sequenceStack.empty())
        {
            postorderSequence.push_back(sequenceStack.top()->val);
            sequenceStack.pop();
        }

        return postorderSequence;
    }
};

void printVector(std::vector<int>& nums)
{
    for (int i = 0; i < nums.size(); ++i)
    {
        std::cout << nums[i] << ' ';
    }
    std::cout << std::endl;
}

int main()
{
    // 构建一棵二叉树
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right->left = new TreeNode(6);
    root->right->right = new TreeNode(7);

    Solution solution;
    std::vector<int> postorderSequence = solution.postorderTraversal(root);
    printVector(postorderSequence);

    delete root->right->right;
    delete root->right->left;
    delete root->left->right;
    delete root->left->left;
    delete root->right;
    delete root->left;
    delete root;
    return 0;
}