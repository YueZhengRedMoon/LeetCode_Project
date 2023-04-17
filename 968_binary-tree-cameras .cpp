#include <iostream>
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
    int minCameraCover(TreeNode* root)
    {
        // node->val == 0 : 节点node没有被监控到
        // node->val == 1 : 节点node被监控到
        // node->val == 2 : 节点node放置了摄像机

        // 添加一个虚拟根
        TreeNode virtualRoot(0, root, nullptr);

        std::stack<TreeNode *> stack;
        TreeNode *last = nullptr;
        TreeNode *current = &virtualRoot;
        int cameraNum = 0;
        while (current || !stack.empty())
        {
            while (current)
            {
                stack.push(current);
                current = current->left;
            }
            current = stack.top();
            if (current->right && current->right != last)
            {
                current = current->right;
            }
            else
            {
                stack.pop();
                // 左孩子不为空
                if (current->left)
                {
                    // 左孩子没有被监控到
                    if (current->left->val == 0)
                    {
                        current->val = 2;  // 在current放摄像机
                    }
                        // 左孩子放置了摄像机
                    else if (current->left->val == 2)
                    {
                        current->val = 1;
                    }
                }
                // 右孩子不为空
                if (current->right)
                {
                    // 右孩子没有被监控到
                    if (current->right->val == 0)
                    {
                        current->val = 2;  // 在current放摄像机
                    }
                    // 右孩子放置了摄像机
                    else if (current->right->val == 2)
                    {
                        current->val = std::max(1, current->val);   // current被监控到
                    }
                }
                if (current->val == 2)
                {
                    ++cameraNum;
                }
                last = current;
                current = nullptr;
            }
        }
        return cameraNum;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
