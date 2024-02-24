#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include "../leetcode.h"

class Solution
{
public:
    std::vector<std::vector<int>> closestNodes(TreeNode* root, std::vector<int>& queries)
    {
        // 中序遍历二叉搜索树获得升序序列
        std::vector<int> inorderSequence;
        std::stack<TreeNode *> stack;
        TreeNode* current = root;
        while (current || !stack.empty())
        {
            if (current)
            {
                stack.push(current);
                current = current->left;
            }
            else
            {
                current = stack.top();
                stack.pop();
                inorderSequence.push_back(current->val);
                current = current->right;
            }
        }

        int n = queries.size();
        std::vector<std::vector<int>> ans(n, std::vector<int>(2));
        for (int i = 0; i < n; ++i)
        {
            ans[i][0] = lowerBound(inorderSequence, queries[i]);
            ans[i][1] = upperBound(inorderSequence, queries[i]);
        }

        return ans;
    }

private:
    // 获取升序数组nums中小于等于val的最大值，如果不存在这样的值，则返回-1
    int lowerBound(std::vector<int>& nums, int val)
    {
        int left = 0, right = nums.size(), res = -1;
        while (left < right)
        {
            int mid = (left + right) / 2;
            if (nums[mid] <= val)
            {
                res = nums[mid];
                left = mid + 1;
            }
            else
            {
                right = mid;
            }
        }
        return res;
    }

    // 获取升序数组nums中大于等于val的最小值，如果不存在这样的值，则返回-1
    int upperBound(std::vector<int>& nums, int val)
    {
        int left = 0, right = nums.size(), res = -1;
        while (left < right)
        {
            int mid = (left + right) / 2;
            if (nums[mid] >= val)
            {
                res = nums[mid];
                right = mid;
            }
            else
            {
                left = mid + 1;
            }
        }
        return res;
    }
};

namespace TimeLimit
{
    class Solution
    {
    public:
        std::vector<std::vector<int>> closestNodes(TreeNode* root, std::vector<int>& queries)
        {
            int n = queries.size();
            std::vector<std::vector<int>> ans(n, std::vector<int>(2));
            for (int i = 0; i < n; ++i)
            {
                ans[i][0] = lowerBound(root, queries[i]);

                ans[i][1] = upperBound(root, queries[i]);
                if (ans[i][1] == inf)
                    ans[i][1] = -1;
            }
            return ans;
        }

    private:
        const int inf {0x3f3f3f3f};

        // 获取二叉搜索树中<=val的最大值，如果不存在这样的值，则返回-1
        int lowerBound(TreeNode* root, int val)
        {
            if (root == nullptr)
                return -1;
            if (root->val > val)
                return lowerBound(root->left, val);
            if (root->val < val)
                return std::max(root->val, lowerBound(root->right, val));
            return val; // root->val == val
        }

        // 获取二叉搜索树中>=val的最小值，如果存在这样的值，返回inf
        int upperBound(TreeNode* root, int val)
        {
            if (root == nullptr)
                return inf;
            if (root->val > val)
                return std::min(root->val, upperBound(root->left, val));
            if (root->val < val)
                return upperBound(root->right, val);
            return val; // root->val == val
        }
    };
}

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
