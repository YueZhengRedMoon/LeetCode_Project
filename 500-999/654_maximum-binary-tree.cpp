#include <iostream>
#include <vector>

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
    TreeNode* constructMaximumBinaryTree(std::vector<int>& nums)
    {
        return constructMaximumBinaryTree(nums, 0, nums.size() - 1);
    }

private:
    TreeNode* constructMaximumBinaryTree(std::vector<int>& nums, int begin, int end)
    {
        if (begin > end)
        {
            return nullptr;
        }
        if (begin == end)
        {
            return new TreeNode(nums[begin]);
        }

        int maxValueIndex = getMaxValueIndex(nums, begin, end);
        TreeNode *root = new TreeNode(nums[maxValueIndex]);
        root->left = constructMaximumBinaryTree(nums, begin, maxValueIndex - 1);
        root->right = constructMaximumBinaryTree(nums, maxValueIndex + 1, end);
        return root;
    }

    int getMaxValueIndex(std::vector<int>& nums, int begin, int end)
    {
        int maxValueIndex = begin;
        for (int i = begin + 1; i <= end; ++i)
        {
            if (nums[i] > nums[maxValueIndex])
            {
                maxValueIndex = i;
            }
        }
        return maxValueIndex;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
