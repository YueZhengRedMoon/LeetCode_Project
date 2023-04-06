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
    std::vector<std::vector<int>> pathSum(TreeNode* root, int targetSum)
    {
        if (root != nullptr)
        {
            std::vector<int> path;
            targetSum_ = targetSum;
            traversal(root, 0, path);
        }
        return paths_;
    }

private:
    std::vector<std::vector<int>> paths_;
    int targetSum_;

    void traversal(TreeNode *node, int sum, std::vector<int> &path)
    {
        // node的判空在调用traversal前

        sum += node->val;
        path.push_back(node->val);

        if (node->left == nullptr && node->right == nullptr)
        {
            if (sum == targetSum_)
            {
                std::vector<int> newPath;
                newPath.reserve(path.size());
                for (auto it = path.begin(); it != path.end(); ++it)
                {
                    newPath.push_back(*it);
                }
                paths_.push_back(newPath);
            }
            path.pop_back();
            return;
        }

        if (node->left)
        {
            traversal(node->left, sum, path);
        }
        if (node->right)
        {
            traversal(node->right, sum, path);
        }

        path.pop_back();
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
