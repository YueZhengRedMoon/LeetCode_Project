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
    std::vector<std::string> binaryTreePaths(TreeNode *root)
    {
        if (root == nullptr)
        {
            return paths;
        }
        if (root->left == nullptr && root->right == nullptr)
        {
            paths.push_back(std::to_string(root->val));
            return paths;
        }

        if (root->left) dfs(root->left, std::to_string(root->val));
        if (root->right) dfs(root->right, std::to_string(root->val));

        return paths;
    }

    void dfs(TreeNode *node, std::string path)
    {
        path += "->" + std::to_string(node->val);
        if (node->left == nullptr && node->right == nullptr)
        {
            paths.push_back(path);
            return;
        }
        if (node->left) dfs(node->left, path);
        if (node->right) dfs(node->right, path);
    }

private:
    std::vector<std::string> paths;
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
