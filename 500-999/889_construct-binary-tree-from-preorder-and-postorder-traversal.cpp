#include <iostream>
#include <vector>
#include <functional>
#include "../leetcode.h"
#include "debug.h"

class Solution
{
public:
    TreeNode* constructFromPrePost(std::vector<int>& preorder, std::vector<int>& postorder)
    {
        int n = preorder.size();
        std::vector<int> postorderIndex(n + 1);
        for (int i = 0; i < n; ++i)
        {
            postorderIndex[postorder[i]] = i;
        }

        TreeNode* root = new TreeNode(preorder[0]);
        auto leftConstruct = construct(1, preorder[0], preorder, postorderIndex);
        root->left = leftConstruct.first;
        auto rightConstruct = construct(leftConstruct.second, preorder[0], preorder, postorderIndex);
        root->right = rightConstruct.first;
        return root;
    }

private:
    std::pair<TreeNode*, int> construct(int i, int parentVal, std::vector<int>& preorder, std::vector<int>& postorderIndex)
    {
        if (i >= preorder.size())
            return {nullptr, i};

        int val = preorder[i];
        if (postorderIndex[val] < postorderIndex[parentVal])
        {
            TreeNode* cur = new TreeNode(val);
            ++i;
            auto leftConstruct = construct(i, val, preorder, postorderIndex);
            cur->left = leftConstruct.first;
            auto rightConstruct = construct(leftConstruct.second, val, preorder, postorderIndex);
            cur->right = rightConstruct.first;
            return {cur, rightConstruct.second};
        }
        else
        {
            return {nullptr, i};
        }
    }
};

int main()
{
    Solution solution;
    std::vector<int> preorder = {1,2,4,5,3,6,7}, postorder = {4,5,2,6,7,3,1};
    TreeNode* root = solution.constructFromPrePost(preorder, postorder);
    return 0;
}
