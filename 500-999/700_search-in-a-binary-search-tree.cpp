#include <iostream>

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
    TreeNode* searchBST(TreeNode* root, int val)
    {
        TreeNode *current = root;
        while (current && current->val != val)
        {
            if (current->val < val)
            {
                current = current->right;
            }
            else
            {
                current = current->left;
            }
        }
        return current;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
