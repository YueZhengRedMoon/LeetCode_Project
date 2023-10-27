#include <iostream>
#include <stack>
#include "../leetcode.h"

class Solution
{
public:
    bool twoSumBSTs(TreeNode *root1, TreeNode *root2, int target)
    {
        std::stack<TreeNode*> stack;
        TreeNode *cur = root1;
        while (cur || !stack.empty())
        {
            if (cur)
            {
                stack.push(cur);
                cur = cur->left;
            }
            else
            {
                cur = stack.top();
                stack.pop();

                if (search(root2, target - cur->val))
                    return true;

                cur = cur->right;
            }
        }
        return false;
    }

private:
    bool search(TreeNode *root, int target)
    {
        if (root->val > target)
        {
             if (root->left)
                 return search(root->left, target);
             else
                 return false;
        }
        else if (root->val < target)
        {
            if (root->right)
                return search(root->right, target);
            else
                return false;
        }
        else
        {
            return true;
        }
    }
};

class Solution2
{
public:
    bool twoSumBSTs(TreeNode *root1, TreeNode *root2, int target)
    {
        std::stack<TreeNode*> stack1, stack2;
        TreeNode *cur1 = root1, *cur2 = root2;

        // 遍历到root1中的最小节点
        while (cur1->left)
        {
            stack1.push(cur1);
            cur1 = cur1->left;
        }
        // 遍历到root2中的最大节点
        while (cur2->right)
        {
            stack2.push(cur2);
            cur2 = cur2->right;
        }

        while (cur1 && cur2)
        {
            int sum = cur1->val + cur2->val;
            if (sum < target)   // 和小了，cur1增加
            {
                cur1 = cur1->right;
                while (cur1 || !stack1.empty())
                {
                    if (cur1)
                    {
                        stack1.push(cur1);
                        cur1 = cur1->left;
                    }
                    else
                    {
                        cur1 = stack1.top();
                        stack1.pop();
                        break;
                    }
                }
            }
            else if (sum > target)  // 和大了，cur2减小
            {
                cur2 = cur2->left;
                while (cur2 || !stack2.empty())
                {
                    if (cur2)
                    {
                        stack2.push(cur2);
                        cur2 = cur2->right;
                    }
                    else
                    {
                        cur2 = stack2.top();
                        stack2.pop();
                        break;
                    }
                }
            }
            else
            {
                return true;
            }
        }

        return false;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
